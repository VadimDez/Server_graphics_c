#include <QtCore/QCoreApplication>
#include <iostream>
#include <malloc.h>
#include <stdio.h>
using namespace std;

struct campi
{
       int codice;
       char descrizione[20];
};

struct dati
{
    int info;
    struct dati *dx, *sx;
};

struct nodo
{
     dati info;
     struct nodo *sx,*dx;
};

struct dati* radice;

void inizializza(void);
void operazione(char testata[]);
struct nodo* generanodo(void);
struct nodo* trovanodo(dati dato, struct nodo *p);
int confrontadati(dati dato1, dati dato2);
void creaalbero(void);
int leggidati(dati *d);
void stampadato(dati d);
void stamparicorsiva(struct nodo *p);
void stampaAlbero(void);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    dati radice;
    inizializza();
    int scelta;
    do
    {
        do
        {
            printf("1. Creazione di un albero\n");
            printf("2. Stampa ordina\n");
            printf("3. Fine lavoro");
            cin >> scelta;
        }while(scelta <1 || scelta >> 3);
        switch(scelta)
        {
        case 1:
            creaalbero();
            break;
        case 2:
            stampaAlbero();
            break;
        }
    }while(scelta != 3);
    system("PAUSE");
    return a.exec();
}

struct nodo *generanodo()
{
    struct nodo *p = NULL;
    dati d;
    int fine;
    fine = leggidati(&d);
    while(fine!=0)
    {
        p = trovanodo(d,p);
        fine = leggidati(&d);
    }
    return p;
}

struct nodo *trovanodo (dati dato, struct nodo *p)
{
    if (p==NULL)
    {
        p = (struct nodo*) malloc (sizeof(struct nodo));
        p->info=dato;
        p->sx=NULL;
        p->dx=NULL;
    }
    else
    {
        switch (confrontadati(dato, p->info))
        {
        case 1:
                p->sx=trovanodo(dato, p->sx);
            break;
        case 2:
            p->dx=trovanodo(dato, p->dx);
            break;
        case 3:
            cout<< "Dato gia presente, non inserito."<<endl;
        }
    }
    return p;
}

void inizializza ()
{
    radice = NULL;
}

int confrontadati(dati dato1, dati dato2)
{
    if(dato1.info<dato2.info)
    {
        return 1;
    }
    else if(dato1.info>dato2.info)
    {
        return 2;
    }
    else if(dato1.info==dato2.info)
    {
        return 3;
    }
}

void stamparicorsiva(struct dati *p)
{
    if(p!=NULL)
    {
        stamparicorsiva(p->sx);
        leggidati(p);
        stamparicorsiva(p->dx);
    }
}

void creaalbero()
{
    cout << "Inserimento dati:"<< endl;
    radice = generanodo();
}

void stampaAlbero()
{
    cout << "Stampa ordinata:"<< endl;
    stamparicorsiva(radice);
}

int leggidati(dati *d)
{
    cout << d->info << endl;
    return 0;
}
