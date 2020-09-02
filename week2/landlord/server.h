#ifndef SERVER_H
#define SERVER_H
#include <QWebSocket>
#include <QWebSocketServer>

class Server : public QObject {
	Q_OBJECT
	private:
		static const int MaxPlayers = 3;
		QWebSocket* clients[MaxPlayers];
		int curConnections;
		QWebSocketServer *serverSocket;
	private slots:
		void newClientConnect();
	public:
		Server();
		~Server();
		void deal() const;
};

#endif // SERVER_H
