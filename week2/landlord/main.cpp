#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w[3];
	w[0].show(), w[1].show(), w[2].show();
	return a.exec();
}
