#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class tcpServer : public QTcpServer
{
    Q_OBJECT
public:
    unsigned int port;
    explicit tcpServer(QObject *parent = 0);
    bool startServer();
    QTcpServer *server;
protected:
    void incomingConnection(int socketDescriptor);
signals:

public slots:



};

#endif // TCPSERVER_H
