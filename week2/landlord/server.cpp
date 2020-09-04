#include "server.h"
#include <QJsonObject>
#include <QJsonDocument>

QJsonObject initMessage(const MessageType &type) {
	QJsonObject ret;
	ret.insert("messageType", type);
	return ret;
}

void Server::sendMessage(const QJsonObject &info, QWebSocket *client = nullptr) {
	if (client != nullptr) {
		client->sendBinaryMessage(QJsonDocument(info).toJson());
	} else {
		for (int i = 0; i < MaxPlayers; ++i) {
			clients[i]->sendBinaryMessage(QJsonDocument(info).toJson());
		}
	}
}
void Server::newClientConnect() {
	clients[currentConnections] = serverSocket->nextPendingConnection();
	connect(clients[currentConnections], SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(processMessage(QByteArray)));
	QJsonObject sendInfo = initMessage(SEND_ID);
	sendInfo.insert("ID", currentConnections);
	sendMessage(sendInfo, clients[currentConnections++]);
	if (currentConnections == MaxPlayers) {
		serverSocket->close();
		deal();
	}
}
void Server::processMessage(QByteArray msg) {
	QJsonObject info = QJsonDocument::fromJson(msg).object(), sendInfo;
	int id = info["clientID"].toInt();
	bool sbCalled;
	switch (info["messageType"].toInt()) {
		case CALL_LANDLORD:
			sbCalled = info["sbCalled"].toBool();
			sendInfo = initMessage(CALL_STATUS_UPDATE);
			sendInfo.insert("ID", id);
			sendInfo.insert("called", info["called"]);
			sendInfo.insert("sbCalled", sbCalled);
			sendMessage(sendInfo);
			if (info["called"].toBool()) {
				landlord = id;
				sbCalled = true;
			}
			id = (id + 1) % MaxPlayers;
			if (id != firstCaller) {
				sendInfo = initMessage(CALL_LANDLORD);
				sendInfo.insert("sbCalled", sbCalled);
				sendMessage(sendInfo, clients[id]);
			} else {
				startGame();
			}
			break;
		case PLAY:
			sendInfo = initMessage(PLAY_STATUS_UPDATE);
			sendInfo.insert("ID", id);
			sendInfo.insert("cards", info["cards"]);
			sendMessage(sendInfo);
			if (info["finished"].toBool()) {
				for (int i = 0; i < MaxPlayers; ++i) {
					sendInfo = initMessage(GAME_OVER);
					sendInfo.insert("win", (i == landlord && id == landlord) || (i != landlord && id != landlord));
					sendMessage(sendInfo, clients[i]);
				}
				restartCount = 0;
			} else {
				sendMessage(initMessage(PLAY), clients[(id + 1) % MaxPlayers]);
			}
			break;
		case RESTART:
			if (++restartCount == MaxPlayers) {
				sendMessage(initMessage(RESTART));
				deal();
			}
			break;
	}
}
Server::Server() {
	serverSocket = new QWebSocketServer("Landlord Server", QWebSocketServer::NonSecureMode);
	serverSocket->listen(QHostAddress::Any, 59583);
	connect(serverSocket, SIGNAL(newConnection()), this, SLOT(newClientConnect()));
	currentConnections = 0;
}
Server::~Server() {
	delete serverSocket;
	for (int i = 0; i < currentConnections; ++i) {
		delete clients[i];
	}
}
void Server::deal() {
	QVector<Card> cards;
	for (int suit = 0; suit < 4; ++suit) {
		for (int point = 0; point < 13; ++point) {
			cards.push_back(Card(CardSuit(suit), CardPoint(point)));
		}
	}
	cards.push_back(Card(SPADE, LITTLEJOKER)), cards.push_back(Card(SPADE, BIGJOKER));
	std::random_shuffle(cards.begin(), cards.end());
	landlordCards = Cards(cards.begin() + 51, cards.end());
	for (int i = 0; i < MaxPlayers; ++i) {
		QJsonObject sendInfo = initMessage(DEAL);
		sendInfo.insert("cards", Cards(cards.begin() + i * 17, cards.begin() + (i + 1) * 17).toJson());
		sendInfo.insert("landlordCards", landlordCards.toJson());
		sendMessage(sendInfo, clients[i]);
	}
	callLandlord();
}
void Server::callLandlord() {
	firstCaller = landlord = rand() % MaxPlayers;
	QJsonObject sendInfo = initMessage(CALL_LANDLORD);
	sendInfo.insert("sbCalled", false);
	sendMessage(sendInfo, clients[firstCaller]);
}
void Server::startGame() {
	QJsonObject sendInfo = initMessage(LANDLORD);
	sendInfo.insert("ID", landlord);
	sendMessage(sendInfo);
	sendMessage(initMessage(PLAY), clients[landlord]);
}
