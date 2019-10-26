#ifndef PROTOCOLIN_H
#define POROTOCOLIN_H
#include <QDataStream>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

class protocolIn: public QObject
{
public:
    protocolIn();
    protocolIn(QTcpSocket *socket);
    int getCode();
    QJsonObject getData();
private:
    int codeCommand;
    QJsonObject jsonData;
    QByteArray getMessage(QTcpSocket *socket);
};

#endif // POROTOCOLIN_H
