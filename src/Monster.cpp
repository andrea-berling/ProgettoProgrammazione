//
// Created by zacomo on 20/09/17.
//

#include "Monster.h"

using namespace std;

Monster::Monster() {
    awake = false;
    this->LP = -1;
    this->DEF = -1;
    this->ATK = -1;
    Name = "";
}

Monster::Monster(string Name, int LV) {
    if (LV < 1)
        LV = 1; //il livello non può essere negativo

    this->LV = LV;
    this->Name = Name;
    int atk = 0, def = 0, lp = 1;
    awake = false;

    if (Name == "Goblin"){  //  Mostri diversi statistiche e simboli diversi
        atk = 2 * (LV +1 );
        def = 1;
        lp = LV;
        this->symbol = 'G';
    }

    if (Name == "Troll"){
        atk = 3 + LV;
        def = 3 + LV;
        lp = 3 + LV;
        this->symbol = 'T';
    }

    if (Name == "Golem"){
        atk = 2 + LV;
        def = 2 * (LV + 1);
        lp = 2 + LV;
        this->symbol = 'O';
    }

    if (Name == "Gineppino"){
        atk = 3 * LV;
        def = 5 * LV;
        lp = 5 * LV;
        this->symbol = 'P';
    }

    this->ATK = atk;
    this->DEF = def;
    this->LP = lp;
}

int Monster::getLP(){
    return this->LP;
}

int Monster::getDEF(){
    return this->DEF;
}

int Monster::getATK(){
    return this->ATK;
}

Point Monster::getPosition() {
    return this->POS;
}

int Monster::getLV(){
    return this->LV;
}

void Monster::setLP(int LP){
    this->LP = LP;
}

void Monster::setDEF(int DEF){
    this->DEF = DEF;
}

void Monster::setATK(int ATK){
    this->ATK = ATK;
}

void Monster::setPosition(int x, int y){
    this->POS.x = x;
    this->POS.y = y;
}

char Monster::getSymbol(){
    return this->symbol;
}

std::string Monster::getName(){
    return this->Name;
}

bool Monster::isAwake(){
    return this->awake;
}

void Monster::wakeUp(){
    this->awake = true;
}

bool operator==(Monster m1,Monster m2){
    m1.Name == m2.Name && m1.POS == m2.POS;
}

bool operator!=(Monster m1,Monster m2){
    m1.Name != m2.Name || m1.POS != m2.POS;
}

namespace std
{
    size_t hash<Monster>::operator()(Monster m) const
    {
        return hash<string>()(m.getName());
    }
    // Hash function for the class Monster
}
