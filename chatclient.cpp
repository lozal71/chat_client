#include "chatclient.h"
#include "protocol_in.h"
#include "protocol_out.h"

chatClient::chatClient()
{
    socket = new QTcpSocket();

    connect (socket, &QTcpSocket::readyRead,
             this, &chatClient::clientReadData);
    connect(socket,&QTcpSocket::disconnected,
            this, &chatClient::SessionClose);
}

void chatClient::clientReadData()
{
    QJsonObject tempObj;
    protocolIn MessageIn(socket);
    tempObj = MessageIn.getData();
    id = tempObj.value("1").toInt();
    respondFromServer = tempObj.value("2").toString();
    emit serverResponded(respondFromServer);
    qDebug() << "client read from server  id" << id;
}

void chatClient::setUserID()
{

}

void chatClient::sendQueryToServer(QString queryString)
{
    if (socket->state() == QTcpSocket::UnconnectedState){
        socket->connectToHost("127.0.0.1", 6000);
    }
    QJsonObject queryClient;
    queryClient.insert("1",1);
    queryClient.insert("2",queryString);
    QJsonDocument doc(queryClient);
    QByteArray message = doc.toJson(QJsonDocument::Compact);
    //QByteArray message = "{\"1\": 1, \"2\":\"login1\"}";
    qDebug() << message;
    if (socket->waitForConnected()){
        //qDebug() <<"We have connect to server!!! send message";
        protocolOut MessageOut(message);
        socket->write(MessageOut.getMessageToClient());
    }
    else{
        //qDebug() << "client say - no connect";
        emit serverResponded("no connection to server \n");
    }
}

void chatClient::SessionClose()
{
    emit sessionClosed("session closed \n");
}

