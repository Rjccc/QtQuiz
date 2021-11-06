#include "cclient.h"

#include <QDebug>

cClient::cClient(QObject *parent, QString name)
    : QObject{parent}
{
    cSocket = new QTcpSocket;
    this->name = name;
}

void cClient::connectToServer()
{
    cSocket->connectToHost(QHostAddress::LocalHost,5050);
    sendAuthorisationMsg();
}

void cClient::connectToServer(QHostAddress addr, int port)
{

}

void cClient::sendAuthorisationMsg()
{
    cMsg_Auth auth;
    auth.name = this->name;
    QByteArray data;
    data.resize(sizeof(auth));
    memmove(data.data(),&auth,sizeof(auth));
    sendMsg(data);
}

void cClient::sendMsg(QByteArray data)
{
    cMsg_Header hdr;
    hdr.startMsg = 0x1212;
    hdr.len = data.size();
    QByteArray toSend;
    toSend.resize(sizeof(hdr));
    memmove(toSend.data(),&hdr,sizeof(hdr));
    toSend.append(data);
    if(cSocket->isOpen())
    {
        qDebug() << cSocket->write(toSend,toSend.size());
    }
}
