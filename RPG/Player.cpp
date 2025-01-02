#include "Player.h"
#include <iostream>

Player::Player(int health, int attack, int skillCooldown)
    : health(health), attack(attack), skillCooldown(skillCooldown), skillCooldownBase(3), maxHealth(health) {
}

void Player::useSkill(int& enemyHealth) {
    if (skillCooldown == 0) {
        std::cout << "당신은 강력한 스킬을 사용했습니다!\n";
        enemyHealth -= attack * 2;
        skillCooldown = skillCooldownBase; // 스킬 사용 후 기본 쿨다운 값으로 재설정
    }
    else {
        std::cout << "스킬 쿨다운 " << skillCooldown << ".\n";
    }
}

void Player::attackEnemy(int& enemyHealth) {
    std::cout << "적을 공격합니다!\n";
    enemyHealth -= attack;
}

void Player::defend() {
    std::cout << "방어합니다. 받는 데미지를 절반으로 감소시킵니다!\n";
}

void Player::reduceCooldown() {
    if (skillCooldown > 0) {
        skillCooldown--; // 쿨다운 감소
    }
}
