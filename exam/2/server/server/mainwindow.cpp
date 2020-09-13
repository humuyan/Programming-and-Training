#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	server = new QTcpServer;
	server->listen(QHostAddress::Any, 59583);
	connect(server, SIGNAL(newConnection()), this, SLOT(newClient()));
}

MainWindow::~MainWindow() {
	delete server;
	delete ui;
}

void MainWindow::newClient() {
	clients.push_back(server->nextPendingConnection());
}
