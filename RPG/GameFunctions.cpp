#include "GameFunctions.h"
#include <iostream>
#include <cstdlib>

bool isRunning = true;  // ������ ���� ������ ���θ� ��Ÿ���� ����

// ��ȿ�� �˻� �Լ�
int getInputWithValidation() {
    std::string input;
    while (true) {
        std::cin >> input;

        if (input == "q" || input == "Q") {
            return -1; // "q" �Ǵ� "Q"�� �ԷµǸ� -1 ��ȯ�Ͽ� ���� �޴��� ���ư�
        }
        
        try {
            int value = std::stoi(input); // �Է��� �������� Ȯ��
            return value;  // ���ڶ�� �ش� ���� ��ȯ
        }
        catch (const std::invalid_argument&) {
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �������ּ��� (���ڸ� �Է��ϰų� 'q'�� ���� �����ϼ���.):\n";
        }
    }
}

// �� �ƽ�Ű ��Ʈ ��� �Լ�
void printRoom(int currentRoom, int totalRooms) {
    std::cout << "\n";

    // �� ���� �� �ٿ� ���
    for (int i = 1; i <= totalRooms; ++i) {
        if (i == currentRoom) {
            // ���� �� ���� (�÷��̾� ��ġ ǥ��)
            std::cout << "+---------+ ";
        }
        else {
            std::cout << "+---------+ ";
        }
    }
    std::cout << "\n";

    for (int i = 1; i <= totalRooms; ++i) {
        if (i == currentRoom) {
            std::cout << "|   <+>   | "; // ���� ���� ǥ��
        }
        else {
            std::cout << "|         | ";
        }
    }
    std::cout << "\n";

    for (int i = 1; i <= totalRooms; ++i) {
        std::cout << "+---------+ ";
    }
    std::cout << "\n";
}

// ���� �ƽ�Ű ��Ʈ ��� �Լ�
void printMonster() {
    std::cout << "      ___\n";
    std::cout << "     /   \\ \n";
    std::cout << "    |     | \n";
    std::cout << "    | O O | \n";
    std::cout << "    |  ^  | \n";
    std::cout << "     \\___/ \n";
}

// HP �� ��� �Լ�
void printHealthBar(int currentHealth, int maxHealth) {
    int healthBarLength = 30;  // ���� ���� ����
    int healthUnits = (currentHealth * healthBarLength) / maxHealth;

    std::cout << "[";
    for (int i = 0; i < healthBarLength; i++) {
        if (i < healthUnits) {
            std::cout << "#";
        }
        else {
            std::cout << "-";
        }
    }
    std::cout << "] " << currentHealth << "/" << maxHealth << "\n";
}
// ���� �Լ�
bool battle(Player& player, int currentRoom, int totalRooms) {
    Enemy enemy(50, 10);
    isRunning = true;

    while (player.health > 0 && enemy.health > 0 && isRunning) {
        // ���� �� ���� ���
        //printRoom(currentRoom, totalRooms);

        // ���� ��Ʈ ���
        std::cout << "\n���Ͱ� ��Ÿ�����ϴ�!\n";
        printMonster();

        // �÷��̾�� ���� HP ���
        std::cout << "\n�÷��̾� ü��: ";
        printHealthBar(player.health, player.maxHealth);  // �÷��̾� HP ǥ��
        std::cout << "�� ü��: ";
        printHealthBar(enemy.health, 50);  // �� HP ǥ��

        // ����, ���, ��ų ����
        std::cout << "����� ���ݷ�: " << player.attack << "\t��ų ���ݷ�: " << player.attack * 2;
        if (player.skillCooldown > 0) {
            std::cout << " (��ų ��ٿ�: " << player.skillCooldown << " ��)";
        }

        int MOPaction = rand() % 2;
        
        if (MOPaction == 1) {
            std::cout << "\n���� �� �غ����Դϴ�!\n";
        }
        else {
            std::cout << "\n�� ���ݷ�: " << enemy.attack << "\n";
        }

        std::cout << "1. ����\n2. ���\n3. ��ų ���\n";
        int choice = getInputWithValidation();  // ��ȿ�� �˻� �� �Է�
        if (choice == -1) {
            isRunning = false;  // ���� ����
            return false; // "q" �Է� �� ���� �����ϰ� ���� �޴��� ���ư�
        }

        // �÷��̾� ���ÿ� ���� �ൿ
        if (choice == 1) {
            if (MOPaction == 1) {
                player.attackEnemy(enemy.health);
                enemy.health += player.attack / 2; // ��� ���� ��� ���� ���� ����
                std::cout << "���� ����� ������ ����߽��ϴ�!\n";
            }
            else {
                player.attackEnemy(enemy.health);
            }
        }
        else if (choice == 2) {
            player.defend();
            enemy.attack /= 3;
        }
        else if (choice == 3) {
            player.useSkill(enemy.health);
        }

        if (enemy.health > 0) {
            enemy.takeTurn(player, MOPaction);
        }

        if (choice == 2) {
            enemy.attack *= 3; // ��� �� �� ���ݷ� ����
        }

        if (player.skillCooldown > 0) {
            player.skillCooldown--;
        }

        enemy.resetDefense();
    }

    if (player.health > 0) {
        std::cout << "���� �����ƽ��ϴ�!\n";
        std::cout << "������ �����ϼ���:\n1. ü��ȸ��\n2. ���ݷ� ����\n3. ��ĭ ����\n";
        int reward = getInputWithValidation();  // ���� ���ÿ� ���� ��ȿ�� �˻� �߰�
        std::cout << "������ ������ "<<reward;

        if (reward == -1) {
            return false; // "q" �Է� �� ���� �����ϰ� ���� �޴��� ���ư�
        }

        if (reward == 1) {
            player.health = player.maxHealth;
        }
        else if (reward == 2) {
            player.attack += 5;
        }
        else if (reward == 3) {
            std::cout << "�� ĭ �����Ͽ����ϴ�!\n";
            return true; // �� ���� ���� �ǳʶٱ�� ����
        }
    }
    else {
        std::cout << "�й��Ͽ����ϴ�.���� �޴��� ���ư��ϴ�.\n";
    }
    return false; // �� �ǳʶٱ� ���� ����
}



void rest(Player& player) {
    std::cout << "�޽�ó�� ã�ҽ��ϴ�. �� �� �ϳ��� �����ϼ���:\n1. ü�� �뷮 ȸ��\n2. �������� ��Ÿ�� ����\n";
    int choice = getInputWithValidation();  // ��ȿ�� �˻� �߰�

    if (choice == -1) {
        return; // "q" �Է� �� ��� ����
    }

    if (choice == 1) {
        player.health += 30;
        if (player.health > player.maxHealth) {
            player.health = player.maxHealth;
        }
    }
    else if (choice == 2) {
        std::cout << "������ ��Ÿ�� ���Ҹ� �����Ͽ����ϴ�.\n";
        player.reduceCooldown(); // ��ٿ��� 1 ���ҽ�Ŵ
    }
}


void bossBattle(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar) {
    Enemy boss(100, 15);
    while (player.health > 0 && boss.health > 0) {

        std::cout << "   .:                    ;    \n";
        std::cout << "   :@.    .~:=@@=:~.    ~@,   \n";
        std::cout << "   @=@  ,=@$=*!!*=#@!, .@@*   \n";
        std::cout << "   @ @~$@$         .#@~@$-@   \n";
        std::cout << "   @ .@@             ,@#  @   \n";
        std::cout << "   @.@;                @##@   \n";
        std::cout << "   @@;                 .@@-   \n";
        std::cout << "   $@                    @-   \n";
        std::cout << "  -@  @@@=~        ;$@@# ~@.  \n";
        std::cout << "  =$    ,;@*     .$#:.    #~  \n";
        std::cout << " .@       .=$    #=       :@  \n";
        std::cout << " ~$     ,~  #!  #= .~      @, \n";
        std::cout << " :=     =@#,,;  *.,@@*     $: \n";
        std::cout << " $*     *@@=      @@@*     =: \n";
        std::cout << " @!      @@@     -@@@      =: \n";
        std::cout << " @!       =*      $;.      =: \n";
        std::cout << " =*                        =~ \n";
        std::cout << " :=                        #~ \n";
        std::cout << " :#     @@$*******=#@@     @. \n";
        std::cout << " .@.    @;=$;;;;;;@!!=    !#  \n";
        std::cout << "  *#    *!$!      *;#;    #-  \n";
        std::cout << "  ,@,   -@@       :@@    :@   \n";
        std::cout << "   :@    *$        @;   ,@,   \n";


        std::cout << "\n�÷��̾� ü��: ";
        printHealthBar(player.health, player.maxHealth);  // �÷��̾� HP ǥ��
        std::cout << "���� ü��: ";
        printHealthBar(boss.health, 100);  // ���� HP ǥ��

        std::cout << "����� ���ݷ�: " << player.attack << "\t��ų ������: " << player.attack * 2;
        if (player.skillCooldown > 0) {
            std::cout << " (���� ��ٿ�: " << player.skillCooldown << " ��)";
        }

        int MOPaction = rand() % 2;

        if (MOPaction == 1) {
            std::cout << "\n������ ����Ϸ� �մϴ�!\n";
        }

        else {
            std::cout << "\n���� ���ݷ�: " << boss.attack << "\n";
        }

        std::cout << "1. ����\n2. ���\n3. ��ų ���\n";
        int choice = getInputWithValidation();  // ��ȿ�� �˻� �߰�

        if (choice == -1) {
            return; // "q" �Է� �� ���� ���� �����ϰ� ���� �޴��� ���ư�
        }

        if (choice == 1) {
            if (MOPaction == 1) {
                player.attackEnemy(boss.health);
                boss.health += player.attack / 10; // ������ ��� ���̶�� ���� ũ�� ����
                std::cout << "������ ������κ��� �޴� ���ظ� ���ҽ��׽��ϴ�.!\n";
            }
            else {
                player.attackEnemy(boss.health);
            }
        }
        else if (choice == 2) {
            player.defend();
            boss.attack /= 2;
        }
        else if (choice == 3) {
            player.useSkill(boss.health);
        }

        if (boss.health > 0) {
            boss.takeTurn(player, MOPaction);
        }

        if (choice == 2) {
            boss.attack *= 2; // ��� �� ������ ���ݷ� ����
        }

        if (player.skillCooldown > 0) {
            player.skillCooldown--;
        }

        boss.resetDefense();
    }

    if (player.health > 0) {
        std::cout << "�����մϴ�! ����� ������ �����ƽ��ϴ�.!\n";
        if (difficulty == "����") easyStar = true;
        if (difficulty == "����") mediumStar = true;
        if (difficulty == "�����") hardStar = true;
    }
    else {
        std::cout << "����� �й��߽��ϴ�. ���θ޴��� ���ư��ϴ�.\n";
    }
}

void difficultySelection(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar) {
    int choice;
    std::cout << "���� ������ �����ϼ���:\n1. ����\n2. ����\n3. �����\n ��Ÿ ���ڸ� ������ �ְ� ���̵��� ���õ˴ϴ�.\n";
    choice = getInputWithValidation();  // ��ȿ�� �˻� �߰�

    if (choice == -1) {
        return; // "q" �Է� �� ��� ����
    }

    if (choice == 1) {
        player.health = 100;
        player.attack = 15;
        player.skillCooldown = 3;
        difficulty = "����";
    }
    else if (choice == 2) {
        player.health = 75;
        player.attack = 10;
        player.skillCooldown = 3;
        difficulty = "����";
    }
    else {
        player.health = 50;
        player.attack = 8;
        player.skillCooldown = 3;
        difficulty = "�����";
    }

    player.maxHealth = player.health;
    easyStar = mediumStar = hardStar = false; // ���̵� �Ϸ� �÷��� �ʱ�ȭ
}
