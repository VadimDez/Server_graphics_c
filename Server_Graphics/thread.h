#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include "tcpserver.h"
#include "server.h"
#include "parser.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    double x,y;
    tcpServer server1;
    Server mserv;
    parser pars;
    explicit Thread(int ID, QObject *parent = 0);
    void run();
    string tokenString;
signals:
    void error(QTcpSocket::SocketError socketerror);
public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    int socketDescript;
};
#endif // THREAD_H
