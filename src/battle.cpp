#include "../include/battle.h"
#include "../include/Monster.h"
#include "../include/Level.h"
#include <iostream>
#include <string>
#include <unistd.h>

int Battle(Window& battle_win, Window& right_win, PlayableCharacter& player, int level,std::list<Monster>& list){

    using namespace std;
    char c;
    Monster m;

    while (!list.empty()){
        m = list.front();

        battle_win.printLine("Per iniziare la battaglia premere a, per consultare l'inventario premere s");

        while ((m.getLP() > 0) && (player.getLP() > 0)) {

            do
            {
                battle_win.clear();
                battle_win.printLine("Premere un tasto valido: ");
                c = getch();
            } while ((c != 'a') && (c != 's')); 

            battle_win.clear();

            switch (c) {
                case 'a':

                    battle_win.printLine("Battaglia con " + m.getName() + ":");
                    battle_win.printLine("");
                    battle_win.printLine("PUNTI VITA -> " + to_string(m.getLP()));
                    battle_win.printLine("ATTACCO -> " + to_string(m.getATK()));
                    battle_win.printLine("DIFESA -> " + to_string(m.getDEF()));

                    sleep(1);   // alternatively getch() press a key to continue

                    if (Critical_Atk(player.getLuck()) == 1){
                        m.setLP(m.getLP() - Atk_Def(m.getDEF(), (2 * player.getATK())));
                        battle_win.printLine("");
                        battle_win.printLine("COLPO CRITICO");
                    }
                    else
                        m.setLP(m.getLP() - Atk_Def(m.getDEF(), player.getATK()));

                    if (m.getLP() < 0)
                        m.setLP(0);

                    battle_win.clear();

                    battle_win.printLine("Battaglia con " + m.getName() + ":");
                    battle_win.printLine("");
                    battle_win.printLine("PUNTI VITA -> " + to_string(m.getLP()));
                    battle_win.printLine("ATTACCO -> " + to_string(m.getATK()));
                    battle_win.printLine("DIFESA -> " + to_string(m.getDEF()));

                    sleep(2);

                    break;

                case 's':
                    //funzione che richiama l'inventario
                    break;
            }

            if (m.getLP() > 0) {
                battle_win.clear();
                battle_win.printLine("L'avversario ti attacca!");

                getch();

                player.setLP(player.getLP() - Atk_Def(player.getDEF(), m.getATK()));

                if (player.getLP() <= 0)
                    player.setLP(0);

                writeInfo(right_win, player,level);

                battle_win.printLine("");
                battle_win.printLine("L'attacco del nemico ti toglie -> " + to_string(Atk_Def(player.getDEF(), m.getATK())) + " LP");
            }

            sleep(2);
        }

        if (m.getLP() <= 0) {
            battle_win.clear();
            battle_win.printLine("!VITTORIA!");
            //mvprintw(4, 44,);
            list.pop_front();
        }
        else if (player.getLP() <= 0){
            battle_win.clear();
            battle_win.printLine("SEI STATO SCONFITTO!");
            return 0;
            //mvprintw(4, 39, "");
        }
    }

    return 1;
}

int Atk_Def (int def, int atk) {
    return  (int)(atk -  (double)(atk * def) / 100);           // fare il casting
}

int Critical_Atk (int luck){
    
    int i=0;

    i = rand() % 100;
    
    if (i <= luck)    // se i <= della fortuna del pg allora viene effettuato il critico (atk*2)
        return 1;
    else
        return 0;
}
