/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *loadAction;
    QAction *saveAction;
    QAction *quitAction;
    QAction *startAction;
    QAction *pauseAction;
    QAction *resumeAction;
    QAction *restartAction;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *startButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QPushButton *restartButton;
    QPushButton *quitButton;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *gameMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        loadAction = new QAction(MainWindow);
        loadAction->setObjectName(QString::fromUtf8("loadAction"));
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        quitAction = new QAction(MainWindow);
        quitAction->setObjectName(QString::fromUtf8("quitAction"));
        startAction = new QAction(MainWindow);
        startAction->setObjectName(QString::fromUtf8("startAction"));
        pauseAction = new QAction(MainWindow);
        pauseAction->setObjectName(QString::fromUtf8("pauseAction"));
        resumeAction = new QAction(MainWindow);
        resumeAction->setObjectName(QString::fromUtf8("resumeAction"));
        restartAction = new QAction(MainWindow);
        restartAction->setObjectName(QString::fromUtf8("restartAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, -30, 151, 571));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 140, 131, 381));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(verticalLayoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout->addWidget(startButton);

        loadButton = new QPushButton(verticalLayoutWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        verticalLayout->addWidget(loadButton);

        saveButton = new QPushButton(verticalLayoutWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setEnabled(true);

        verticalLayout->addWidget(saveButton);

        pauseButton = new QPushButton(verticalLayoutWidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        verticalLayout->addWidget(pauseButton);

        resumeButton = new QPushButton(verticalLayoutWidget);
        resumeButton->setObjectName(QString::fromUtf8("resumeButton"));

        verticalLayout->addWidget(resumeButton);

        restartButton = new QPushButton(verticalLayoutWidget);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));

        verticalLayout->addWidget(restartButton);

        quitButton = new QPushButton(verticalLayoutWidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        verticalLayout->addWidget(quitButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 32));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        gameMenu = new QMenu(menubar);
        gameMenu->setObjectName(QString::fromUtf8("gameMenu"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(gameMenu->menuAction());
        fileMenu->addAction(loadAction);
        fileMenu->addAction(saveAction);
        fileMenu->addAction(quitAction);
        gameMenu->addAction(startAction);
        gameMenu->addAction(pauseAction);
        gameMenu->addAction(resumeAction);
        gameMenu->addAction(restartAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        loadAction->setText(QApplication::translate("MainWindow", "\350\275\275\345\205\245\346\270\270\346\210\217", nullptr));
        saveAction->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\270\270\346\210\217", nullptr));
        quitAction->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        startAction->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pauseAction->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234\346\270\270\346\210\217", nullptr));
        resumeAction->setText(QApplication::translate("MainWindow", "\347\273\247\347\273\255\346\270\270\346\210\217", nullptr));
        restartAction->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        groupBox->setTitle(QString());
        startButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        loadButton->setText(QApplication::translate("MainWindow", "\350\275\275\345\205\245\346\270\270\346\210\217", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\270\270\346\210\217", nullptr));
        pauseButton->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234\346\270\270\346\210\217", nullptr));
        resumeButton->setText(QApplication::translate("MainWindow", "\347\273\247\347\273\255\346\270\270\346\210\217", nullptr));
        restartButton->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        quitButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        fileMenu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        gameMenu->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
