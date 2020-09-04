#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "server.h"
#include <QMainWindow>
#include <QWebSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT
	private slots:
		void processMessage(QByteArray msg);
		void serverConnected();
		void establishServer();
		void on_startButton_clicked();
		void on_callLandlordButton_clicked();
		void on_noCallButton_clicked();
		void on_exitButton_clicked();
		void on_playButton_clicked();
		void on_noPlayButton_clicked();
		void on_restartButton_clicked();

	private:
		const QUrl ServerUrl = QUrl("ws://127.0.0.1:59583");
		const QString CallButtonName[2][2] = {{"不叫", "不抢"}, {"叫地主", "抢地主"}};
		struct UICard : public Card {
			bool up;
			QImage image;
			QString fileName;
			static int height, width;
			UICard() = default;
			UICard(const Card &base);
		} Padding, landlordCards[3];
		Ui::MainWindow *ui;
		QWebSocket *clientSocket;
		Server *server;
		int id, leftRest, rightRest, noPlayCount;
		bool dealt, showLandlordCards, playing, firstDisabled;
		QVector<UICard> cards, centralCards;
		Cards chosenCards, lastPlay;
		void sendMessage(const QJsonObject &info);
		void updateRest();
		template<class T> void sortCards(QVector<T> &cards);
		void resizeEvent(QResizeEvent*);
		void paintEvent(QPaintEvent*);
		void mousePressEvent(QMouseEvent *e);
		void init();
		void callLandlord(const bool &called);
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
};
#endif // MAINWINDOW_H
