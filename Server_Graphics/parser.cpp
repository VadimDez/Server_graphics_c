#include "parser.h"

parser::parser()
{
}
// inserisce tutta la stringa mandata dal client in queue
void parser::insert(string str)
{
    string s;
    for(unsigned int i=0;i<str.length();i++)
    {
        char c = str[i];
        // ogni volta controlla se carattere e' un numero o un operatore,
        // se e' un numero aggiunge nella stringa S, poi se trova un altro numero lo agginge in
        // fondo della stringa S, quando trova operatore, prima aggiunge la stringa S
        // che contiene numero in altra stringa queue, e poi aggiunge operatore.
        // cosi posso lavorare con i numeri che sono fatti di piu' cifre(es.:512);
        if(c=='+'|| c=='-' || c=='/'|| c=='*' || c=='^' || c=='(' || c==')')
        {
            if(!s.empty()) // c'e' operatore. Usa quando ci sono numeri negativi.
            {
                temp.push(s);
            }
            s = c;
            temp.push(s);
            s.clear();
        }
        else
        {
            s += c;
            if((i+1)==str.length())//se e' in fondo;
            {
                temp.push(s);
            }
        }
    }
}
// controlla la stringa mandata dal utente che e' stata precedentemente salvata nella queue
// e mette nella stringa di risposta i numeri asseconda delle precedenze
// invece gli operatori mette in uno stack sempre riguardando le precedenze
int parser::precedence()
{
    int NumParentesi=0;
    while (!temp.empty())
    {
        bool exit=false;
        bool flag=false;
        if(temp.front()==")")//se trova parentesi destra, salva nel deque di output
        {                    //gli operatori dallo stack e cancella essi dallo stack
            while(ops.top()!="(")
            {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
            exit=true;
            flag=false;
            NumParentesi--;
        }
        while(!exit)
        {   // mette operatore dentro lo stack, controllando la precedenza degli operatori
            if(temp.front()=="+"||temp.front()=="-"||temp.front()=="/"||temp.front()=="*"||temp.front()=="^")
            {
                if(!ops.empty())
                {
                    if(ops.top()=="*"||ops.top()=="-"||ops.top()=="+"||ops.top()=="/"||ops.top()=="^")
                    {
                        if((ops.top()=="+"||ops.top()=="-")&&( temp.front()=="*"||temp.front()=="/"||temp.front()=="^" ))
                        {
                            if(!flag)
                                ops.push(temp.front());
                        }
                        else if(ops.top()=="*"||(ops.top()=="/" && temp.front()=="^"))
                        {
                            if (!flag)
                                ops.push(temp.front());
                        }
                        else
                        {
                            output.push_back(ops.top());
                            ops.pop();
                            ops.push(temp.front());
                        }
                    }
                    else
                        ops.push(temp.front());
                }
                else
                    ops.push(temp.front());
            }
            else if(temp.front()=="(")
            {
                ops.push("(");
                flag=true;
                NumParentesi++;
            }
            else
            {
               output.push_back(temp.front());
            }
            exit=true;
        }
        temp.pop();
    }
    if(NumParentesi!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void parser::operators() // aggiunge alla stringa di risposta gli operatori
{
    while(!ops.empty())
    {
        if(ops.top()=="+"||ops.top()=="-"||ops.top()=="/"||ops.top()=="*" || ops.top()=="^")
            output.push_back(ops.top());
        ops.pop();
    }
}
double parser::result() // calcola il risultato
{
    deque<string>::iterator it;
    it=output.begin();
    char* cstr=new char(2);
    string str;
    int count=0;
    float temp;
    while (output.size()!=1)
    {
        str=*it;
        strcpy(cstr,str.c_str());
        double tmp2=atoi(cstr);
        if((*it=="*"||*it=="+"||*it=="/"||*it=="-" || *it=="^")&&tmp2>=0)
        {
            string sign=*it;
            if(*it-->"-9999"||(*it<"99999999"&&*it-->"-9999")||*it<"9999999999")
            {
                *it++,*it++;
                output.erase(output.begin()+count);
                it=output.begin()+(count-1);
                str=*it;
                strcpy(cstr,str.c_str());
                temp=atoi(cstr);
                output.erase(output.begin()+(count-1));
                if(!output.empty())
                {
                    it=output.begin()+(count-2),str=*it;
                    strcpy(cstr,str.c_str());
                    output.erase(output.begin()+(count-2));
                }
                else
                {
                    str='0';
                    strcpy(cstr,str.c_str());
                }
                if(sign=="+")
                    temp=temp+atof(cstr);
                else if(sign=="-")
                    temp=atof(cstr)-temp;
                else if(sign=="*")
                    temp=atof(cstr)*temp;
                else if (sign=="/")
                    temp=atof(cstr)/temp;
                else if(sign=="^")
                    temp=pow(atof(cstr),double(temp));
                itoa(temp,cstr,10);
                //sprintf(cstr,"%f",temp);
                str=cstr;
                if(!output.empty())
                {
                   output.insert(output.begin()+(count-2),str);
                }
                else
                {
                   output.insert(output.begin(),str);
                }
                it=output.begin();
                count=0;
            }
        }
        *it++;
        count++;
    }
    string s = output.front();
    return atof(s.c_str());;
}
