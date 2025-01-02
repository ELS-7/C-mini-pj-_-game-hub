#include <iostream>

// 각 게임의 시작 함수 선언
void startRPG();
void startWallBreak();
void startSnakeGame();

int main() {
    while (true) {
        std::cout << "\n=== Game Hub ===\n";
        std::cout << "1. RPG Game\n";
        std::cout << "2. 벽돌깨기\n";
        std::cout << "3. 뱀꼬리잡기\n";
        std::cout << "4. Exit\n";
        std::cout << "게임을 선택하세요: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            startRPG();
            break;
        case 2:
            startWallBreak();
            break;
        case 3:
            startSnakeGame();
            break;
        case 4:
            std::cout << "게임 허브 종료!\n";
            return 0;
        default:
            std::cout << "다시 선택해주세요.\n";
        }
    }

    return 0;
}
