#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "Player.h"
#include "Enemy.h"
#include <string>

void difficultySelection(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar);
void battle(Player& player);
void rest(Player& player);
void bossBattle(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar);

#endif // GAME_UTILS_H
