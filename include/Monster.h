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

    Monster(std::string Name, int LV, int x, int y);

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

    char getsymbol();
};


#endif //GAME_MONSTER_H
