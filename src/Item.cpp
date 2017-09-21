//
// Created by zacomo on 19/09/17.
//

#include "Item.h"

using namespace std;

Item::Item() {
    name ="";
    type = -1;
    LP = 0;
    MP = 0;
    DEF = 0;
    ATK = 0;
}

Item::Item(string name, int type, int LP, int MP, int DEF, int ATK) {
    this->name = name;

    if (type > -1 && type < 7) //type va da 0 a 6
        this->type = type;

    this->LP = LP;
    this->MP = MP;
    this->DEF = DEF;
    this->ATK = ATK;

}

string Item::getname() {
    return this->name;
}

int Item::gettype() {
    return this->type;
}

int Item::getLP() {
    return this->LP;
}

int Item::getMP() {
    return this->MP;
}

int Item::getDEF() {
    return this->DEF;
}

int Item::getATK() {
    return this->ATK;
}

bool Item::operator==(Item rhs) {
    return this->name == rhs.name;
}

bool Item::operator!=(Item rhs) {
    return this->name != rhs.name;
}