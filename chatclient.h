#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QTcpSocket>


class chatClient : public QObject
{
    Q_OBJECT
public:
    chatClient();
public slots:
    void sendQueryToServer(QString loginString, QString passString);
    void SessionClose();
private:
    QTcpSocket * socket;
    QString respondFromServer;
    int id;
    void clientReadData();
    void getReplayFromServer();
    void setUserID();

signals:
    void sessionClosed(QString respondString);
    void serverResponded(QString respondString);
};

#endif // CHATCLIENT_H
