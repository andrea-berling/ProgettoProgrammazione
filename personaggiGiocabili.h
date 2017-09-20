//
// Created by zacomo
//


#include <unordered_set>
#include <string>
#include "Item.h"

struct Position{
    double X, Y;
};

class PlayableCharacter{
private:
    double LP, MP, DEF, ATK;
    int LV, Coins;
    Position POS;
    std::string Name;
    std::unordered_multiset<Item> Inventory;
    Item equipment [6];

public:

    PlayableCharacter(double LP, double MP, double DEF, double ATK, std::string Name):Inventory(47);

    double getLP();

    double getMP();

    double getDEF();

    double getATK();

    Position getPosition();

    int getLV();

    int getCoins();

    void setLP(double LP);

    void setMP(double MP);

    void setDEF(double DEF);

    void setATK(double ATK);

    void setPosition(double x, double y);

    //void setLV(int LV);

    void setCoins(int Coins);

    std::string getName();

    bool useConsumable(Item sbobba);

    bool equip(Item ferraglia);

    bool unequip(Item ferraglia);

    bool getItem(Item thing);

    bool dropItem(Item thing);

    void LVLup();
};



