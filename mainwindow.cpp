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
    setConnect();
    fullCbxLogins();
    fullCbxPasswords();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConnect()
{

    connect(ui->pbAuth, &QPushButton::clicked,
            this,  &MainWindow::slotSendQueryAuth);
    connect(this,  SIGNAL(SendQueryAuth(QJsonObject)),
            clientSocket, SLOT(slotSendQuery(QJsonObject)));
    connect(clientSocket,
            SIGNAL(serverResponded(QJsonObject)),
            this,
            SLOT(logServerResponds(QJsonObject)));
    connect(clientSocket,
            SIGNAL(sessionClosed(QJsonObject)),
            this,
            SLOT(logServerResponds(QJsonObject)));
}

void MainWindow::logServerResponds(QJsonObject joRespond)
{
    ui->teLog->insertPlainText("Respond from server:\n");
    for (const QString& eachKey : joRespond.keys())
    {
        ui->teLog->insertPlainText(joRespond.value(eachKey).toString());

    }
}


void MainWindow::slotSendQueryAuth()
{
    QJsonObject joTemp;
    joTemp.insert("login",ui->cbxLogins->currentText());
    joTemp.insert("pass",ui->cbxPasswords->currentText());
    emit SendQueryAuth(joTemp);
}


void MainWindow::fullCbxLogins()
{
    ui->cbxLogins->addItem("login1");
    ui->cbxLogins->addItem("login2");
    ui->cbxLogins->addItem("login3");
}

void MainWindow::fullCbxPasswords()
{
    ui->cbxPasswords->addItem("pass1");
    ui->cbxPasswords->addItem("pass2");
    ui->cbxPasswords->addItem("pass3");
}



