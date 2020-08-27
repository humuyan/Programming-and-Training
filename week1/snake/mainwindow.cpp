#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QtGlobal>
#include <QTime>
#include <QFileDialog>

void MainWindow::paintEvent(QPaintEvent*) {
	int canvasHeight = height() - ui->toolBar->height() - ui->menubar->height(), canvasWidth = width() - ui->groupBox->width(), tableSize = std::min(canvasHeight, canvasWidth);
	int gridSize = tableSize / Size, offsetX = (canvasWidth - tableSize) / 2 + ui->groupBox->width(), offsetY = (canvasHeight - tableSize) / 2 + ui->toolBar->height() + ui->menubar->height();
	for (int i = 0; i < Size; ++i) {
		for (int j = 0; j < Size; ++j) {
			QPainter p(this);
			p.setBrush(color[grid[i][j]]);
			p.setPen(QPen(color[grid[i][j]], 0));
			p.drawRect(offsetX + i * gridSize, offsetY + j * gridSize, gridSize, gridSize);
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
			for (int i = 0; i < Size; ++i) {
				for (int j = 0; j < Size; ++j) {
					grid[i][j] = (j == Size / 2 && (i == Size / 2 - 1 || i == Size / 2)) ? SNAKE : EMPTY;
				}
			}
			update();
			snakePosition.clear();
			snakePosition.push_back({Size / 2 - 1, Size / 2}), snakePosition.push_back({Size / 2, Size / 2});
			curDir = RIGHT;
			restLen = cnt = 0;
			ui->lcdNumber->display(0);
			break;
		case STARTED:
			timer.start(RefreshPeriod);
			setFocus();
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
		int canvasHeight = height() - ui->toolBar->height() - ui->menubar->height(), canvasWidth = width() - ui->groupBox->width(), tableSize = std::min(canvasHeight, canvasWidth);
		int gridSize = tableSize / Size, offsetX = (canvasWidth - tableSize) / 2 + ui->groupBox->width(), offsetY = (canvasHeight - tableSize) / 2 + ui->toolBar->height() + ui->menubar->height();
		int i = (e->x() - offsetX) / gridSize, j = (e->y() - offsetY) / gridSize;
		if (i >= 0 && i < Size && j >= 0 && j < Size && !(j == 19 && (i == 19 || i == 20))) {
			grid[i][j] = (grid[i][j] == HANDICAP) ? EMPTY : HANDICAP;
		}
		update();
	}
}
void MainWindow::generateFood() {
	int i, j;
	do {
		i = qrand() % Size, j = qrand() % Size;
	} while (grid[i][j] != EMPTY);
	grid[i][j] = FOOD;
	update();
}
void MainWindow::keyPressEvent(QKeyEvent *e) {
	if (curStatus == STARTED) {
		if (e->key() == Qt::Key_Up && curDir != DOWN) curDir = UP, move();
		if (e->key() == Qt::Key_Down && curDir != UP) curDir = DOWN, move();
		if (e->key() == Qt::Key_Left && curDir != RIGHT) curDir = LEFT, move();
		if (e->key() == Qt::Key_Right && curDir != LEFT) curDir = RIGHT, move();
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
	QString fileName = QFileDialog::getSaveFileName(this, "", "./", "贪吃蛇存档文件(*.snake)");
	if (fileName != "") {
		QFile output(fileName);
		output.open(QIODevice::WriteOnly);
		QDataStream out(&output);
		for (int i = 0; i < Size; ++i) {
			for (int j = 0; j < Size; ++j) {
				out << qint8(grid[i][j]);
			}
		}
		out << qint32(cnt) << qint8(curDir) << qint16(snakePosition.size());
		for (position g: snakePosition) {
			out << qint8(g.x) << qint8(g.y);
		}
		output.close();
	}
}
void MainWindow::load() {
	QString fileName = QFileDialog::getOpenFileName(this, "", "./", "贪吃蛇存档文件(*.snake)");
	if (fileName != "") {
		QFile input(fileName);
		input.open(QIODevice::ReadOnly);
		QDataStream in(&input);
		qint8 x, y;
		for (int i = 0; i < Size; ++i) {
			for (int j = 0; j < Size; ++j) {
				in >> x;
				grid[i][j] = gridType(x);
			}
		}
		qint16 z;
		in >> cnt >> x >> z;
		curDir = direction(x);
		snakePosition.clear();
		while (z--) {
			in >> x >> y;
			snakePosition.push_back({x, y});
		}
		input.close();
		update();
		setGameStatus(PAUSED);
	}
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
	if (nextHead.x < 0 || nextHead.x >= Size || nextHead.y < 0 || nextHead.y >= Size || grid[nextHead.x][nextHead.y] == HANDICAP || grid[nextHead.x][nextHead.y] == SNAKE) {
		setGameStatus(ENDED);
		return;
	}
	if (grid[nextHead.x][nextHead.y] == FOOD) {
		restLen += 3;
		generateFood();
	}
	grid[nextHead.x][nextHead.y] = SNAKE;
	snakePosition.push_back(nextHead);
	if (restLen) {
		--restLen;
	} else {
		position curTail = snakePosition.front();
		snakePosition.pop_front();
		grid[curTail.x][curTail.y] = EMPTY;
	}
	update();
	ui->lcdNumber->display(++cnt);
}
void MainWindow::on_quitButton_clicked() { quit(); }
void MainWindow::on_quitAction_triggered() { quit(); }
void MainWindow::on_startButton_clicked() { start(); }
void MainWindow::on_startAction_triggered() { start(); }
void MainWindow::on_pauseButton_clicked() { pause(); }
void MainWindow::on_pauseAction_triggered() { pause(); }
void MainWindow::on_resumeButton_clicked() { resume(); }
void MainWindow::on_resumeAction_triggered() { resume(); }
void MainWindow::on_restartButton_clicked() { restart(); }
void MainWindow::on_restartAction_triggered() { restart(); }
void MainWindow::on_saveButton_clicked() { save(); }
void MainWindow::on_saveAction_triggered() { save(); }
void MainWindow::on_loadButton_clicked() { load(); }
void MainWindow::on_loadAction_triggered() { load(); }
