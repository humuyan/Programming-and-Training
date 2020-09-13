#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	ui->getButton->setEnabled(false);
}

MainWindow::~MainWindow() {
	delete ui;
}


void MainWindow::on_pushButton_clicked() {
	QFileDialog::getOpenFileName(this, "", "./", "(*.*)");
}
