#include <iostream>

// �� ������ ���� �Լ� ����
void startRPG();
void startWallBreak();
void startSnakeGame();

int main() {
    while (true) {
        std::cout << "\n=== Game Hub ===\n";
        std::cout << "1. RPG Game\n";
        std::cout << "2. ��������\n";
        std::cout << "3. �첿�����\n";
        std::cout << "4. Exit\n";
        std::cout << "������ �����ϼ���: ";

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
            std::cout << "���� ��� ����!\n";
            return 0;
        default:
            std::cout << "�ٽ� �������ּ���.\n";
        }
    }

    return 0;
}
