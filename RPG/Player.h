#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int health;
    int attack;
    int skillCooldown; // ���� ��ٿ�
    int skillCooldownBase; // �⺻ ��ٿ� (3���� �ʱ�ȭ)
    int maxHealth;

    Player(int health, int attack, int skillCooldown);
    void useSkill(int& enemyHealth);
    void attackEnemy(int& enemyHealth);
    void defend();
    void reduceCooldown(); // ��ٿ� ���� �Լ� �߰�
};

#endif
