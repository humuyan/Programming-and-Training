#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
	private slots:
		void on_actionExit_triggered();
		void on_actionClear_triggered();
		void slotClicked();
		void on_actionSave_triggered();

		void on_actionOpen_triggered();

private:
		Ui::MainWindow *ui;
		struct Square {
			int x, y;
			bool chosen;
		};
		QVector<Square> squares;
		QTimer timer;
		QMouseEvent *lastClick;
		void paintEvent(QPaintEvent*);
		void mousePressEvent(QMouseEvent* e);
		void mouseDoubleClickEvent(QMouseEvent *e);
		void keyPressEvent(QKeyEvent *e);
		void mouseMoveEvent(QMouseEvent *e);
};
#endif // MAINWINDOW_H
