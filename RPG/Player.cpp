#include "Player.h"
#include <iostream>

Player::Player(int health, int attack, int skillCooldown)
    : health(health), attack(attack), skillCooldown(skillCooldown), skillCooldownBase(3), maxHealth(health) {
}

void Player::useSkill(int& enemyHealth) {
    if (skillCooldown == 0) {
        std::cout << "����� ������ ��ų�� ����߽��ϴ�!\n";
        enemyHealth -= attack * 2;
        skillCooldown = skillCooldownBase; // ��ų ��� �� �⺻ ��ٿ� ������ �缳��
    }
    else {
        std::cout << "��ų ��ٿ� " << skillCooldown << ".\n";
    }
}

void Player::attackEnemy(int& enemyHealth) {
    std::cout << "���� �����մϴ�!\n";
    enemyHealth -= attack;
}

void Player::defend() {
    std::cout << "����մϴ�. �޴� �������� �������� ���ҽ�ŵ�ϴ�!\n";
}

void Player::reduceCooldown() {
    if (skillCooldown > 0) {
        skillCooldown--; // ��ٿ� ����
    }
}
