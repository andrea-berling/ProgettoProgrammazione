//
// Created by zacomo on 20/09/17.
//

#include "Monster.h"

Monster::Monster(string Name, int LV, int x, int y) {
    if (LV < 1)
        LV = 1; //il livello non può essere negativo

    this->LV = LV;
    this->POS.X = x;
    this->POS.Y = y;
    this->Name = Name;
    double atk = 0, def = 0, lp = 1;

    if (Name == "Goblin"){
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

double Monster::getLP(){
    return this->LP;
}

double Monster::getDEF(){
    return this->DEF;
}

double Monster::getATK(){
    return this->ATK;
}

Position Monster::getPosition() {
    return this->POS;
}

int Monster::getLV(){
    return this->LV;
}

void Monster::setLP(double LP){
    this->LP = LP;
}

void Monster::setDEF(double DEF){
    this->DEF = DEF;
}

void Monster::setATK(double ATK){
    this->ATK = ATK;
}

void Monster::setPosition(double x, double y){
    this->POS.X = x;
    this->POS.Y = y;
}

char Monster:: getsymbol(){
    return this->symbol;
}

std::string Monster::getName(){
    return this->Name;
}


