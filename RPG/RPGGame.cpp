#include "Player.h"
#include "GameFunctions.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

void startRPG() {
    srand(time(0));
    Player player(0, 0, 0);
    std::string difficulty;
    bool easyStar = false, mediumStar = false, hardStar = false;

    while (true) {
        std::cout << "Welcome to the RPG!\n";
        std::cout << "1. 게임 시작\n";
        std::cout << "   쉬움" << (easyStar ? " *" : "") << "\n";
        std::cout << "   보통" << (mediumStar ? " *" : "") << "\n";
        std::cout << "   어려움" << (hardStar ? " *" : "") << "\n";
        std::cout << "2. 종료\n";
        std::cout << "선택하세요(종료하시려면 'q' 를 누르세요): ";

        std::string choice;
        std::cin >> choice;

        if (choice == "q") {
            // 게임 종료
            std::cout << "Exiting to main menu...\n";
            break;
        }

        if (choice == "1") {
            // 난이도 선택 및 초기화
            difficultySelection(player, difficulty, easyStar, mediumStar, hardStar);

            for (int room = 1; room <= 5; ++room) {
                std::cout << "\n" << room << "번 방에 입장했습니다.\n";

                // 현재 방 상태 출력
                printRoom(room, 5);

                // 방 이벤트 발생
                int event = rand() % 3;

                if (room == 5) {
                    // 보스 방
                    std::cout << "최종 보스 등장이요!\n";
                    bossBattle(player, difficulty, easyStar, mediumStar, hardStar);
                    break;
                }
                else if (event == 0 || event == 2) {
                    // 전투 이벤트
                    bool nextRoom = battle(player, room, 5);  // 전투 후 반환값 처리
                    //if (!nextRoom) {
                    //    std::cout << "You chose to quit. Returning to the main menu...\n";
                    //    break;  // "q"가 입력되면 전투를 종료하고 메인 메뉴로 돌아감
                    //}
                    if (nextRoom && room!=4) {
                        // 전투 후 방을 건너뛴 경우
                        room += 1;  // 방을 건너뛰고 진행
                    }
                }
                else if (event == 1) {
                    // 휴식 이벤트
                    std::cout << "휴식처를 찾았습니다.\n";
                    rest(player);
                }

                // 플레이어가 사망했을 경우
                if (player.health <= 0) {
                    std::cout << "사망했습니다. 메인 화면으로 돌아갑니다...\n";
                    break;
                }
            }
        }
        else if (choice == "2") {
            // 게임 종료
            std::cout << "플레이 해주셔서 감사합니다! Goodbye!\n";
            break;
        }
        else {
            // 잘못된 입력
            std::cout << "잘못된 선택입니다. 다시 선택해주십시오.\n";
            break;
        }
    }
    std::cout << "RPG Game Over!\n";
}
