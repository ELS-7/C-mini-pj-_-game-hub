#include "Enemy.h"
#include <iostream>
#include <cstdlib>

Enemy::Enemy(int health, int attack) : health(health), attack(attack), defending(false) {}




void Enemy::takeTurn(Player& player, int MOPaction) {
    if (MOPaction == 0) {
        defending = false;
        std::cout << "적이 당신을 공격합니다!\n";
        player.health -= attack;
    }
    else {
        defend();
    }
}


void Enemy::defend() {
    defending = true;
    std::cout << "적이 방어했습니다, 받는 데미지가 절반으로 감소했습니다!\n";
}

void Enemy::resetDefense() {
    defending = false;
}