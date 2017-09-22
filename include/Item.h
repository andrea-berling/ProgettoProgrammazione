//
// Created by zacomo on 19/09/17.
//

#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include <string>
#include "Graph.h"

class Item {
    protected:
        std::string name;
        int type;           //0-3 Armatura 4-5 Arma/Scudo 6 Consumabile
        int LP,MP,DEF,ATK;
        char symbol;
        Point position;
    public:
        Item();

        Item(std::string name, int type, int LP, int MP, int DEF, int ATK);

        std::string getname();

        int gettype();

        int getLP();

        int getMP();

        int getDEF();

        int getATK();

        char getsymbol();

        Point getposition();

        Point setposition(int x, int y);

        friend bool operator ==(Item i1, Item i2);

        friend bool operator !=(Item i1, Item i2);
};

namespace std
{
    template <> struct hash<Item>
    {
        size_t operator()(Item i) const;
        // Hash function for the class Item
    };
}

void retrieveItems(std::ifstream& file, std::vector& set);
// Given a file with the items and a vector of Items, it retireves them and stores them in the vector
#endif //GAME_ITEM_H
