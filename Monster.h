//
// Created by zacomo on 20/09/17.
//

#ifndef GAME_MONSTER_H
#define GAME_MONSTER_H


class Monster {
    private:
        double LP, DEF, ATK;
        int LV;
        Position POS;
        std::string Name;

    public:

    Monster(string Name, int LV, int x, int y);

    double getLP();

    double getDEF();

    double getATK();

    Position getPosition();

    int getLV();

    void setLP(double LP);

    void setDEF(double DEF);

    void setATK(double ATK);

    void setPosition(double x, double y);

    std::string getName();
};


#endif //GAME_MONSTER_H
