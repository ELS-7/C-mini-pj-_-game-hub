#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy {
public:
    int health;
    int attack;
    bool defending;
    Enemy(int health, int attack);
    void takeTurn(Player& player, int MOPaction);
    void defend();
    void resetDefense();
};

#endif