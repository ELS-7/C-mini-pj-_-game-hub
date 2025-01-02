#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "Player.h"
#include "Enemy.h"
#include <string>

bool battle(Player& player, int currentRoom, int totalRooms);
void rest(Player& player);
void bossBattle(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar);
void difficultySelection(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar);

// �� �ƽ�Ű ��Ʈ ��� �Լ�
void printRoom(int currentRoom, int totalRooms);

// ���� �ƽ�Ű ��Ʈ ��� �Լ�
void printMonster();

// HP �� ��� �Լ�
void printHealthBar(int currentHealth, int maxHealth);


#endif // GAME_FUNCTIONS_H
