//
// Created by zacomo
//

#include <iostream>
#include <string>
struct Item{
    string description; //diversa per ogni oggetto, come chiave primaria
    string type; //forse si può fare con enum
    bool consumable;
    int LP,MP,DEF,ATK; //Caratteristiche modificate dall'item
};
