#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

struct Caractere{
	int nr_aparitii = 0;
	char caracter;
}v[200];

void frecventa(Caractere v[],int &lungime,char c)
{
    int i,OK = 0;
    for(int i=0;i<lungime;i++)
        if(v[i].caracter == c && int(c) != 10)
        {
            v[i].nr_aparitii++;
            OK = 1;
            break;
        }
    if(!OK)
    {
    v[lungime].caracter = c;
    v[lungime].nr_aparitii++;
    lungime++;
    }
}

void sortare(Caractere v[],int lungime)
{
    for(int i = 0;i < lungime;i++)
        for(int j = i+1;j <= lungime;j++)
            if(v[i].nr_aparitii > v[j].nr_aparitii)
                {
                    int auxnr = v[i].nr_aparitii;
                    char auxc = v[i].caracter;
                    v[i].nr_aparitii = v[j].nr_aparitii;
                    v[i].caracter = v[j].caracter;
                    v[j].nr_aparitii = auxnr;
                    v[j].caracter = auxc;
                }
}

struct Nod{
    int nr_aparitii = 0;
    string litera = "";
    string cod = "";
    Nod* next;
    Nod* prev;
    Nod* st;
    Nod* dr;
};

Nod* head = NULL;

Nod* newNod(){
    Nod* temp = new Nod;
    temp->next = NULL;
    temp->prev = NULL;
    temp->st = NULL;
    temp->dr = NULL;
    return temp;
}

void adaugFinal(Nod* &head,int nr_aparitii,string litera){
    Nod* el = newNod();
    el->litera = litera;
    el->nr_aparitii = nr_aparitii;
    el->cod = "";
    if (head == NULL)
          head = el;
     else{
           Nod* temp = head;
           while(temp->next != NULL)
                    temp = temp->next;
          temp->next = el;
          el->prev = temp;
     }
 }

void Afisare(Nod* head){
    Nod* temp = head;
    while(temp != NULL){
        cout << temp->litera << "\t" << temp->nr_aparitii << endl;
        temp = temp->next;
    }
}

void bubbleSort(Nod* start){
    int OK;
    Nod *el1;
    Nod *el2 = NULL;
    if (start == NULL)
        return;
    do{
        OK = 0;
        el1 = start;
        while (el1->next != el2){
            if (el1->nr_aparitii > el1->next->nr_aparitii){
                swap(el1->nr_aparitii, el1->next->nr_aparitii);
                swap(el1->litera,el1->next->litera);
                swap(el1->cod,el1->next->cod);
                swap(el1->st,el1->next->st);
                swap(el1->dr,el1->next->dr);
                OK = 1;
            }
            el1 = el1->next;
        }
    }
    while (OK);
}

void arbore(Nod* &head){
    Nod* temp = head;
    if(temp->next != NULL){
        Nod* x = newNod();
        Nod* y = newNod();
        Nod* z = newNod();
        //Stanga
        y->litera = temp->litera;
        y->nr_aparitii = temp->nr_aparitii;
        if(temp->st != NULL && temp->dr != NULL){
            y->st = temp->st;
            y->dr = temp->dr;
        }
        //Dreapta
        z->litera = temp->next->litera;
        z->nr_aparitii = temp->next->nr_aparitii;
        if(temp->next->st != NULL && temp->next->dr != NULL){
            z->st = temp->next->st;
            z->dr = temp->next->dr;
        }
        x->nr_aparitii = y->nr_aparitii + z->nr_aparitii;
        x->litera = y->litera + z->litera;
        x->st = y;
        x->dr = z;
        head = head->next->next;
        delete temp;
        delete temp->next;
        if(head == NULL){
            head = x;
            return;
        }
        head->prev = x;
        x->next = head;
        head = x;
    }
}

void codificare(Nod* head,string str){
    if (head != NULL){
        codificare(head->st,str + "0");
        if(head->st == NULL && head->dr == NULL)
        	head->cod = str;
        codificare(head->dr, str + "1");
    }
}

void afisaretxt(Nod* head,ofstream& g1){
    if (head != NULL){
        g1<<head->litera<<" "<<head->nr_aparitii<<endl;
        if(head->st == NULL && head->dr == NULL)
            g1<<0<<endl;
        afisaretxt(head->st,g1);
        afisaretxt(head->dr,g1);
    }
}


void afisare(Nod* head,string str){
    if (head != NULL){
    	if(head->litera == str){
    	cout << head->litera << "  (" << head->nr_aparitii << ")\t\t" << head->cod << endl;
    	return;
    	}
        afisare(head->st,str);
        afisare(head->dr,str);
    }
}

void parcurg(Nod* head,string str,string &cod){
    if (head != NULL){
    	if(head->litera == str)
        {
    	    cout << head->cod;
    	    cod = cod + head->cod;
        }
        parcurg(head->st,str,cod);
        parcurg(head->dr,str,cod);
    }
}

void decodificare(Nod* head,string cod, int &poz)
{
    while(head->st != NULL && head->dr != NULL)
    {
        if(cod[poz] == '0')
            head = head->st;
        else
            head = head->dr;
        poz++;
    }
    cout << head->litera;
}


int main(){
    ifstream f1("in.txt");
    ifstream f2("in.txt");
    ofstream g1("out.txt");
    char c;
    string cod = "";
    int i,lungime = 0;
    //Frecventa fiecarui caracter
    f1.get(c);
    v[0].caracter = c;
    v[0].nr_aparitii++;
    lungime++;
    while (f1.get(c))
    {
        frecventa(v,lungime,c);
    }
    lungime--;
    sortare(v,lungime);
    //Adaugare in lista
    for(i = 0;i <= lungime;i++)
    {
        char aux[2];
        aux[0] = v[i].caracter;
        aux[1] = NULL;
        adaugFinal(head,v[i].nr_aparitii,string(aux));
    }
    //Sortare si creare arbore
    bubbleSort(head);
    while(head->next != NULL){
        arbore(head);
        bubbleSort(head);
    }
    //Codificare text si afisare caractere si codul acestora
    codificare(head,"");
    cout << "Caracter\tCodificare" << endl;
    for(i = lungime;i >= 0;i--)
    {
    	char aux[2];
    	aux[0] = v[i].caracter;
    	aux[1] = NULL;
    	afisare(head,string(aux));
    }
    //Afisare text codificat
    cout << "\nTextul codificat:";
    while (f2.get(c))
    {
        char aux[2];
        aux[0] = c;
        aux[1] = NULL;
        parcurg(head,string(aux),cod);
    }
    afisaretxt(head,g1);
    cout << endl;
    g1 << cod;
    //Afisare si decodificare text
    cout << "Textul decodificat:";
    i = 0;
    while(i < cod.size())
    {
        decodificare(head,cod,i);
    }
    return 0;;
}
