//
// Created by zacomo
//

#include "item.h"

using namespace std;

struct list{
    Item thing;         //da sistemare il nome
    bool equipped;
    list *next;
};

typedef list* listptr;

listptr getPosition(Item elemento, listptr p);
//Restituisce un puntatore al nodo in cui è presente l'item cercato

bool is_in(Item elemento, listptr p);
//True se quell'item è presente nella lista p, false altrimenti

bool is_in_type(string tipo, listptr p);
//True se quel tipo è presente, falso altrimenti.

void HeadInsert(Item elemento, listptr p);
//Inserisce elemento nella lista p

void ListRemove(Item elemento, listptr p);
//Rimuove l'elemento dalla lista


