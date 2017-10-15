#ifndef BATTLE_H
#define BATTLE_H
#include <iostream>
#include <time.h>
#include <list>
#include "Monster.h"
#include "personaggiGiocabili.h"
#include "Window.h"

int Battle (Window& battle_win, Window& right_win, PlayableCharacter& player, int level,std::list<Monster>& list);

int Atk_Def (int def, int atk);

int Critical_Atk (int luck);

#endif
