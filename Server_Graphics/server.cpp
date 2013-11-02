#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->pushButton->setVisible(false);
}

Server::~Server()
{
    delete ui;
}
// funzione per la partenza del server
void Server::on_startServerButton_clicked()
{
    ui->port->setDisabled(true);
    if(serv.startServer())
    {
        ui->stato->setText("Server e' in ascolto");
        ui->startServerButton->setVisible(false);
        ui->pushButton->setVisible(true);
    }
    else
    {
        ui->stato->setText("Server non e' partito");
    }
}

void Server::on_port_valueChanged(int arg1)
{
    serv.port = arg1;
}
// Quando viene premuto il tasto dello Stop
void Server::on_pushButton_clicked()
{
    serv.server->close();
    ui->stato->setText("Server spento.");
    ui->pushButton->setVisible(false);
    ui->startServerButton->setVisible(true);
    ui->port->setEnabled(true);
}
