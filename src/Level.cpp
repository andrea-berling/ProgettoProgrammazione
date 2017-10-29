#include "../include/Level.h"
#include "../include/utility.h"
#include <ncurses.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <unistd.h>
#include "../include/Menu.h"

#define NEEDED_PIECES 12

using namespace std;

Level::Level(const LevelConfig& config, PlayableCharacter& pg):level(config.n),map(config.width,config.height)
{
    vector<Item> itemsSet;
    Room R;
    Point p;

    retrieveItems(itemsSet); // Retrieves all the possible items from a file and puts them in the vector

    if(level > 1)
        shopMenu(pg, itemsSet);

    int generatedRooms = map.generate(config.rooms);

    spawnItems(config.items,itemsSet,generatedRooms);
    spawnMonsters(config.monsters,generatedRooms);

    upStairs = map.placeStairs(UP_STAIRS);

    R = map.pickRoom();
    p = map.freeSpot(R);
    map(p.x,p.y).setUpperLayer("degree");
}

void Level::printMap(const Point playerPos, Window& mapWindow)
{
    mapWindow.clear();
    WINDOW *win = mapWindow.getWin();
    move(0,0);
    for(int i = 0; i < map.getHeight(); i++)
    {
        for (int j = 0; j < map.getWidth(); j++)
        {
            if(map(j,i).isVisible())
                if(map(j,i).getUpperLayer() == "degree")
                    waddch(win,'*');
                else
                    waddch(win,map(j,i).getSymbol());
            else
                waddch(win,' ');
        }
    }
    for(auto i : items)
    {
        Point position = i.second.getPosition();
        if(i.second.isVisible())
            mvwaddch(win,position.y,position.x,i.second.getSymbol());
    }
    for(auto m : monsters)
    {
        Point position = m.second.getPosition();
        if(m.second.isAwake())
            mvwaddch(win,position.y,position.x,m.second.getSymbol());
    }

    mvwaddch(win,playerPos.y,playerPos.x,'@');

    wrefresh(win);
}

void Level::placeCharacter(PlayableCharacter& player, const pos_pref_t preference)
{
    switch(preference)
    {
        case RANDOM:
            {
                string room = map.placeCharacter(player);
                map.setVisible(room,monsters,items);
                if (level > 1)
                    downStairs = map.placeStairs(DOWN_STAIRS,player.getPosition().x,player.getPosition().y);
            }
            break;
            
        case DOWNSTAIRS:
            player.setPosition(downStairs.x,downStairs.y);
            break;

        case UPSTAIRS:
            player.setPosition(upStairs.x,upStairs.y);
            break;
    }
}

status_t Level::handleTurn(Window& mapWindow, Window& info, Window& bottom,PlayableCharacter& player)
{
    status_t status = DEFAULT;
    int x,y,c;
    bool moved = false;

    while(status == DEFAULT)
    {
        // Handle the input from the player
        c = getch();
        switch(c)
        {
            // Movement keys
            case 'k':
            case KEY_UP:
            case 'j':
            case KEY_DOWN:
            case 'h':
            case KEY_LEFT:
            case 'l':
            case KEY_RIGHT:
                moved = map.movePlayer(player,c);
                break;
            case 'i':
                player.showInventory();
                writeInfo(info,player);
                break;
            case 'q':
                status = promptExit(bottom);
                break;
        }

        x = player.getPosition().x;
        y = player.getPosition().y;

        // Show the map dinamically
        showMap(player.getPosition());

        if(moved == true)
        {
            moved = false;
            // Move the npcs
            for(auto& m : monsters)
                if(m.second.isAwake())
                    moveMonster(player.getPosition(),m.second);
            // Change level
            if(map(x,y).getType() == UP_STAIRS || map(x,y).getType() == DOWN_STAIRS)
                status = map(x,y).getType() == UP_STAIRS ? UP : DOWN;
            else
            {
                // Update the players info
                info.clear();
                writeInfo(info,player);
                printMap(player.getPosition(),mapWindow);

                // Handle the battle with nearby monsters, if present
                status = handleBattles(player,bottom,info,mapWindow);
                if(status != LOSS && map(x,y).getUpperLayer() != "")
                    // Pick up items or degree pieces
                    status = pickItUp(player,bottom);
            }
        }
    }

    return status;
}

int Level::getLevel() const
{
    return level;
}

void writeEquipment(Window& win, PlayableCharacter& pg){
    string msg1 = "";
    string msg2 = "";
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                msg1 = "Elmo: ";
                if (pg.getEquipmentAt(0) == Item()) {
                    msg2 = "Non equipaggiato";
                }
                else {
                    msg2 = pg.getEquipmentAt(0).getName();
                }
                msg1 = msg1 + msg2;
                win.printLine(msg1);
                break;

            case 1:
                msg1 = "Corazza: ";
                if (pg.getEquipmentAt(1) == Item())
                    msg2 = "Non equipaggiata";
                else
                    msg2 = (pg.getEquipmentAt(1)).getName();

                msg1 = msg1 + msg2;
                win.printLine(msg1);
                break;

            case 2:
                msg1 = "Stivali: ";
                if (pg.getEquipmentAt(2) == Item())
                    msg2 = "Non equipaggiati";
                else
                    msg2 = (pg.getEquipmentAt(2)).getName();

                msg1 = msg1 + msg2;
                win.printLine(msg1);
                break;

            case 3:
                msg1 = "Spada: ";
                if (pg.getEquipmentAt(3) == Item())
                    msg2 = "Non equipaggiata";
                else
                    msg2 = (pg.getEquipmentAt(3)).getName();

                msg1 = msg1 + msg2;
                win.printLine(msg1);
                break;

            case 4:
                msg1 = "Scudo: ";
                if (pg.getEquipmentAt(4) == Item())
                    msg2 = "Non equipaggiato";
                else
                    msg2 = (pg.getEquipmentAt(4)).getName();

                msg1 = msg1 + msg2;
                win.printLine(msg1);
                break;
        }
    }
}

void Level::writeInfo(Window& win,PlayableCharacter& pg){
    win.clean();
    win.printLine(pg.getName());
    win.printLine("");
    win.printLine("LP: " + to_string(pg.getLP()) + '/' + to_string(pg.getLPMAX()));
    win.printLine("MP: " + to_string(pg.getMP()) + '/' + to_string(pg.getMPMAX()));
    win.printLine("ATK: " + to_string(pg.getATK()));
    win.printLine("DEF: " + to_string(pg.getDEF()));
    win.printLine("LV: " + to_string(pg.getLV()));
    win.printLine("Cucuzze: " + to_string(pg.getCoins()));
    win.printLine("");
    win.printLine("Livello attuale: " + to_string(level));
    win.printLine("Pezzi di laurea: " + to_string(pg.getPieces()) + "/" + to_string(NEEDED_PIECES));

    win.separator();

    writeEquipment(win, pg);

    win.printLine("");
    win.printLine("Mossa speciale: ");
    switch (pg.getName().front()){
        case 'G':
            win.printLine("Rigenerazione");
            break;

        case 'B':
            win.printLine("Attacco Furtivo");
            break;

        case 'P':
            win.printLine("Attacco Magico");
            break;
    }

}

void Level::shopMenu(PlayableCharacter& pg,vector<Item>& itemsSet)
{
    int priceMult = 4;
    int items = 3;
    int indexes[items];
    int yoffset = items + 1;
    int xoffset = 24;   // length of the name of the item with the longest name
    int xinfo = 20;
    int yinfo = 0;
    int choice = 0;
    bool done = false;
    bool noMoney = false;
    int confirm = -1;
    string ID = "item.shop." + to_string(level) + ".";
    Item chosenItem;

    generateKPermutation(indexes,0,itemsSet.size()-1,items);

    Menu shop(map.getWidth()/2 - xoffset,map.getHeight()/2 - yoffset, 4, itemsSet[indexes[0]].getName().c_str(), itemsSet[indexes[1]].getName().c_str(), itemsSet[indexes[2]].getName().c_str(), "Sono Povero"); // c_str() returns the c string correpsonding to the string
    Window itemInfo(shop.getX() + xinfo, shop.getY() + yinfo, 11, 30);

    itemInfo.clean();
    itemInfo.printLine("SHOP");
    itemInfo.printLine("");
    itemInfo.printLine("Se hai abbastanza cucuzze");
    itemInfo.printLine("puoi rafforzarti");

    choice = shop.handleChoice();

    while (!done) {

        if (choice != 3 ) {
            chosenItem = itemsSet[indexes[choice]];
            itemInfo.clean();

            chosenItem = itemsSet[indexes[choice]];
            itemInfo.printLine(chosenItem.getName());
            itemInfo.printLine("Prezzo: " + to_string((1 + indexes[choice])*priceMult) + " Cucuzze");
            itemInfo.printLine("LP: + " + to_string(chosenItem.getLP()));
            itemInfo.printLine("MP: + " + to_string(chosenItem.getMP()));
            itemInfo.printLine("ATK: + " + to_string(chosenItem.getATK()));
            itemInfo.printLine("DEF: + " + to_string(chosenItem.getDEF()));
            itemInfo.printLine("LUCK: + " + to_string(chosenItem.getLuck()));
            itemInfo.separator();
            if(noMoney)     // If you tried to buy something you can't afford
            {
                itemInfo.printLine("Cucuzze insufficienti!");
                noMoney = false;
            }
            confirm = shop.handleChoice();

            if (confirm == choice){ // se scelto due volte, viene scalato il prezzo dell'Item
                if (pg.addCoins(-(1 + indexes[choice])*priceMult))  // true se bastano i fondi, false altrimenti
                {
                    chosenItem.setId(ID + to_string(choice));
                    pg.pickItem(chosenItem);
                    done = true;
                }
                else
                    noMoney = true;
                    itemInfo.printLine("Cucuzze insufficienti!");
                    //non viene stampato a causa del clear; implementare setFirstAvaiableLine?
            }
            else
                choice = confirm;   // Così fa vedere le stat della nuova scelta
        }
        else
            done = true;        // è stato selezionato quit/esci
    }
}

Point Level::getUpStairs() const
{
    return upStairs;
}

Point Level::getDownStairs() const
{
    return downStairs;
}

void Level::monstersAround(const Point playerPos, std::list<Monster>& list)
{
    std::list<std::string> ids;

    for(int i = playerPos.y - 1; i < playerPos.y + 2; i++)
        for(int j = playerPos.x - 1; j < playerPos.x + 2; j++)
            if(!map(j,i).isWalkable() && map(j,i).getUpperLayer() != "" && map(j,i).getUpperLayer().front() == 'm') 
                // Map(j,i) is not walkable as there is a monster on it
                ids.push_back(map(j,i).getUpperLayer());

    for(string id : ids)
    {
        list.push_back(monsters[id]);
    }
}

void Level::moveMonster(Point playerPosition, Monster& mons){
    int dist;
    Point fmpos;    //  Futura posizione del mostro
    Point mpos; //  Posizione del mostro
    mpos = mons.getPosition();
    fmpos = mpos;
    map(mpos).setUpperLayer("");

    dist = w(playerPosition, mpos);
    if (map(playerPosition).getId() == map(mpos).getId()) { // if the monster and the player are in the same room

        for (int i = 0; i < 4; i++) {
            switch (i) {
                case 0:
                    fmpos.x = mpos.x + 1;
                    fmpos.y = mpos.y;
                    break;
                case 1:
                    fmpos.x = mpos.x - 1;
                    fmpos.y = mpos.y;
                    break;
                case 2:
                    fmpos.x = mpos.x;
                    fmpos.y = mpos.y + 1;
                    break;
                case 3:
                    fmpos.x = mpos.x;
                    fmpos.y = mpos.y - 1;
                    break;
            }

            if (validPosition(fmpos, playerPosition) && (w(fmpos, playerPosition) < dist))
                mpos = fmpos;

        }
    }
    else{
        int rmove;
        rmove = rand(0,3);

        switch (rmove) {
            case 0:
                fmpos.x = mpos.x + 1;
                fmpos.y = mpos.y;
                break;
            case 1:
                fmpos.x = mpos.x - 1;
                fmpos.y = mpos.y;
                break;
            case 2:
                fmpos.x = mpos.x;
                fmpos.y = mpos.y + 1;
                break;
            case 3:
                fmpos.x = mpos.x;
                fmpos.y = mpos.y - 1;
                break;
        }

        if (validPosition(fmpos, playerPosition))
            mpos = fmpos;

    }

    mons.setPosition(mpos.x, mpos.y);   // Assegna la nuova posizione al mostro
    map(mpos).setUpperLayer(mons.getId());
}

bool Level::validPosition(const Point pos,const Point playerPos)
{
    return pos != playerPos && map(pos).getType() == PAVEMENT && map(pos).getId() != "" && map(pos).getUpperLayer() == "";    // The monster can't leave
    //the room it's in and can't walk on the player or on items
}

bool Level::Battle(Window& battle_win, Window& right_win, Window& mapWin, PlayableCharacter& player, Monster& m){

    using namespace std;
    char c;
    int k;
    bool noAttack = false;
    bool escape = false;
    bool win;

    while ((m.getLP() > 0) && (player.getLP() > 0) && (!escape)) {

            battle_win.clean();
            battle_win.printLine("Premi:");
            battle_win.printLine("a) Attacco");
            battle_win.printLine("i) Consultare Inventario");
            battle_win.printLine("r) Corrompere il mostro");

            c = getch();

            battle_win.clean();
            noAttack = false;

            switch (c) {
                case 'a':

                    battle_win.printLine("Battaglia con " + m.getName() + ":");
                    battle_win.printLine("");
                    battle_win.printLine("PUNTI VITA -> " + to_string(m.getLP()));
                    battle_win.printLine("ATTACCO -> " + to_string(m.getATK()));
                    battle_win.printLine("DIFESA -> " + to_string(m.getDEF()));

                    getch();

                    battle_win.clean();
                    battle_win.printLine("Cosa vuoi fare?");
                    battle_win.printLine("1) Attacco normale");
                    battle_win.printLine("2) Mossa speciale");
                    battle_win.printLine("");

                    c = getch();

                    switch (c){
                        case '1': // Attacco normale scelto
                            int damage;

                            if (Luck(player.getLuck()) == 1) {             // attacco critico
                                damage = Atk_Def(m.getDEF(), (2 * player.getATK()));
                                battle_win.printLine("Colpo Critico");
                                getch();
                            } else{
                                damage = Atk_Def(m.getDEF(), player.getATK());
                            }

                            m.setLP(m.getLP() - damage);
                            battle_win.printLine("Hai tolto al tuo avversario " + to_string(damage) + " punti vita");
                            break;

                        case '2':
                            switch (player.getName().front()){
                                case 'G':   //gaudenzio
                                    battle_win.printLine("Hai guadagnato " + to_string(player.getLV() * 2) + " punti vita!");
                                    player.setLP(player.getLP() + player.getLV() * 2);
                                    writeInfo(right_win, player);
                                    break;

                                case 'P':   //peppino
                                    if (player.getMP() > 3) {
                                        battle_win.printLine("Stai usando 3 mana: attacco duplicato!");
                                        m.setLP(m.getLP() - Atk_Def(m.getDEF(), (2 * player.getATK())));
                                        writeInfo(right_win, player);
                                    }
                                    break;

                                case 'B':   //badore
                                    if (Luck(player.getLuck()) == 1) {
                                        battle_win.printLine("Il nemico non ti vede: attacco triplicato!");
                                        m.setLP(m.getLP() - Atk_Def(m.getDEF(), (3 * player.getATK())));
                                    } else {
                                        battle_win.printLine("Sei stato maldestro: il nemico contrattacca e perdi un turno!");
                                        player.setLP(player.getLP() - Atk_Def(player.getDEF(), (2 * m.getATK())));
                                        writeInfo(right_win, player);
                                    }
                                    break;
                            }

                            break;

                        default:
                            battle_win.printLine("Hai fatto una mossa falsa, perdi il turno!");
                            battle_win.printLine("(la prossima volta premi 1 o 2)");
                            break;
                    }

                    getch();

                    if (m.getLP() < 0)
                        m.setLP(0);

                    battle_win.clean();

                    battle_win.printLine("Battaglia con " + m.getName() + ":");
                    battle_win.printLine("");
                    battle_win.printLine("PUNTI VITA -> " + to_string(m.getLP()));
                    battle_win.printLine("LIVELLO -> " + to_string(m.getLV()));

                    getch();

                    break;

                case 'i':
                    player.showInventory();
                    right_win.clean();
                    writeInfo(right_win, player);
                    printMap(player.getPosition(), mapWin);

                    break;

                case 'r':

                    if (Luck(player.getLuck()) == 1){
                        battle_win.printLine("Per corrompere il mostro devi dare " + to_string(m.getLV()*5) + " Cucuzze");

                        if (player.getCoins() < m.getLV()*2){
                            battle_win.printLine("Non hai abbastanza cucuzze!");
                        }
                        else {
                            battle_win.printLine("Per procedere premi s, altrimenti n");

                            do{
                                c= getch();
                            } while (c!= 's' && c!= 'n');

                            battle_win.clean();

                            if (c == 's'){
                                win = true;
                                escape = true;

                                player.setCoins(player.getCoins() - m.getLV()*5);

                                battle_win.clean();
                                battle_win.printLine("Hai corrotto il mostro, se n'è andato");
                                battle_win.printLine("Hai dovuto pagare " + to_string(m.getLV()*5) + " Cucuzze");
                            }
                            else
                                escape =  false;
                        }
                    }
                    else {
                        battle_win.printLine("Non sei abbastanza fortunato il mostro non si fa corrompere");
                        battle_win.printLine("Perdi il tuo turno, il mostro ne approfitta e attacca");
                        escape = false;
                    }

                    getch();
                    battle_win.clean();

                    break;

                default:
                    battle_win.printLine("Premere un tasto valido!");
                    getch();
                    battle_win.clean();
                    noAttack = true;
                    break;
            }

            k = Luck(70);

            if ((m.getLP() > 0) && (!noAttack) && (!escape) && (k == 1)) {

                player.setLP(player.getLP() - Atk_Def(player.getDEF(), m.getATK()));

	            battle_win.clean();
                battle_win.printLine("L'avversario ti attacca!");
                battle_win.printLine("");
                battle_win.printLine("L'attacco del nemico ti toglie -> " + to_string(Atk_Def(player.getDEF(), m.getATK())) + " LP");

                getch();

                if (player.getLP() <= 0)
                    player.setLP(0);

                right_win.clean();
                writeInfo(right_win, player);
            }
	
    	    if (m.getLP() > 0 && k == 0){
	            battle_win.clean();
	            battle_win.printLine("L'avversaerio e' maldestro, fallisce l'attacco");
                getch();
    	    }
    }

    if (m.getLP() <= 0) {
        int wCoins = m.getLV() * 5; //  Monete vinte dal PG
        battle_win.clean();
        battle_win.printLine("!VITTORIA!");
        getch();
        battle_win.printLine("Hai ottenuto "+to_string(wCoins)+" Cucuzze!");
        player.addCoins(wCoins);
        getch();
        battle_win.clean();
        battle_win.box();
        win = true;
    }
    else if (player.getLP() <= 0){
        battle_win.clean();
        battle_win.printLine("SEI STATO SCONFITTO!");
        getch();
        battle_win.clear();
        win = false;
    }

    return win;
}

int Atk_Def (int def, int atk) {
    return  (int)(atk -  (double)(atk * def) / 100);           // fare il casting
}

int Luck (int luck){
    
    int i=0;

    i = rand() % 100 + 1;
    
    if (i <= luck)    // se i <= della fortuna del pg allora viene effettuato il critico (atk*2)
        return 1;
    else
        return 0;
}

status_t promptExit(Window& win)
{
    status_t status = DEFAULT;
    int c;

    win.clean();
    win.printLine("Sei sicuro di voler uscire? (y/n)");
    c = getch();

    if(c == 'y')
        status = QUIT;
    else
        win.clean();

    return status;
}

void Level::showMap(const Point p)
{
    if(map(p.x,p.y).getId() != "")
        map.setVisible(map(p.x,p.y).getId(),monsters,items);
    else
        map.showAround(p.x,p.y);
}

status_t Level::pickItUp(PlayableCharacter& player,Window& win)
{
    status_t status = DEFAULT;
    Point p = player.getPosition();

    if(map(p.x,p.y).getUpperLayer().front() == 'i') // It's an item
        if(player.pickItem(items[map(p.x,p.y).getUpperLayer()]))    /* returns true if the item was actually picked
                                                                   up*/
        {
            win.printLine("Raccolto " + items[map(p.x,p.y).getUpperLayer()].getName());
            getch();
            win.clean();
            items.erase(map(p.x,p.y).getUpperLayer());
            map(p.x,p.y).setUpperLayer("");
        }
        else
        {
            win.printLine("Hai camminato su " + items[map(p.x,p.y).getUpperLayer()].getName());
            getch();
            win.clean();
        } 
    else    // it's a degree piece
    {
        player.pickUpPiece();
        win.printLine("Hai raccolto un pezzo di laurea");
        map(p.x,p.y).setUpperLayer("");
        getch();
        if(player.getPieces() == NEEDED_PIECES)
        {
            win.printLine("Hai trovato tutti i pezzi della laurea");
            getch();
            status = WIN;
        }
        else
        {
            win.printLine("Ne mancano ancora " + to_string(NEEDED_PIECES - player.getPieces()) + ". Tieni duro");
            getch();
            win.clean();
        } 
    }

    return status;
}

status_t Level::handleBattles(PlayableCharacter& player, Window& bottom, Window& playerInfo, Window& mapWindow)
{
    status_t status = DEFAULT;
    list<Monster> monstersNearby;

    monstersAround(player.getPosition(),monstersNearby);
    if(!monstersNearby.empty())
    {
        for(Monster m : monstersNearby)
            if(Battle(bottom,playerInfo,mapWindow,player,m))  // Returns true upon a win, false upon a loss
            {
                map(m.getPosition()).setUpperLayer("");
                monsters.erase(m.getId());
                printMap(player.getPosition(),mapWindow);
                playerInfo.clear();
                writeInfo(playerInfo,player);
            } 
            else
                status = LOSS;
    }

    return status;
}

void LevelConfig::newLevel()
{
    n++;
    rooms++;
    items = rooms/2;
    monsters = rooms/2;
}

void Level::spawnItems(const int n,const vector<Item>& itemsSet,const int generatedRooms)
{
    int id = 0;
    unordered_set<Point> spots;
    map.freeSpots(n,spots,ceil(static_cast<double>(n)/generatedRooms));
    for(Point p : spots)
    {
        int index = rand(0,min(level*3,static_cast<int>(itemsSet.size())-1));
        Item i = itemsSet[index];
        i.setPosition(p.x,p.y);
        string ID = "item" + to_string(id) + "." + to_string(level);
        i.setId(ID);
        id++;
        map(p.x,p.y).setUpperLayer(ID); // Place an object
        items[ID] = i;
    }
}

void Level::spawnMonsters(const int n, const int generatedRooms)
{
    int id = 0;
    unordered_set<Point> spots;
    vector<Monster> monstersSet = {Monster("Goblin",level),
                                   Monster("Troll",level),
                                   Monster("Golem",level),
                                   Monster("Gineppino",level)};

    map.freeSpots(n,spots,ceil(static_cast<double>(n)/generatedRooms));

    for(Point p : spots)
    {
        int index = rand(0,monstersSet.size()-1);
        Monster m = monstersSet[index];
        m.setPosition(p.x,p.y);
        string ID = "monster" + to_string(id);
        m.setId(ID);
        id++;
        map(p.x,p.y).setUpperLayer(ID); // Spawn a monster
        monsters[ID] = m;
    }
}
