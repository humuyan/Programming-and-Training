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
		void serverConnected();
		void establishServer();
		void on_startButton_clicked();
	private:
		const QUrl serverUrl = QUrl("ws://127.0.0.1:59583");
		Ui::MainWindow *ui;
		QWebSocket *clientSocket;
		Server *server;
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
};
#endif // MAINWINDOW_H
