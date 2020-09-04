#ifndef SERVER_H
#define SERVER_H
#include "card.h"
#include <QWebSocket>
#include <QWebSocketServer>

enum MessageType {SEND_ID, DEAL, CALL_LANDLORD, CALL_STATUS_UPDATE, LANDLORD, PLAY, PLAY_STATUS_UPDATE, GAME_OVER, RESTART};
const int MaxPlayers = 3;
QJsonObject initMessage(const MessageType &type);

class Server : public QObject {
	Q_OBJECT
	private:
		QWebSocket* clients[MaxPlayers];
		int currentConnections, firstCaller, landlord, restartCount;
		Cards landlordCards;
		QWebSocketServer *serverSocket;
		void sendMessage(const QJsonObject &info, QWebSocket *client);
		void deal();
		void callLandlord();
		void startGame();
	private slots:
		void newClientConnect();
		void processMessage(QByteArray msg);
	public:
		Server();
		~Server();
};

#endif // SERVER_H
