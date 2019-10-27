#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "protocol_in.h"
#include "protocol_out.h"
#include "chatclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setConnect();
public slots:
    void logServerResponds(QString stringRespond);
    void logSessionClose();
    void slotSendQuery();
private:
    Ui::MainWindow *ui;
    chatClient * clientSocket;
    void fullCbxLogins();
    void fullCbxPasswords();
signals:
    void SendQuery(QString param1, QString param2);
};

#endif // MAINWINDOW_H
