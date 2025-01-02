#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "Player.h"
#include "Enemy.h"
#include <string>

bool battle(Player& player, int currentRoom, int totalRooms);
void rest(Player& player);
void bossBattle(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar);
void difficultySelection(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar);

// 방 아스키 아트 출력 함수
void printRoom(int currentRoom, int totalRooms);

// 몬스터 아스키 아트 출력 함수
void printMonster();

// HP 바 출력 함수
void printHealthBar(int currentHealth, int maxHealth);


#endif // GAME_FUNCTIONS_H
