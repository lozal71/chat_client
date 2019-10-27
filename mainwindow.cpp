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
    connect(clientSocket,
            SIGNAL(sessionClosed(QString)),
            this,
            SLOT(logServerResponds(QString)));
    connect(ui->pbSendQuery,
            &QPushButton::clicked,
            this,
            &MainWindow::slotSendQuery);
    connect(this,
            SIGNAL(SendQuery(QString,QString)),
            clientSocket,
            SLOT(sendQueryToServer(QString, QString)));
    connect(clientSocket,
            SIGNAL(serverResponded(QString)),
            this,
            SLOT(logServerResponds(QString)));
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
    emit SendQuery(ui->cbxLogins->currentText(),
                   ui->cbxPasswords->currentText());
}

//void MainWindow::userAuth()
//{
//    id = ui->sbClientID->value();
//}

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



