/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *chatBox;
    QLineEdit *textEdit;
    QListWidget *listUsers;
    QListWidget *listChannels;
    QLabel *label;
    QLabel *label_2;
    QPushButton *buttonConnect;
    QLabel *loginLabel;
    QLabel *ipLabel;
    QLineEdit *channelEdit;
    QPushButton *buttonChannel;
    QPushButton *buttonJoin;
    QPushButton *buttonQuit;
    QLabel *label_7;
    QPushButton *buttonLeave;
    QLineEdit *loginEdit;
    QLineEdit *ipEdit;
    QLineEdit *ipEdit_2;
    QLineEdit *ipEdit_3;
    QLineEdit *ipEdit_4;
    QLineEdit *ipEdit_5;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(551, 399);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        chatBox = new QTextEdit(centralWidget);
        chatBox->setObjectName(QString::fromUtf8("chatBox"));
        chatBox->setEnabled(true);
        chatBox->setGeometry(QRect(10, 10, 251, 211));
        chatBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chatBox->setReadOnly(true);
        textEdit = new QLineEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(10, 230, 251, 27));
        textEdit->setMaxLength(900);
        listUsers = new QListWidget(centralWidget);
        listUsers->setObjectName(QString::fromUtf8("listUsers"));
        listUsers->setGeometry(QRect(270, 30, 121, 141));
        listUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listChannels = new QListWidget(centralWidget);
        listChannels->setObjectName(QString::fromUtf8("listChannels"));
        listChannels->setEnabled(true);
        listChannels->setGeometry(QRect(410, 30, 121, 141));
        listChannels->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 9, 61, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(416, 7, 61, 20));
        buttonConnect = new QPushButton(centralWidget);
        buttonConnect->setObjectName(QString::fromUtf8("buttonConnect"));
        buttonConnect->setGeometry(QRect(30, 340, 81, 27));
        loginLabel = new QLabel(centralWidget);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));
        loginLabel->setGeometry(QRect(130, 280, 161, 21));
        ipLabel = new QLabel(centralWidget);
        ipLabel->setObjectName(QString::fromUtf8("ipLabel"));
        ipLabel->setGeometry(QRect(201, 311, 171, 21));
        channelEdit = new QLineEdit(centralWidget);
        channelEdit->setObjectName(QString::fromUtf8("channelEdit"));
        channelEdit->setEnabled(false);
        channelEdit->setGeometry(QRect(410, 210, 113, 27));
        channelEdit->setMaxLength(20);
        buttonChannel = new QPushButton(centralWidget);
        buttonChannel->setObjectName(QString::fromUtf8("buttonChannel"));
        buttonChannel->setEnabled(false);
        buttonChannel->setGeometry(QRect(410, 240, 111, 27));
        buttonJoin = new QPushButton(centralWidget);
        buttonJoin->setObjectName(QString::fromUtf8("buttonJoin"));
        buttonJoin->setEnabled(false);
        buttonJoin->setGeometry(QRect(410, 180, 111, 27));
        buttonQuit = new QPushButton(centralWidget);
        buttonQuit->setObjectName(QString::fromUtf8("buttonQuit"));
        buttonQuit->setGeometry(QRect(420, 330, 99, 27));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(130, 311, 16, 21));
        QFont font;
        font.setPointSize(14);
        label_7->setFont(font);
        buttonLeave = new QPushButton(centralWidget);
        buttonLeave->setObjectName(QString::fromUtf8("buttonLeave"));
        buttonLeave->setEnabled(false);
        buttonLeave->setGeometry(QRect(300, 180, 99, 27));
        loginEdit = new QLineEdit(centralWidget);
        loginEdit->setObjectName(QString::fromUtf8("loginEdit"));
        loginEdit->setEnabled(true);
        loginEdit->setGeometry(QRect(10, 280, 113, 27));
        loginEdit->setMaxLength(20);
        loginEdit->setEchoMode(QLineEdit::Normal);
        ipEdit = new QLineEdit(centralWidget);
        ipEdit->setObjectName(QString::fromUtf8("ipEdit"));
        ipEdit->setGeometry(QRect(10, 310, 31, 27));
        ipEdit_2 = new QLineEdit(centralWidget);
        ipEdit_2->setObjectName(QString::fromUtf8("ipEdit_2"));
        ipEdit_2->setGeometry(QRect(40, 310, 31, 27));
        ipEdit_3 = new QLineEdit(centralWidget);
        ipEdit_3->setObjectName(QString::fromUtf8("ipEdit_3"));
        ipEdit_3->setGeometry(QRect(70, 310, 31, 27));
        ipEdit_4 = new QLineEdit(centralWidget);
        ipEdit_4->setObjectName(QString::fromUtf8("ipEdit_4"));
        ipEdit_4->setGeometry(QRect(100, 310, 31, 27));
        ipEdit_5 = new QLineEdit(centralWidget);
        ipEdit_5->setObjectName(QString::fromUtf8("ipEdit_5"));
        ipEdit_5->setGeometry(QRect(140, 310, 51, 27));
        ipEdit_5->setMaxLength(6);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 551, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IRC Client", 0, QApplication::UnicodeUTF8));
        textEdit->setText(QApplication::translate("MainWindow", "Enter text here", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Users", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Channels", 0, QApplication::UnicodeUTF8));
        buttonConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        loginLabel->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        ipLabel->setText(QApplication::translate("MainWindow", "IP", 0, QApplication::UnicodeUTF8));
        channelEdit->setText(QApplication::translate("MainWindow", "Channel name", 0, QApplication::UnicodeUTF8));
        buttonChannel->setText(QApplication::translate("MainWindow", "Create channel", 0, QApplication::UnicodeUTF8));
        buttonJoin->setText(QApplication::translate("MainWindow", "Join channel", 0, QApplication::UnicodeUTF8));
        buttonQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", ":", 0, QApplication::UnicodeUTF8));
        buttonLeave->setText(QApplication::translate("MainWindow", "Leave channel", 0, QApplication::UnicodeUTF8));
        ipEdit->setInputMask(QApplication::translate("MainWindow", "000", 0, QApplication::UnicodeUTF8));
        ipEdit_2->setInputMask(QApplication::translate("MainWindow", "000", 0, QApplication::UnicodeUTF8));
        ipEdit_3->setInputMask(QApplication::translate("MainWindow", "000", 0, QApplication::UnicodeUTF8));
        ipEdit_4->setInputMask(QApplication::translate("MainWindow", "000", 0, QApplication::UnicodeUTF8));
        ipEdit_5->setInputMask(QApplication::translate("MainWindow", "000000", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
