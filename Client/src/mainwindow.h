#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <strings.h>
#include <QString>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include "Protocols/Protocol.h"
#include "Protocols/EnterProtocol.h"
#include "Protocols/ListProtocol.h"
#include "Protocols/Message.h"
#include "Protocols/MessageProtocol.h"
#include "Protocols/StandardProtocol.h"
#include "Protocols/ErrorProtocol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void connectToServer();
    void sendMsg();
    void quit();
    void leaveChannel();
    void selectionChange();
    void joinChannel();
    void createChannel();
    void listeningLoop();
    void sucConnect();
    void sockError(QAbstractSocket::SocketError);

private:
    Ui::MainWindow *ui;
    QTcpSocket* socket;
    QHostAddress host;
    QString name, channel, ip;
    bool logDataOk, connected = false, onChannel = false;
    Message msg;
    char buffer[1024];
    enum phase {LOG, CHAN_CR, CHAN_JOIN, CHAN_LV, UNSET };
    phase lastPhase = UNSET;
    QByteArray qBytes;
};

#endif // MAINWINDOW_H
