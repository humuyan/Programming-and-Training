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
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *startButton;
    QPushButton *callLandlordButton;
    QPushButton *noCallButton;
    QLabel *rightLabel;
    QLabel *leftLabel;
    QLabel *myLabel;
    QPushButton *exitButton;
    QLabel *leftRestLabel;
    QLabel *rightRestLabel;
    QPushButton *playButton;
    QPushButton *noPlayButton;
    QPushButton *restartButton;
    QLabel *leftIdentityLabel;
    QLabel *rightIdentityLabel;
    QLabel *myIdentityLabel;
    QLabel *myRestLabel;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(720, 0, 81, 36));
        callLandlordButton = new QPushButton(centralwidget);
        callLandlordButton->setObjectName(QString::fromUtf8("callLandlordButton"));
        callLandlordButton->setGeometry(QRect(280, 210, 80, 36));
        noCallButton = new QPushButton(centralwidget);
        noCallButton->setObjectName(QString::fromUtf8("noCallButton"));
        noCallButton->setGeometry(QRect(420, 210, 80, 36));
        rightLabel = new QLabel(centralwidget);
        rightLabel->setObjectName(QString::fromUtf8("rightLabel"));
        rightLabel->setGeometry(QRect(690, 110, 80, 21));
        rightLabel->setAlignment(Qt::AlignCenter);
        leftLabel = new QLabel(centralwidget);
        leftLabel->setObjectName(QString::fromUtf8("leftLabel"));
        leftLabel->setGeometry(QRect(60, 120, 80, 21));
        leftLabel->setAlignment(Qt::AlignCenter);
        myLabel = new QLabel(centralwidget);
        myLabel->setObjectName(QString::fromUtf8("myLabel"));
        myLabel->setGeometry(QRect(350, 180, 80, 21));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(720, 40, 81, 36));
        leftRestLabel = new QLabel(centralwidget);
        leftRestLabel->setObjectName(QString::fromUtf8("leftRestLabel"));
        leftRestLabel->setGeometry(QRect(60, 160, 80, 21));
        leftRestLabel->setAlignment(Qt::AlignCenter);
        rightRestLabel = new QLabel(centralwidget);
        rightRestLabel->setObjectName(QString::fromUtf8("rightRestLabel"));
        rightRestLabel->setGeometry(QRect(690, 150, 80, 21));
        rightRestLabel->setAlignment(Qt::AlignCenter);
        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(260, 260, 80, 36));
        noPlayButton = new QPushButton(centralwidget);
        noPlayButton->setObjectName(QString::fromUtf8("noPlayButton"));
        noPlayButton->setGeometry(QRect(430, 260, 80, 36));
        restartButton = new QPushButton(centralwidget);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));
        restartButton->setGeometry(QRect(330, 300, 106, 30));
        leftIdentityLabel = new QLabel(centralwidget);
        leftIdentityLabel->setObjectName(QString::fromUtf8("leftIdentityLabel"));
        leftIdentityLabel->setGeometry(QRect(60, 200, 80, 21));
        leftIdentityLabel->setAlignment(Qt::AlignCenter);
        rightIdentityLabel = new QLabel(centralwidget);
        rightIdentityLabel->setObjectName(QString::fromUtf8("rightIdentityLabel"));
        rightIdentityLabel->setGeometry(QRect(690, 200, 80, 21));
        rightIdentityLabel->setAlignment(Qt::AlignCenter);
        myIdentityLabel = new QLabel(centralwidget);
        myIdentityLabel->setObjectName(QString::fromUtf8("myIdentityLabel"));
        myIdentityLabel->setGeometry(QRect(680, 460, 80, 21));
        myIdentityLabel->setAlignment(Qt::AlignCenter);
        myRestLabel = new QLabel(centralwidget);
        myRestLabel->setObjectName(QString::fromUtf8("myRestLabel"));
        myRestLabel->setGeometry(QRect(680, 490, 80, 21));
        myRestLabel->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 32));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\277\236\346\216\245", nullptr));
        callLandlordButton->setText(QApplication::translate("MainWindow", "\345\217\253\345\234\260\344\270\273", nullptr));
        noCallButton->setText(QApplication::translate("MainWindow", "\344\270\215\345\217\253", nullptr));
        rightLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        leftLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        myLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        exitButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        leftRestLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        rightRestLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        playButton->setText(QApplication::translate("MainWindow", "\345\207\272\347\211\214", nullptr));
        noPlayButton->setText(QApplication::translate("MainWindow", "\344\270\215\345\207\272", nullptr));
        restartButton->setText(QApplication::translate("MainWindow", "\345\206\215\347\216\251\344\270\200\346\254\241", nullptr));
        leftIdentityLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        rightIdentityLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        myIdentityLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        myRestLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
