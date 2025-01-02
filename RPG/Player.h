#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int health;
    int attack;
    int skillCooldown; // 현재 쿨다운
    int skillCooldownBase; // 기본 쿨다운 (3으로 초기화)
    int maxHealth;

    Player(int health, int attack, int skillCooldown);
    void useSkill(int& enemyHealth);
    void attackEnemy(int& enemyHealth);
    void defend();
    void reduceCooldown(); // 쿨다운 감소 함수 추가
};

#endif
