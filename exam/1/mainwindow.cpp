#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	resize(QSize(600, 600 + ui->menubar->height()));
	connect(&timer, SIGNAL(timeout()), this, SLOT(slotClicked()));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setBrush(Qt::white), painter.fillRect(0, 0, width(), height(), painter.brush());
	for (Square &x: squares) {
		painter.setBrush(x.chosen ? Qt::green : Qt::blue), painter.setPen(x.chosen ? Qt::red : Qt::black);
		painter.drawRect(x.x, x.y, 60, 60);
	}
}

void MainWindow::mousePressEvent(QMouseEvent* e) {
	if (e->button() == Qt::LeftButton) {
		timer.start(100);
		lastClick = e;
	} else if (e->button() == Qt::RightButton) {
		if (!squares.empty() && squares.rbegin()->chosen) {
			squares.rbegin()->chosen = false;
			update();
		}
	}
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		timer.stop();
		squares.push_back({e->x() - 30, e->y() - 30, false});
		update();
	}
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
	if (!squares.empty() && squares.rbegin()->chosen) {
		if (e->key() == Qt::Key_W) squares.rbegin()->y -= 30;
		if (e->key() == Qt::Key_S) squares.rbegin()->y += 30;
		if (e->key() == Qt::Key_A) squares.rbegin()->x -= 30;
		if (e->key() == Qt::Key_D) squares.rbegin()->x += 30;
		update();
	}
}

void MainWindow::slotClicked() {
	timer.stop();
	Square chosen = {-1, -1, false};
	for (int i = squares.size() - 1; i >= 0; --i) {
		if (lastClick->x() >= squares[i].x && lastClick->x() <= squares[i].x + 60 && lastClick->y() >= squares[i].y && lastClick->y() <= squares[i].y + 60) {
			chosen = squares[i];
			squares.erase(squares.begin() + i);
			break;
		}
	}
	if (chosen.x != -1) {
		for (Square &x: squares) {
			x.chosen = false;
		}
		chosen.chosen = true;
		squares.push_back(chosen);
		update();
	}
}

void MainWindow::on_actionExit_triggered() {
	close();
}

void MainWindow::on_actionClear_triggered() {
	squares.clear();
	update();
}

void MainWindow::on_actionSave_triggered() {
	QString fileName = QFileDialog::getSaveFileName(this, "", "./", "存档文件(*.sq)");
	if (fileName != "") {
		QFile output(fileName);
		output.open(QIODevice::WriteOnly);
		QDataStream out(&output);
		out << int(squares.size());
		for (Square &x: squares) {
			out << int(x.x) << int(x.y) << int(x.chosen);
		}
		output.close();
	}
}

void MainWindow::on_actionOpen_triggered() {
	QString fileName = QFileDialog::getOpenFileName(this, "", "./", "存档文件(*.sq)");
	if (fileName != "") {
		QFile input(fileName);
		input.open(QIODevice::ReadOnly);
		QDataStream in(&input);
		int size;
		in >> size;
		squares.clear();
		for (int x, y, chosen; size--; ) {
			in >> x >> y >> chosen;
			squares.push_back({x, y, bool(chosen)});
		}
		input.close();
		update();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
	if (!squares.empty() && squares.rbegin()->chosen) {
		squares.rbegin()->x = e->x() - 30, squares.rbegin()->y = e->y() - 30;
		update();
	}
}
