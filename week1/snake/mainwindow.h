#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QQueue>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT
	private slots:
		void move();
		void on_quitButton_clicked();
		void on_quitAction_triggered();
		void on_startButton_clicked();
		void on_startAction_triggered();
		void on_pauseButton_clicked();
		void on_pauseAction_triggered();
		void on_resumeButton_clicked();
		void on_resumeAction_triggered();
		void on_restartButton_clicked();
		void on_restartAction_triggered();
		void on_saveButton_clicked();
		void on_saveAction_triggered();
		void on_loadButton_clicked();
		void on_loadAction_triggered();

	private:
		enum gameStatus {UNSTARTED, STARTED, PAUSED, ENDED};
		enum direction {UP, DOWN, LEFT, RIGHT};
		const static int Size = 40, RefreshPeriod = 200;
		const int dx[4] = {0, 0, -1, 1};
		const int dy[4] = {-1, 1, 0, 0};
		struct position {
			int x, y;
		};
		enum gridType {EMPTY, SNAKE, FOOD, HANDICAP};
		const QColor color[4] = {Qt::gray, Qt::green, Qt::yellow, Qt::red};
		Ui::MainWindow *ui;
		gameStatus curStatus;
		direction curDir;
		int restLen, cnt;
		gridType grid[Size][Size];
		QTimer timer;
		QQueue<position> snakePosition;
		void paintEvent(QPaintEvent *e);
		void setGameStatus(const gameStatus &x);
		void mousePressEvent(QMouseEvent *e);
		void generateFood();
		void keyPressEvent(QKeyEvent *e);
		void quit();
		void start();
		void pause();
		void resume();
		void restart();
		void save();
		void load();
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
};
#endif // MAINWINDOW_H
