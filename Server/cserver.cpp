#include "cserver.h"

#include <QDebug>

cServer::cServer(QObject *parent)
    : QObject{parent}
{
    cTcpServer = new QTcpServer();
}

void cServer::startServer()
{
    cTcpServer->listen(QHostAddress::LocalHost,5050);
    qDebug() << cTcpServer->isListening();
    connect(cTcpServer, SIGNAL(newConnection()),this,SLOT(newClient()));
}

void cServer::stopServer()
{
    if(cTcpServer->isListening())
    {
        cTcpServer->close();
    }
}

void cServer::newClient()
{
    QTcpSocket *client = cTcpServer->nextPendingConnection();
    connect(client,SIGNAL(readyRead()),this,SLOT(rcvData()));
    rawClients << client;
}

void cServer::rcvData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if(rawClients.contains(client))
    {
        //if its not authorised client
        while(checkMsg(client))
        {
            cMsg_Header hdr;
            QByteArray buf = QByteArray(client->read(sizeof(cMsg_Header)),(int)sizeof(cMsg_Header));
            memset(&hdr,0,sizeof(cMsg_Header));
            memcpy(&hdr,buf,sizeof(cMsg_Header));
            buf.clear();
            buf.resize(hdr.len);
            qDebug() << hdr.len << client->bytesAvailable();
            QByteArray t;
            t = client->read(hdr.len);
            cMsg_Auth auth;
            memset(&auth,0,sizeof(cMsg_Auth));
            memcpy(&auth,t,sizeof(cMsg_Auth));

            qDebug() << auth.typeOfMsg << auth.name;
        }
    }
}

bool cServer::checkMsg(QTcpSocket *client)
{
    QByteArray tmp = QByteArray(client->peek(sizeof(cMsg_Header)),(int)sizeof(cMsg_Header));
    if(!tmp.contains(0x1212))
        return false;

    cMsg_Header hdr;
    memset(&hdr,0,sizeof(cMsg_Header));
    memcpy(&hdr,tmp,sizeof(cMsg_Header));

    if(client->bytesAvailable() < sizeof(cMsg_Header) + hdr.len)
        return false;

    return true;

}
