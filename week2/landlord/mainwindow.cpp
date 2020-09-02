#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	srand(time(nullptr));
	clientSocket = new QWebSocket;
	connect(clientSocket, SIGNAL(connected()), this, SLOT(serverConnected()));
	connect(clientSocket, SIGNAL(disconnected()), this, SLOT(establishServer()));
	ui->callLandlordButton->hide(), ui->noCallButton->hide();
}
MainWindow::~MainWindow() {
	delete ui, delete clientSocket;
	if (server != nullptr) {
		delete server;
	}
}

void MainWindow::serverConnected() {
	disconnect(clientSocket, SIGNAL(connected()), this, SLOT(serverConnected()));
	disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(establishServer()));
	QMessageBox::information(nullptr, "Connected", "连接成功！");
	ui->startButton->setEnabled(false);
	ui->callLandlordButton->show(), ui->noCallButton->show();
}
void MainWindow::establishServer() {
	server = new Server;
	clientSocket->open(serverUrl);
}
void MainWindow::on_startButton_clicked() {
	clientSocket->open(serverUrl);
}
