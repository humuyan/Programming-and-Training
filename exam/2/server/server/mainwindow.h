#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
	private slots:
		void newClient();
		void messageReceived(QTcpSocket *socket);
	private:
		Ui::MainWindow *ui;
		QTcpServer *server;
		QVector<QTcpSocket*> clients;
};
#endif // MAINWINDOW_H