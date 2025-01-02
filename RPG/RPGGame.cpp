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
        std::cout << "1. ���� ����\n";
        std::cout << "   ����" << (easyStar ? " *" : "") << "\n";
        std::cout << "   ����" << (mediumStar ? " *" : "") << "\n";
        std::cout << "   �����" << (hardStar ? " *" : "") << "\n";
        std::cout << "2. ����\n";
        std::cout << "�����ϼ���(�����Ͻ÷��� 'q' �� ��������): ";

        std::string choice;
        std::cin >> choice;

        if (choice == "q") {
            // ���� ����
            std::cout << "Exiting to main menu...\n";
            break;
        }

        if (choice == "1") {
            // ���̵� ���� �� �ʱ�ȭ
            difficultySelection(player, difficulty, easyStar, mediumStar, hardStar);

            for (int room = 1; room <= 5; ++room) {
                std::cout << "\n" << room << "�� �濡 �����߽��ϴ�.\n";

                // ���� �� ���� ���
                printRoom(room, 5);

                // �� �̺�Ʈ �߻�
                int event = rand() % 3;

                if (room == 5) {
                    // ���� ��
                    std::cout << "���� ���� �����̿�!\n";
                    bossBattle(player, difficulty, easyStar, mediumStar, hardStar);
                    break;
                }
                else if (event == 0 || event == 2) {
                    // ���� �̺�Ʈ
                    bool nextRoom = battle(player, room, 5);  // ���� �� ��ȯ�� ó��
                    //if (!nextRoom) {
                    //    std::cout << "You chose to quit. Returning to the main menu...\n";
                    //    break;  // "q"�� �ԷµǸ� ������ �����ϰ� ���� �޴��� ���ư�
                    //}
                    if (nextRoom && room!=4) {
                        // ���� �� ���� �ǳʶ� ���
                        room += 1;  // ���� �ǳʶٰ� ����
                    }
                }
                else if (event == 1) {
                    // �޽� �̺�Ʈ
                    std::cout << "�޽�ó�� ã�ҽ��ϴ�.\n";
                    rest(player);
                }

                // �÷��̾ ������� ���
                if (player.health <= 0) {
                    std::cout << "����߽��ϴ�. ���� ȭ������ ���ư��ϴ�...\n";
                    break;
                }
            }
        }
        else if (choice == "2") {
            // ���� ����
            std::cout << "�÷��� ���ּż� �����մϴ�! Goodbye!\n";
            break;
        }
        else {
            // �߸��� �Է�
            std::cout << "�߸��� �����Դϴ�. �ٽ� �������ֽʽÿ�.\n";
            break;
        }
    }
    std::cout << "RPG Game Over!\n";
}
