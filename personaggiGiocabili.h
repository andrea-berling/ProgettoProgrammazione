//
// Created by zacomo
//

#include "list.h"

struct Position{
    double X, Y;
};

class PlayableCharacter{
private:
    double LP, MP, DEF, ATK;
    int LV, Coins;
    Position POS;
    string  Name, Description;
    listptr Inventory;
    listptr Equipment;
    //int InvSize; dimensioni Inventario

public:

    PlayableCharacter(double LP, double MP, double DEF, double ATK, string Name, string Description){
        this->LP = LP;
        this->MP = MP;
        this->DEF = DEF;
        this->ATK = ATK;
        this->POS.X=0;
        this->POS.Y=0;
        this->LV = 0;
        this->Coins = 0;
        this->Name = Name;
        this->Description = Description;
        Inventory = NULL;
        Equipment = NULL;
    }

    double getLP(){
        return LP;
    }

    double getMP(){
        return MP;
    }

    double getDEF(){
        return DEF;
    }

    double getATK(){
        return ATK;
    }

    Position getPosition() {
        return this->POS;
    }

    int getLV(){
        return LV;
    }

    int getCoins(){
        return Coins;
    }

    void setLP(double LP){
        this->LP = LP;
    }

    void setMP(double MP){
        this->MP = MP;
    }

    void setDEF(double DEF){
        this->DEF = DEF;
    }

    void setATK(double ATK){
        this->ATK = ATK;
    }

    void setPosition(double x, double y){
        this->POS.X = x;
        this->POS.Y = y;
    }

    void setLV(int LV){
        this->LV = LV;
    }

    void setCoins(int Coins){
        this->Coins = Coins;
    }

    string getName(){
        return Name;
    }

    string getDescription(){
        return Description;
    }

    listptr getEquipment(){
        return Equipment;
    }

    listptr getInventory(){
        return Inventory;
    }

    string useConsumable(Item thing){ //implementabile anche con descrizione
        listptr tmpptr = getPosition(thing, Inventory);
        if ((!is_in_type(thing.type, Inventory)) && (tmpptr->thing.consumable)){
            LP = LP + tmpptr->thing.LP;
            MP = MP + tmpptr->thing.MP;
            DEF = DEF + tmpptr->thing.DEF;
            ATK = ATK + tmpptr->thing.DEF;
            ListRemove(thing, Inventory);           //consumabile utilizzabile una sola volta
            return thing.description + " usato!";

        }
        return "Non è un consumabile o non è nel tuo inventario!";
    }

    string equipItem(Item thing){
        if (!is_in_type(thing.type, Equipment)){

            listptr tmpptr = getPosition(thing, Inventory);
            tmpptr->equipped = true;
            LP = LP + tmpptr->thing.LP;
            MP = MP + tmpptr->thing.MP;
            DEF = DEF + tmpptr->thing.DEF;
            ATK = ATK + tmpptr->thing.ATK;
            HeadInsert(thing, Equipment);
            return "Oggetto equipaggiato!";
        }
        return "Hai già equipaggiato un oggetto dello stesso tipo!";

    }

    string unequipItem(Item thing){
        listptr tmpptr = getPosition(thing, Inventory);
        if (is_in(thing, Equipment)){
            tmpptr->equipped = false;
            LP = LP - tmpptr->thing.LP;
            MP = MP - tmpptr->thing.MP;
            DEF = DEF - tmpptr->thing.DEF;
            ATK = ATK - tmpptr->thing.ATK;
            ListRemove(thing, Equipment);
            return "Oggetto riposto nell'inventario!";
        }

        return "L'oggetto non è stato equipaggiato!";

    }

    string getItem(Item thing){
        HeadInsert(thing, Inventory);
        Inventory->equipped = false; //un oggetto appena raccolto non è equipaggiato
        return thing.description + " è stato raccolto!";
    }

    string dropItem(Item thing){     //Eventualmente posso implementarlo con la descrizione
        ListRemove(thing, Inventory); //dell'Item.
        return thing.description + " è stato lasciato!";
    }
};



