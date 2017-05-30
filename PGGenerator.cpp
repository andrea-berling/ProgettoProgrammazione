//
// Created by zacomo
//

#include "personaggiGiocabili.h"

using namespace std;

PlayableCharacter Guerriero(15,0,20,12,"Gianbruno", "storia di Gianbruno");
//Attacco medio e difesa eccellente
//Lento nei movimenti
//Uso della magia ridotto o nullo

PlayableCharacter Mago(10,20,10,8,"Peppino", "Storia di Peppino");
//Attacco elevato se si usa mana, debole altrimenti
//Difesa medio-bassa
//velocità media

PlayableCharacter Ladro(10,0,5,12,"Badore","Storia di Badore");
//Attacco elevato se si usa abilità, nella media altrimenti
//Movimenti rapidi
//Difesa scarsa
//L'abilità consiste nella possibilità di raddoppiare l'attacco
//ma con una % di rischio di fallimento con conseguente perdita di LP
//Inizia con un bonus di X monete