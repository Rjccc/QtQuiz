#ifndef CCLIENT_H
#define CCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

#define SERVER_ADDR = "localhost"
#define SERVER_PORT = 5050

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
    explicit cClient(QObject *parent = nullptr, QString name = QString());
    void connectToServer();

signals:
    void sConnected();
    void sDisconnected();
    void sReconnected();
private:
    QTcpSocket *cSocket = NULL;
    QString name;

    void connectToServer(QHostAddress,int); //addr , port
    void sendAuthorisationMsg();
    void sendMsg(QByteArray);
};

#endif // CCLIENT_H
