#include <QtCore/QCoreApplication>
#include <iostream>
#include <windows.h>
using namespace std;

struct albero
{
    int dato;
    struct albero *min;
    struct albero *max;
    albero();
};

albero::albero()
{
    dato = NULL;
    min = NULL;
    max = NULL;
}

int menu();
void scelta(int &sceltaMenu, bool &exit, albero *ptr);
void minimo(albero *ptr);
void massimo(albero *ptr);
void inserimento(albero *ptr, int valore);
void search(int valore, albero *ptr);
void stampapreorder(albero *ptr);
void stampapostorder(albero *ptr);
void inorder(albero *ptr);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    albero *ptr;
    ptr = new albero;
    int sceltaMenu;
    bool exit = true;
    while(exit)
    {
        system("CLS");
        sceltaMenu = menu();
        scelta(sceltaMenu, exit, ptr);
        system("PAUSE");
    }
    return 0;
}

int menu()
{
    int scelta;
    do
    {
        cout << "[1] per inserimento\n";
        cout << "[2] per la ricerca\n";
        cout << "[3] per il max\n";
        cout << "[4] per il min\n";
        cout << "[5] per la stampa preorder\n";
        cout << "[6] per la stampa postorder\n";
        cout << "[7] per la stampa inorder\n";
        cout << "[8] per uscire\n";
        cin >> scelta;
    }while(scelta < 1 || scelta >8);
    return scelta;
}

void scelta(int &sceltaMenu, bool &exit, albero *ptr)
{
    int valore;
    switch(sceltaMenu)
    {
    case 1:
        cout << "Inserisci dato: ";
        cin >> valore;
        inserimento(ptr, valore);
        break;
    case 2:
        cout << "Inserire valore da cercare: \n";
        cin >> valore;
        search(valore, ptr);
        break;
    case 3:
        massimo(ptr);
        break;
    case 4:
        minimo(ptr);
        break;
    case 5:
        stampapreorder(ptr);
        break;
    case 6:
        stampapostorder(ptr);
        break;
    case 7:
        inorder(ptr);
        break;
    case 8:
        exit = false;
        break;
    }
}

void inserimento(albero *ptr, int valore)
{
    if(ptr->dato == NULL)
    {
        ptr->dato = valore;
    }
    else
    {
        if(valore < ptr->dato)
        {
            ptr->min = new albero;
            ptr = ptr->min;
            inserimento(ptr,valore);
        }
        else
        {
            ptr->max = new albero;
            ptr = ptr->max;
            inserimento(ptr, valore);
        }
    }
}

void search(int valore, albero *ptr)
{
    if(ptr == NULL)
    {
        cout <<"il valore cercato non e' stato trovato!"<<endl;
    }
    else
    {
        if(valore == ptr->dato)
        {
            cout << "Valore cercato " << valore <<" e' stato trovato!"<<endl;
        }
        else
        {
            if(valore < ptr->dato)
            {
                search(valore, ptr->min);
            }
            else
            {
                search(valore, ptr->max);
            }
        }
    }
}

void massimo(albero *ptr)
{
    if(ptr->dato == NULL)
    {
        cout << "Albero e' vuoto!\n";
    }
    else
    {
        if(ptr->max == NULL)
        {
            cout << "Max : " << ptr->dato <<endl;
        }
        else
        {
            massimo(ptr->max);
        }
    }
}

void minimo(albero *ptr)
{
    if(ptr->dato == NULL)
    {
        cout << "Albero e' vuoto!\n";
    }
    else
    {
        if(ptr->min == NULL)
        {
            cout << "Min : " << ptr->dato<<endl;
        }
        else
        {
            minimo(ptr->min);
        }
    }
}

void stampapreorder(albero *ptr)
{
    if(ptr != NULL)
    {
        cout << ptr->dato;
        stampapreorder(ptr->min);
        stampapreorder(ptr->max);
    }
}

void stampapostorder(albero *ptr)
{
    if(ptr != NULL)
    {
        stampapreorder(ptr->min);
        stampapreorder(ptr->max);
        cout << ptr->dato;
    }
}

void inorder(albero *ptr)
{
    if(ptr != NULL)
    {
        inorder(ptr->min);
        cout<<ptr->dato<<" ";
        inorder(ptr->max);
    }
}
