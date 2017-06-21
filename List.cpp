//
// Created by zacomo
//

#include "list.h"

listptr getPosition(Item elemento, listptr p){
    listptr el = NULL;
    bool found = false;
    while ((p != NULL) && !found){
        if (elemento.description == p->thing.description) {
            el = p;
            found = true;
        }
        p = p->next;
    }
    return el;
}

bool is_in(Item elemento, listptr p){
    bool found = false;
    while ((p != NULL) && !found){
        if (elemento.description == p->thing.description) found = true;

        p = p->next;
    }
    return found;
}

bool is_in_type(string tipo, listptr p){
    bool found = false;
    while ((p != NULL) && !found){
        if (tipo == p->thing.description) found = true;
        p = p->next;
    }
    return found;
}

void HeadInsert(Item elemento, listptr p){
    listptr tmpptr = new list;
    tmpptr->thing = elemento;
    tmpptr->next = p;
    p = tmpptr;
    delete tmpptr;
}

void ListRemove(Item elemento, listptr p){
    listptr tmpptr = p;
    bool found = false;
    while ((p != NULL) && !found){  //se ci sono elementi uguali ne deve rimuovere 1 solo
        if (elemento.description == p->next->thing.description){
            tmpptr = p;
            found = true;
        }
        p = p->next;
    }
    tmpptr->next = p->next;
    delete p;
    delete tmpptr;
    //forse da rivedere caso in cui l'elemento è in fondo alla lista
    //ovvero (p->next = NULL)
}

