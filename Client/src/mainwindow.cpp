#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>
#include <QTime>

bool testString(QString str) {
    if(str.contains("~"))
    {
        return false;
    }
    else {
        if(str.isEmpty()) {
            return false;
        }
            else {
                return true;
        }
    }
}

void copyToList(Protocol *temp, QListWidget *list) {
    list->clear();
    ListProtocol *ltemp;
    ltemp = dynamic_cast<ListProtocol*>(temp);
    int size = ltemp->getSize();
    for(int x = 0; x < size; x++) {
        list->addItem(QString::fromStdString(ltemp->getList(x)));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Setting up connections
    connect(ui->buttonConnect, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->buttonJoin, SIGNAL(clicked()), this, SLOT(joinChannel()));
    connect(ui->buttonChannel, SIGNAL(clicked()), this, SLOT(createChannel()));
    connect(ui->buttonLeave, SIGNAL(clicked()), this, SLOT(leaveChannel()));
    connect(ui->listChannels, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChange()));
    connect(ui->textEdit, SIGNAL(returnPressed()), this, SLOT(sendMsg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToServer() {
    //Parse login to check for ~ and see if not empty
    logDataOk = true;
    name = ui->loginEdit->text();
    if(!testString(name))
    {
        ui->loginEdit->setStyleSheet("QLineEdit#loginEdit { background-color: yellow }");
        ui->loginLabel->setText("Incorrect login.");
        logDataOk = false;
    }
    else {
        ui->loginEdit->setStyleSheet("QLineEdit#loginEdit { background-color: white }");
        ui->loginLabel->setText("Login");
    }
    //Parsing and checking IP edit
    if(ui->ipEdit->text().isEmpty() ||
            ui->ipEdit_2->text().isEmpty() ||
            ui->ipEdit_3->text().isEmpty() ||
            ui->ipEdit_4->text().isEmpty() ||
            ui->ipEdit_5->text().isEmpty()) {
        ui->ipEdit->setStyleSheet("QLineEdit#ipEdit { background-color: yellow }");
        ui->ipEdit_2->setStyleSheet("QLineEdit#ipEdit_2 { background-color: yellow }");
        ui->ipEdit_3->setStyleSheet("QLineEdit#ipEdit_3 { background-color: yellow }");
        ui->ipEdit_4->setStyleSheet("QLineEdit#ipEdit_4 { background-color: yellow }");
        ui->ipEdit_5->setStyleSheet("QLineEdit#ipEdit_5 { background-color: yellow }");
        ui->ipLabel->setText("IP; cannot be left empty");
        logDataOk = false;

    }
    else {
        ui->ipEdit->setStyleSheet("QLineEdit#ipEdit { background-color: white }");
        ui->ipEdit_2->setStyleSheet("QLineEdit#ipEdit_2 { background-color: white }");
        ui->ipEdit_3->setStyleSheet("QLineEdit#ipEdit_3 { background-color: white }");
        ui->ipEdit_4->setStyleSheet("QLineEdit#ipEdit_4 { background-color: white }");
        ui->ipEdit_5->setStyleSheet("QLineEdit#ipEdit_5 { background-color: white }");
        ui->ipLabel->setText("IP");
    }
    //Socket connection
    if(logDataOk) {
        ip = ui->ipEdit->text() + "." + ui->ipEdit_2->text() + "." + ui->ipEdit_3->text() + "." + ui->ipEdit_4->text();
        host = QHostAddress(ip);
        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(connected()), this, SLOT(sucConnect()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sockError(QAbstractSocket::SocketError)));
        connect(socket, SIGNAL(readyRead()), this, SLOT(listeningLoop()));
        socket->connectToHost(host, ui->ipEdit_5->text().toShort());
    }
}

void MainWindow::sendMsg() {
    //StandardProtocol sptcl(SEND, ui->textEdit->text().toStdString());
    StandardProtocol sptcl(SEND, ui->textEdit->text().toUtf8().constData());
    msg.packMsg(&sptcl);
    socket->write(msg.getBuffer());
    socket->waitForBytesWritten();
    msg.clearBuffer();
    ui->textEdit->clear();
}

void MainWindow::quit() {
    if(connected) {
        Protocol ptcl(LOGOFF);
        msg.packMsg(&ptcl);
        socket->write(msg.getBuffer());
        socket->waitForBytesWritten();
        socket->close();
        msg.clearBuffer();
    }
    this->close();
}

void MainWindow::selectionChange() {
    ui->buttonJoin->setEnabled(true);
}

void MainWindow::leaveChannel() {
    onChannel = false;
    Protocol ptcl(LEAVE);
    msg.packMsg(&ptcl);
    socket->write(msg.getBuffer());
    socket->waitForBytesWritten();
    msg.clearBuffer();
    ui->chatBox->setText("Channel left.\n");
    ui->buttonChannel->setEnabled(true);
    ui->buttonJoin->setEnabled(true);
    ui->textEdit->setEnabled(false);
    ui->buttonLeave->setEnabled(false);
    lastPhase = CHAN_LV;
    ui->listUsers->clear();
}

void MainWindow::joinChannel() {
    if(!ui->listChannels->selectedItems().isEmpty()) {
        channel = ui->listChannels->selectedItems().first()->text();
        EnterProtocol eptcl(JOIN, channel.toStdString());
        msg.packMsg(&eptcl);
        socket->write(msg.getBuffer());
        socket->waitForBytesWritten();
        msg.clearBuffer();
        ui->chatBox->setText("Attempting to join channel " + channel + "...\n");
        lastPhase = CHAN_JOIN;
    }
}

void MainWindow::createChannel() {
    channel = ui->channelEdit->text();
    if(!testString(channel)) {
        ui->channelEdit->setStyleSheet("QLineEdit#channelEdit { background-color: yellow }");
    }
    else {
        ui->channelEdit->setStyleSheet("QLineEdit#channelEdit { background-color: white }");
        EnterProtocol eptcl(CREATE, channel.toStdString());
        msg.packMsg(&eptcl);
        socket->write(msg.getBuffer());
        socket->waitForBytesWritten();
        msg.clearBuffer();
        ui->chatBox->setText("Attempting to create channel " + channel + "...\n");
        lastPhase = CHAN_CR;
    }
}

void MainWindow::listeningLoop() {
    while(socket->canReadLine()) {
        bzero((char *) buffer, sizeof(buffer));
        socket->readLine(buffer, 1024);
        strcpy(msg.getBuffer(), buffer);
        Protocol *temp = msg.unpackMsg();
        switch(temp->getId()) {
        case USERSLIST:
            copyToList(temp, ui->listUsers);
            break;
        case ROOMSLIST:
            copyToList(temp, ui->listChannels);
            if(ui->listChannels->selectedItems().isEmpty())
                ui->buttonJoin->setEnabled(false);
            break;
        case MSG:
            MessageProtocol *mtemp;
            mtemp = dynamic_cast<MessageProtocol*>(temp);
            qBytes = mtemp->getContent().c_str();
            ui->chatBox->append("[" + QString::fromStdString(mtemp->getTime()) + "]" +
                                QString::fromStdString(mtemp->getName()) + ": " +
                                QString::fromUtf8(qBytes.data(), qBytes.size()) + "\n");
            break;
        case ACK:
            switch(lastPhase) {
            case LOG:
                ui->buttonChannel->setEnabled(true);
                ui->buttonConnect->setEnabled(false);
                ui->channelEdit->setEnabled(true);
                lastPhase = UNSET;
                break;
            case CHAN_CR:
                ui->chatBox->append("Successfully made channel " + channel +".\n");
                ui->textEdit->setEnabled(true);
                ui->buttonLeave->setEnabled(true);
                ui->buttonChannel->setEnabled(false);
                ui->buttonJoin->setEnabled(false);
                onChannel = true;
                lastPhase = UNSET;
                break;
            case CHAN_JOIN:
                ui->chatBox->append("Successfully joined channel " + channel +".\n");
                ui->textEdit->setEnabled(true);
                ui->buttonLeave->setEnabled(true);
                ui->buttonChannel->setEnabled(false);
                ui->buttonJoin->setEnabled(false);
                onChannel = true;
                lastPhase = UNSET;
                break;
            case CHAN_LV:
                ui->chatBox->setText("Channel left.\n");
                break;
            case UNSET:
                ui->chatBox->append("ACK received while phase being UNSET.\n");
                break;
            default:
                ui->chatBox->append("ACK received while phase being unknown.\n");
            }
            break;
        case ERROR:
            ErrorProtocol *eptcl;
            eptcl = dynamic_cast<ErrorProtocol*>(temp);
            switch(eptcl->getError()) {
            case LOGINUSER:
                ui->chatBox->setText("Connection failed. Error received: " + QString::fromStdString(eptcl->getText()));
                connected = false;
                socket->close();
                break;
            case CREATEROOM:
                ui->chatBox->append("Failed to create channel " + channel + ". Reason: " + QString::fromStdString(eptcl->getText()) + "\n");
                break;
            case JOINROOM:
                ui->chatBox->append("Failed to join channel " + channel + ". Reason: " + QString::fromStdString(eptcl->getText()) + "\n");
                break;
            case WRONGMSG:
                ui->chatBox->append("Wrong message error received: " + QString::fromStdString(eptcl->getText()) + "\n");
                break;
            default:
                ui->chatBox->append("Received unknown error: " + QString::fromStdString(eptcl->getText()) + "\n");
            }
            break;
        default:
            ui->chatBox->setText("Unknown message received.\n");
        }
    }
}

void MainWindow::sucConnect() {
    connected = true;
    EnterProtocol ptcl(LOGIN, name.toStdString());
    msg.packMsg(&ptcl);
    ui->chatBox->setText("Connecting to server " + ip + " as user " + name + "...\n");
    socket->write(msg.getBuffer());
    socket->waitForBytesWritten();
    msg.clearBuffer();
    lastPhase = LOG;
}

void MainWindow::sockError(QAbstractSocket::SocketError err) {
    ui->chatBox->setText("Connection error: " + err);
}
