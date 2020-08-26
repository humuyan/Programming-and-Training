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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBar>
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
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *startButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QPushButton *restartButton;
    QPushButton *quitButton;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *gameMenu;
    QToolBar *toolBar;

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
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        startButton = new QPushButton(groupBox);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy1);
        startButton->setMinimumSize(QSize(0, 36));

        verticalLayout->addWidget(startButton);

        loadButton = new QPushButton(groupBox);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        sizePolicy1.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(loadButton);

        saveButton = new QPushButton(groupBox);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setEnabled(true);
        sizePolicy1.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(saveButton);

        pauseButton = new QPushButton(groupBox);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        sizePolicy1.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pauseButton);

        resumeButton = new QPushButton(groupBox);
        resumeButton->setObjectName(QString::fromUtf8("resumeButton"));
        sizePolicy1.setHeightForWidth(resumeButton->sizePolicy().hasHeightForWidth());
        resumeButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(resumeButton);

        restartButton = new QPushButton(groupBox);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));
        sizePolicy1.setHeightForWidth(restartButton->sizePolicy().hasHeightForWidth());
        restartButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(restartButton);

        quitButton = new QPushButton(groupBox);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));
        sizePolicy1.setHeightForWidth(quitButton->sizePolicy().hasHeightForWidth());
        quitButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(quitButton);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lcdNumber = new QLCDNumber(groupBox);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        verticalLayout->addWidget(lcdNumber);


        horizontalLayout->addWidget(groupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 32));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        gameMenu = new QMenu(menubar);
        gameMenu->setObjectName(QString::fromUtf8("gameMenu"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(gameMenu->menuAction());
        fileMenu->addAction(loadAction);
        fileMenu->addAction(saveAction);
        fileMenu->addAction(quitAction);
        gameMenu->addAction(startAction);
        gameMenu->addAction(pauseAction);
        gameMenu->addAction(resumeAction);
        gameMenu->addAction(restartAction);
        toolBar->addAction(startAction);
        toolBar->addAction(loadAction);
        toolBar->addAction(saveAction);
        toolBar->addAction(pauseAction);
        toolBar->addAction(resumeAction);
        toolBar->addAction(restartAction);
        toolBar->addAction(quitAction);

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
        label->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\357\274\232", nullptr));
        fileMenu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        gameMenu->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
