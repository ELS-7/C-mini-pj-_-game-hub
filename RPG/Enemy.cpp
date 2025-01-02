#include "Enemy.h"
#include <iostream>
#include <cstdlib>

Enemy::Enemy(int health, int attack) : health(health), attack(attack), defending(false) {}




void Enemy::takeTurn(Player& player, int MOPaction) {
    if (MOPaction == 0) {
        defending = false;
        std::cout << "���� ����� �����մϴ�!\n";
        player.health -= attack;
    }
    else {
        defend();
    }
}


void Enemy::defend() {
    defending = true;
    std::cout << "���� ����߽��ϴ�, �޴� �������� �������� �����߽��ϴ�!\n";
}

void Enemy::resetDefense() {
    defending = false;
}