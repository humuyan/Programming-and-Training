#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT
	private slots:
		void on_quitButton_clicked();
		void on_quitAction_triggered();
	private:
		Ui::MainWindow *ui;
		enum gameStatus {UNSTARTED, STARTED, PAUSED, ENDED};
		void setGameStatus(const gameStatus &x);
		void quit();
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
};
#endif // MAINWINDOW_H
