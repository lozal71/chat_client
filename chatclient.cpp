#include "chatclient.h"


chatClient::chatClient()
{
    socket = new QTcpSocket();

    connect (socket, &QTcpSocket::readyRead,
             this, &chatClient::readRespond);
    connect(socket,&QTcpSocket::disconnected,
            this, &chatClient::slotSessionClose);
}

void chatClient::readRespond()
{

    protocolIn MessageIn(socket);
    joRespond = MessageIn.getData();
    emit serverResponded(joRespond);
    //qDebug() << "client read from server  id" << id;
}


void chatClient::slotSendQuery(QJsonObject joParam)
{
    if (socket->state() == QTcpSocket::UnconnectedState){
        socket->connectToHost("127.0.0.1", 6000);
    }
    QJsonObject queryClient;
    queryClient.insert("codeCommand",Auth);
    queryClient.insert("joDataInput",joParam);
    QJsonDocument doc(queryClient);
    QByteArray baMessage = doc.toJson(QJsonDocument::Compact);
    //qDebug() << message;
    if (socket->waitForConnected()){
        //qDebug() <<"We have connect to server!!! send message";
        protocolOut MessageOut(baMessage);
        socket->write(MessageOut.getMessageToClient());
    }
    else{
        //qDebug() << "client say - no connect";
        joRespond.insert("codeCommand",NoConnect);
        joRespond.insert("joDataInput","no connection to server");
        emit serverResponded(joRespond);
    }
}

void chatClient::slotSessionClose()
{
    joRespond.insert("codeCommand",SessionClosed);
    joRespond.insert("joDataInput","session closed");
    emit sessionClosed(joRespond);
}

