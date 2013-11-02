#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpSocket>
#include <tcpserver.h>
namespace Ui {
    class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    tcpServer serv;
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    void on_startServerButton_clicked();

    void on_port_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Server *ui;
};

#endif // SERVER_H
