//
// Created by zacomo on 20/09/17.
//

#ifndef GAME_MONSTER_H
#define GAME_MONSTER_H
#include <string>
#include "Graph.h"


class Monster {
    private:
        double LP, DEF, ATK;
        int LV;
        Point POS;
        std::string Name;
        char symbol;   

    public:

    Monster();

    Monster(std::string Name, int LV);

    double getLP();

    double getDEF();

    double getATK();

    Point getPosition();

    int getLV();

    void setLP(double LP);

    void setDEF(double DEF);

    void setATK(double ATK);

    void setPosition(double x, double y);

    std::string getName();

    char getSymbol();

    friend bool operator==(Monster m1,Monster m2);

    friend bool operator!=(Monster m1,Monster m2);
};

namespace std
{
    template <> struct hash<Monster>
    {
        size_t operator()(Monster m) const;
        // Hash function for the class Item
    };
}


#endif //GAME_MONSTER_H
