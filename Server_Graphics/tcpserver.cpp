#include "tcpserver.h"
#include <thread.h>
tcpServer::tcpServer(QObject *parent) :
    QTcpServer(parent)
{
    server = this;
}

bool tcpServer::startServer()
{
    if(!this->listen(QHostAddress::Any,port))
    {
        return false; // se non e' partito
    }
    else
    {
        return true; // se e' partito
    }
}

void tcpServer::incomingConnection(int socketDescriptor)
{
    Thread *thread = new Thread(socketDescriptor,this);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}
