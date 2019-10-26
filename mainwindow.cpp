#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect (socket, &QTcpSocket::readyRead,
             this, &MainWindow::clientReadData);
    connect(ui->pbProfile1, &QPushButton::clicked,
            this, &MainWindow::buttonClick1);
    connect(ui->pbProfile2, &QPushButton::clicked,
            this, &MainWindow::buttonClick2);
    connect(socket,&QTcpSocket::disconnected,
            this,&MainWindow::connectClosed);
    connect(this, &MainWindow::connectClosed,
            this,&MainWindow::removeSession);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clientReadData()
{
    protocolIn MessageIn(socket);
    QString messageFromServer;
    messageFromServer = MessageIn.getData();
    ui->teLog->insertPlainText(messageFromServer+"\n");
   // ui->leLogin->setText(messageFromServer);
    qDebug() << "client read from server " << messageFromServer;
}

void MainWindow::buttonClick1()
{
    if (socket->state() == QTcpSocket::UnconnectedState){
        socket->connectToHost("127.0.0.1", 6000);
    }
    QByteArray message = "{\"1\": 1, \"2\":\"user1\"}";
    qDebug() << message;
    if (socket->waitForConnected()){
        qDebug() <<"We have connect to server!!! send message";
        protocolOut MessageOut(message);
        socket->write(MessageOut.getMessageToClient());
    }
    else{
        qDebug() << "client say - no connect";
    }
}

void MainWindow::buttonClick2()
{
    if (socket->state() == QTcpSocket::UnconnectedState){
        socket->connectToHost("127.0.0.1", 6000);
    }
    QByteArray message = "{\"1\": 1, \"2\":\"user2\"}";
    qDebug() << message;
    if (socket->waitForConnected()){
        qDebug() <<"We have connect to server!!! I want to send message";
        protocolOut MessageOut(message);
        socket->write(MessageOut.getMessageToClient());
    }
    else{
        qDebug() << "client say - no connect";
    }
}

void MainWindow::removeSession()
{
     ui->teLog->insertPlainText("Connect closed \n");
}



