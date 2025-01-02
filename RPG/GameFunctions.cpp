#include "GameFunctions.h"
#include <iostream>
#include <cstdlib>

bool isRunning = true;  // 게임이 실행 중인지 여부를 나타내는 변수

// 유효성 검사 함수
int getInputWithValidation() {
    std::string input;
    while (true) {
        std::cin >> input;

        if (input == "q" || input == "Q") {
            return -1; // "q" 또는 "Q"가 입력되면 -1 반환하여 메인 메뉴로 돌아감
        }
        
        try {
            int value = std::stoi(input); // 입력이 숫자인지 확인
            return value;  // 숫자라면 해당 값을 반환
        }
        catch (const std::invalid_argument&) {
            std::cout << "잘못된 입력입니다. 다시 선택해주세요 (숫자를 입력하거나 'q'를 눌러 종료하세요.):\n";
        }
    }
}

// 방 아스키 아트 출력 함수
void printRoom(int currentRoom, int totalRooms) {
    std::cout << "\n";

    // 각 방을 한 줄에 출력
    for (int i = 1; i <= totalRooms; ++i) {
        if (i == currentRoom) {
            // 현재 방 강조 (플레이어 위치 표시)
            std::cout << "+---------+ ";
        }
        else {
            std::cout << "+---------+ ";
        }
    }
    std::cout << "\n";

    for (int i = 1; i <= totalRooms; ++i) {
        if (i == currentRoom) {
            std::cout << "|   <+>   | "; // 현재 방의 표시
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

// 몬스터 아스키 아트 출력 함수
void printMonster() {
    std::cout << "      ___\n";
    std::cout << "     /   \\ \n";
    std::cout << "    |     | \n";
    std::cout << "    | O O | \n";
    std::cout << "    |  ^  | \n";
    std::cout << "     \\___/ \n";
}

// HP 바 출력 함수
void printHealthBar(int currentHealth, int maxHealth) {
    int healthBarLength = 30;  // 길이 조정 가능
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
// 전투 함수
bool battle(Player& player, int currentRoom, int totalRooms) {
    Enemy enemy(50, 10);
    isRunning = true;

    while (player.health > 0 && enemy.health > 0 && isRunning) {
        // 현재 방 상태 출력
        //printRoom(currentRoom, totalRooms);

        // 몬스터 아트 출력
        std::cout << "\n몬스터가 나타났습니다!\n";
        printMonster();

        // 플레이어와 적의 HP 출력
        std::cout << "\n플레이어 체력: ";
        printHealthBar(player.health, player.maxHealth);  // 플레이어 HP 표시
        std::cout << "적 체력: ";
        printHealthBar(enemy.health, 50);  // 적 HP 표시

        // 공격, 방어, 스킬 선택
        std::cout << "당신의 공격력: " << player.attack << "\t스킬 공격력: " << player.attack * 2;
        if (player.skillCooldown > 0) {
            std::cout << " (스킬 쿨다운: " << player.skillCooldown << " 턴)";
        }

        int MOPaction = rand() % 2;
        
        if (MOPaction == 1) {
            std::cout << "\n적이 방어를 준비중입니다!\n";
        }
        else {
            std::cout << "\n적 공격력: " << enemy.attack << "\n";
        }

        std::cout << "1. 공격\n2. 방어\n3. 스킬 사용\n";
        int choice = getInputWithValidation();  // 유효성 검사 후 입력
        if (choice == -1) {
            isRunning = false;  // 전투 종료
            return false; // "q" 입력 시 전투 종료하고 메인 메뉴로 돌아감
        }

        // 플레이어 선택에 따른 행동
        if (choice == 1) {
            if (MOPaction == 1) {
                player.attackEnemy(enemy.health);
                enemy.health += player.attack / 2; // 방어 중인 경우 피해 절반 감소
                std::cout << "적은 당신의 공격을 방어했습니다!\n";
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
            enemy.attack *= 3; // 방어 후 적 공격력 복구
        }

        if (player.skillCooldown > 0) {
            player.skillCooldown--;
        }

        enemy.resetDefense();
    }

    if (player.health > 0) {
        std::cout << "적을 물리쳤습니다!\n";
        std::cout << "보상을 선택하세요:\n1. 체력회복\n2. 공격력 증가\n3. 두칸 전진\n";
        int reward = getInputWithValidation();  // 보상 선택에 대해 유효성 검사 추가
        std::cout << "선택한 리워드 "<<reward;

        if (reward == -1) {
            return false; // "q" 입력 시 전투 종료하고 메인 메뉴로 돌아감
        }

        if (reward == 1) {
            player.health = player.maxHealth;
        }
        else if (reward == 2) {
            player.attack += 5;
        }
        else if (reward == 3) {
            std::cout << "두 칸 전진하였습니다!\n";
            return true; // 두 개의 방을 건너뛰기로 선택
        }
    }
    else {
        std::cout << "패배하였습니다.메인 메뉴로 돌아갑니다.\n";
    }
    return false; // 방 건너뛰기 선택 안함
}



void rest(Player& player) {
    std::cout << "휴식처를 찾았습니다. 둘 중 하나를 선택하세요:\n1. 체력 대량 회복\n2. 영구적인 쿨타임 감소\n";
    int choice = getInputWithValidation();  // 유효성 검사 추가

    if (choice == -1) {
        return; // "q" 입력 시 즉시 종료
    }

    if (choice == 1) {
        player.health += 30;
        if (player.health > player.maxHealth) {
            player.health = player.maxHealth;
        }
    }
    else if (choice == 2) {
        std::cout << "영구적 쿨타임 감소를 선택하였습니다.\n";
        player.reduceCooldown(); // 쿨다운을 1 감소시킴
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


        std::cout << "\n플레이어 체력: ";
        printHealthBar(player.health, player.maxHealth);  // 플레이어 HP 표시
        std::cout << "보스 체력: ";
        printHealthBar(boss.health, 100);  // 보스 HP 표시

        std::cout << "당신의 공격력: " << player.attack << "\t스킬 데미지: " << player.attack * 2;
        if (player.skillCooldown > 0) {
            std::cout << " (남은 쿨다운: " << player.skillCooldown << " 번)";
        }

        int MOPaction = rand() % 2;

        if (MOPaction == 1) {
            std::cout << "\n보스가 방어하려 합니다!\n";
        }

        else {
            std::cout << "\n보스 공격력: " << boss.attack << "\n";
        }

        std::cout << "1. 공격\n2. 방어\n3. 스킬 사용\n";
        int choice = getInputWithValidation();  // 유효성 검사 추가

        if (choice == -1) {
            return; // "q" 입력 시 보스 전투 종료하고 메인 메뉴로 돌아감
        }

        if (choice == 1) {
            if (MOPaction == 1) {
                player.attackEnemy(boss.health);
                boss.health += player.attack / 10; // 보스가 방어 중이라면 피해 크게 감소
                std::cout << "보스가 당신으로부터 받는 피해를 감소시켰습니다.!\n";
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
            boss.attack *= 2; // 방어 후 보스의 공격력 복구
        }

        if (player.skillCooldown > 0) {
            player.skillCooldown--;
        }

        boss.resetDefense();
    }

    if (player.health > 0) {
        std::cout << "축하합니다! 당신은 보스를 물리쳤습니다.!\n";
        if (difficulty == "쉬움") easyStar = true;
        if (difficulty == "보통") mediumStar = true;
        if (difficulty == "어려움") hardStar = true;
    }
    else {
        std::cout << "당신은 패배했습니다. 메인메뉴로 돌아갑니다.\n";
    }
}

void difficultySelection(Player& player, std::string& difficulty, bool& easyStar, bool& mediumStar, bool& hardStar) {
    int choice;
    std::cout << "게임 수준을 선택하세요:\n1. 쉬움\n2. 보통\n3. 어려움\n 기타 숫자를 누르면 최고 난이도가 선택됩니다.\n";
    choice = getInputWithValidation();  // 유효성 검사 추가

    if (choice == -1) {
        return; // "q" 입력 시 즉시 종료
    }

    if (choice == 1) {
        player.health = 100;
        player.attack = 15;
        player.skillCooldown = 3;
        difficulty = "쉬움";
    }
    else if (choice == 2) {
        player.health = 75;
        player.attack = 10;
        player.skillCooldown = 3;
        difficulty = "보통";
    }
    else {
        player.health = 50;
        player.attack = 8;
        player.skillCooldown = 3;
        difficulty = "어려움";
    }

    player.maxHealth = player.health;
    easyStar = mediumStar = hardStar = false; // 난이도 완료 플래그 초기화
}
