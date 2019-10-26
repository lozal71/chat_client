#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientSocket = new chatClient();
    createUsersList();
    QString respond;
    connect(clientSocket, SIGNAL(sessionClosed(QString)),
            this, SLOT(logServerResponds(QString)));
    connect(ui->pbSendQuery,&QPushButton::clicked,
            this, &MainWindow::slotSendQuery);
    connect(this,SIGNAL(SendQuery(QString)),
            clientSocket, SLOT(sendQueryToServer(QString)));
    connect(clientSocket,
            SIGNAL(serverResponded(QString)),
            this,
            SLOT(logServerResponds(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::logServerResponds(QString stringRespond)
{
    ui->teLog->insertPlainText(stringRespond + "\n");
}

void MainWindow::logSessionClose()
{
    ui->teLog->insertPlainText("session closed \n");
}

void MainWindow::slotSendQuery()
{
    emit SendQuery(ui->cbxLogins->currentText());
}

//void MainWindow::userAuth()
//{
//    id = ui->sbClientID->value();
//}

void MainWindow::createUsersList()
{
    ui->cbxLogins->addItem("login1");
    ui->cbxLogins->addItem("login3");
    ui->cbxLogins->addItem("login2");
}



