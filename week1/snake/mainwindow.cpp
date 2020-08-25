#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::quit() {
	close();
}
void MainWindow::setGameStatus(const gameStatus &x) {
	switch (x) {
		case UNSTARTED:
			ui->pauseButton->setEnabled(false), ui->pauseAction->setEnabled(false);
			ui->resumeButton->setEnabled(false), ui->resumeAction->setEnabled(false);
			break;
	}
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle("贪吃蛇");
	setGameStatus(UNSTARTED);
}
MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_quitButton_clicked() {
	quit();
}
void MainWindow::on_quitAction_triggered() {
	quit();
}
