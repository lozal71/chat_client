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
public slots:
    void logServerResponds(QString stringRespond);
    void logSessionClose();
    void slotSendQuery();
private:
    Ui::MainWindow *ui;
    chatClient * clientSocket;
//    QString datafromServer;
//    int id;
//    void clientReadData();
   // void getReplayFromServer();
    //void removeSession();
//    void userAuth();

    void createUsersList();
signals:
    void SendQuery(QString param);
//    void connectClosed();
};

#endif // MAINWINDOW_H
