//
// Created by zacomo on 19/09/17.
//

#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include <string>

class Item {
    protected:
        std::string name;
        int type;           //0-3 Armatura 4-5 Arma/Scudo 6 Consumabile
        int LP,MP,DEF,ATK;

    public:
        Item();

        Item(std::string name, int type, int LP, int MP, int DEF, int ATK);

        std::string getname();

        int gettype();

        int getLP();

        int getMP();

        int getDEF();

        int getATK();

        bool operator ==(Item rhs);

        bool operator !=(Item rhs);
};

#endif //GAME_ITEM_H
