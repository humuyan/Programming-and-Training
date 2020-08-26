#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QtGlobal>
#include <QTime>

void MainWindow::paintEvent(QPaintEvent*) {
	int x = 200, y = 100, d = std::min((height() - 100) / 40, (width() - 200) / 40);
	for (int i = 0; i < 40; ++i) {
		for (int j = 0; j < 40; ++j) {
			QPainter p(this);
			p.setBrush(color[i][j]);
			p.setPen(QPen(color[i][j], 0));
			p.drawRect(x + i * d, y + j * d, d, d);
		}
	}
}
void MainWindow::setGameStatus(const gameStatus &x) {
	curStatus = x;
	bool pause = (x == STARTED), resume = (x == PAUSED), restart = (x == PAUSED || x == ENDED), save = (x == PAUSED), start = (x == UNSTARTED), quit = true, load = (x == UNSTARTED);
	ui->pauseButton->setEnabled(pause), ui->pauseAction->setEnabled(pause);
	ui->resumeButton->setEnabled(resume), ui->resumeAction->setEnabled(resume);
	ui->restartButton->setEnabled(restart), ui->restartAction->setEnabled(restart);
	ui->saveButton->setEnabled(save), ui->saveAction->setEnabled(save);
	ui->startButton->setEnabled(start), ui->startAction->setEnabled(start);
	ui->quitButton->setEnabled(quit), ui->quitAction->setEnabled(quit);
	ui->loadButton->setEnabled(load), ui->loadAction->setEnabled(load);
	switch (curStatus) {
		case UNSTARTED:
			for (int i = 0; i < 40; ++i) {
				for (int j = 0; j < 40; ++j) {
					color[i][j] = (j == 19 && (i == 19 || i == 20)) ? Qt::green : Qt::gray;
				}
			}
			update();
			snakePosition.clear();
			snakePosition.push_back({19, 19}), snakePosition.push_back({20, 19});
			curDir = R;
			restLen = cnt = 0;
			ui->lcdNumber->display(0);
			break;
		case STARTED:
			timer.start(250);
			break;
		case PAUSED:
			timer.stop();
			break;
		case ENDED:
			timer.stop();
			QMessageBox::information(nullptr, "Game Over", "游戏结束！");
			break;
	}
}
void MainWindow::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton && curStatus == UNSTARTED) {
		int x = 200, y = 100, d = std::min((height() - 100) / 40, (width() - 200) / 40), i = (e->x() - x) / d, j = (e->y() - y) / d;
		if (i >= 0 && i < 40 && j >= 0 && j < 40 && !(j == 19 && (i == 19 || i == 20))) {
			color[i][j] = (color[i][j] == Qt::red) ? Qt::gray : Qt::red;
		}
		update();
	}
}
void MainWindow::generateFood() {
	int i, j;
	do {
		i = qrand() % 40, j = qrand() % 40;
	} while (color[i][j] != Qt::gray);
	color[i][j] = Qt::yellow;
	update();
}
void MainWindow::keyPressEvent(QKeyEvent *e) {
	if (curStatus == STARTED) {
		if (e->key() == Qt::Key_Up && curDir != D) {
			curDir = U;
		}
		if (e->key() == Qt::Key_Down && curDir != U) {
			curDir = D;
		}
		if (e->key() == Qt::Key_Left && curDir != R) {
			curDir = L;
		}
		if (e->key() == Qt::Key_Right && curDir != L) {
			curDir = R;
		}
		move();
	}
}
void MainWindow::quit() {
	close();
}
void MainWindow::start() {
	generateFood();
	setGameStatus(STARTED);
}
void MainWindow::pause() {
	setGameStatus(PAUSED);
}
void MainWindow::resume() {
	setGameStatus(STARTED);
}
void MainWindow::restart() {
	setGameStatus(UNSTARTED);
}
void MainWindow::save() {
	// TODO
}
void MainWindow::load() {
	// TODO
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle("贪吃蛇");
	setGameStatus(UNSTARTED);
	connect(&timer, SIGNAL(timeout()), this, SLOT(move()));
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	setFocusPolicy(Qt::StrongFocus);
}
MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::move() {
	position curHead = snakePosition.back(), nextHead = {curHead.x + dx[curDir], curHead.y + dy[curDir]};
	if (nextHead.x < 0 || nextHead.x >= 40 || nextHead.y < 0 || nextHead.y >= 40 || color[nextHead.x][nextHead.y] == Qt::red || color[nextHead.x][nextHead.y] == Qt::green) {
		setGameStatus(ENDED);
		return;
	}
	if (color[nextHead.x][nextHead.y] == Qt::yellow) {
		restLen += 3;
		generateFood();
	}
	color[nextHead.x][nextHead.y] = Qt::green;
	snakePosition.push_back(nextHead);
	if (restLen) {
		--restLen;
	} else {
		position curTail = snakePosition.front();
		snakePosition.pop_front();
		color[curTail.x][curTail.y] = Qt::gray;
	}
	update();
	ui->lcdNumber->display(++cnt);
}
void MainWindow::on_quitButton_clicked() { quit(); }
void MainWindow::on_quitAction_triggered() { quit(); }
void MainWindow::on_startButton_clicked() {	start(); }
void MainWindow::on_startAction_triggered() { start(); }
void MainWindow::on_pauseButton_clicked() {	pause(); }
void MainWindow::on_pauseAction_triggered() { pause(); }
void MainWindow::on_resumeButton_clicked() { resume(); }
void MainWindow::on_resumeAction_triggered() { resume(); }
void MainWindow::on_restartButton_clicked() { restart(); }
void MainWindow::on_restartAction_triggered() { restart(); }
void MainWindow::on_saveButton_clicked() { save(); }
void MainWindow::on_saveAction_triggered() { save(); }
void MainWindow::on_loadButton_clicked() { load(); }
void MainWindow::on_loadAction_triggered() { load(); }
