#ifndef CSERVER_H
#define CSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#pragma pack(1)

typedef char           CHAR;
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned int   DWORD;
typedef short          INT16;
typedef unsigned int   UINT;
typedef int            INT32;
typedef double         DOUBLE;

#define cMsgStartMsg 0x1212;

struct cMsg_Header
{
    WORD    startMsg;               //have to be equal to 1212
    WORD    len;                    //information part length
};
typedef cMsg_Header cMsg_Header;

struct cMsg_Auth
{
    WORD    typeOfMsg = 0x01;
    QString name;
};
typedef cMsg_Auth cMsg_Auth;

#pragma pack()

class cClient : public QObject
{
    Q_OBJECT
public:
    explicit cClient(QObject *parent = nullptr);
};

class cServer : public QObject
{
    Q_OBJECT
public:
    explicit cServer(QObject *parent = nullptr);
    void startServer();
    void stopServer();
    bool isStarted() { return cTcpServer->isListening(); }

signals:
    void sStarted();

private:
    QTcpServer *cTcpServer = NULL;
    QList<QTcpSocket*> rawClients;
    QList<cClient*> clients;

    bool checkMsg(QTcpSocket*);
private slots:
    void newClient();
    void rcvData();
};

#endif // CSERVER_H
