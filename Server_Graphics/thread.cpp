#include "thread.h"
#include <iostream>
using namespace std;
Thread::Thread(int ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescript = ID;
}

void Thread::run()
{
    socket = new QTcpSocket(server1.server->nextPendingConnection());
    if(!socket->setSocketDescriptor(this->socketDescript))
    {
        emit error(socket->error());
        return;
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    exec();
}

void Thread::readyRead()
{
    bool exit = false;
    bool error = false;
    QByteArray equazione,valoreX;
    QByteArray Data = socket->readAll();
    int i(0);
    // trovo inizio della trasmissione: ST
    // sposta indice finche non trova ST, se non trova mette errore
    do
    {
        if(Data[i] == 'S' && Data[i+1] == 'T')
        {
            exit = true;
        }
        else
        {
            i++;
            if(i>20)
            {
                exit = true;
                error = true;
            }
        }
    }while(!exit);
    exit = false;
    if(!error) // trovo la posizione della x
    { // trovo &x= e esco dal ciclo,altrimenti metto flag di errore
        do
        {
            if(Data[i] == '&' && Data[i+1] == 'x' && Data[i+2] == '=')
            {
                i += 3;
                exit = true;
            }
            else
            {
                i++;
                if(i > 100) //in caso se non trova '&x=' - ritorna al client ERRORE
                {
                    exit = true;
                    error = true;
                }
            }
        }while(!exit);
    }
    exit = false;
    if(!error) // qui copio il valore della X e equazione
    {
        do
        {
            do // Copio valore di x
            {
               valoreX += Data[i];
               i++;
            }while(Data[i] != '&' && Data[i+1] != 'y' && Data[i+2] != '=');
            x = valoreX.toDouble(); // converto in double;
            i += 3; // perche' '&y=' sono 3 caratteri, serve per saltare questi 3 caratteri
            do // copio equazione nel QByteArray e se trovo una x nella equazione
            {  //la sostituisco con x passata.
                if(Data[i] != 'x')
                {
                    equazione += Data[i];
                }
                else
                {
                    if(x < 0) // controllo per mettere le perentesi se il valore di x e' negativo
                    {
                        equazione += "(0";
                    }
                    equazione += QString::number(x);
                    if(x < 0)
                        equazione += ")";
                }
                i++;
            }while(Data[i] != '&' || Data[i+1] != 'c' || Data[i+2] != 's' || Data[i+3] != '=');
            i += 4; // per saltare '&cs='
            exit = true;
        }while(!exit);
    }
    exit = false;
    if(!error)
    {   // copio tutto il pachetto fino al valore di check sum
        // per fare poi checksum del paccetto ricevuto e vedere se
        // due checksum sono uguali
        char *toCheck = new char[i];
                for(int count =0; count < i;count++) // copio paccetto
                {
                    *toCheck = Data[count];
                }
                // copio valore di checksum;
                QByteArray checksum;
                int count(0);
                do
                {
                    checksum[count] = Data[i];
                    i++;
                    count++;
                }while(Data[i] != '&' || Data[i+1] != 'E' || Data[i+2] != 'T');
                // controllo se corrisponde checksum;
                if(strcmp(toCheck,checksum) == 0)
                {
                    error = true; // se non sono uguali mette flag di errore
                }
                delete[] toCheck;
    }
    if(!error) // qui parserizzo e trovo il risultato e ottengo la Y
    {
        if(equazione[0] == '-') // se valore e' con il meno avanti
        {                       // trasformo in "0-equazione"
            equazione.push_front("0");
        }
        pars.insert(equazione.data());
        pars.precedence();
        if(pars.precedence()==0)
        {
            pars.operators();
            y = pars.result();
            pars.output.clear();
        }
        else
        {
            error = true;
        }
    }
    Data.clear();
    if(!error) // dopo aver ottenuto la Y la rimando al client
    {
        Data += "y=";
        Data += QString::number(y).toLocal8Bit();
    }
    else // altrimenti mando errore
    {
        Data += "ERR";
    }
    socket->write(Data);
    socket->waitForBytesWritten(1);
    Data.clear();
}

void Thread::disconnected()
{
    socket->deleteLater();
    exit(0);
}
