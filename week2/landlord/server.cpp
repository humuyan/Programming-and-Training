#include "server.h"
#include "card.h"
#include <QJsonObject>
#include <QJsonDocument>

void Server::newClientConnect() {
	clients[curConnections++] = serverSocket->nextPendingConnection();
	if (curConnections == MaxPlayers) {
		serverSocket->close();
	}
}
Server::Server() {
	serverSocket = new QWebSocketServer("Landlord Server", QWebSocketServer::NonSecureMode);
	serverSocket->listen(QHostAddress::Any, 59583);
	connect(serverSocket, SIGNAL(newConnection()), this, SLOT(newClientConnect()));
	curConnections = 0;
}
Server::~Server() {
	delete serverSocket;
	for (int i = 0; i < curConnections; ++i) {
		delete clients[i];
	}
}
void Server::deal() const {
	QVector<Card> cards;
	for (int suit = 0; suit < 4; ++suit) {
		for (int point = 0; point < 13; ++point) {
			cards.push_back(Card(CardSuit(suit), CardPoint(point)));
		}
	}
	cards.push_back(Card(SPADE, LITTLEJOKER)), cards.push_back(Card(SPADE, BIGJOKER));
	std::random_shuffle(cards.begin(), cards.end());
	for (int i = 0; i < curConnections; ++i) {
		QJsonObject info;
		info.insert("messageType", "deal");
		info.insert("cards", Cards(cards.begin() + i * 17, cards.begin() + (i + 1) * 17).toJson());
		info.insert("landlordCards", Cards(cards.begin() + 51, cards.end()).toJson());
		clients[i]->sendBinaryMessage(QJsonDocument(info).toJson());
	}
}
