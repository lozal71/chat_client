#ifndef PROTOCOLIN_H
#define POROTOCOLIN_H
#include <QDataStream>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>


enum setCodeCommand {ErrorMessage = 0, Auth = 1, SessionClosed = 2, NoConnect = 3};

class protocolIn: public QObject
{

public:
    //protocolIn();
    protocolIn(QTcpSocket *socket);
    setCodeCommand getCode();
    QJsonObject getData();
private:
    setCodeCommand codeCommand;
    QJsonObject joDataInput;
    QJsonObject getJsonObjectIN(QTcpSocket *socket);
};

#endif // POROTOCOLIN_H
