//
// Created by zacomo
//


#include <unordered_set>
#include <string>
#include "../include/Item.h"

struct Position{            //Da rimuovere in futuro per usarne una in comune
    double X, Y;
};

class PlayableCharacter{
private:
    double LP, MP, DEF, ATK;
    double LPMAX, MPMAX;
    int LV, Coins;
    Position POS;
    std::string Name;
    std::unordered_multiset<Item> Inventory;
    Item equipment [6];

public:

    PlayableCharacter();
    // Costruttore di default

    PlayableCharacter(double LPMAX, double MPMAX, double DEF, double ATK, std::string Name);

    double getLP();

    double getLPMAX();

    double getMP();

    double getMPMAX();

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

    void setCoins(int Coins);

    std::string getName();

    bool useConsumable(Item sbobba);

    bool equip(Item ferraglia);

    bool unequip(Item ferraglia);

    bool getItem(Item thing);

    bool dropItem(Item thing);

    void LVLup();
};



