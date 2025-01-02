#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

const int WIDTH = 20;   // �� �ʺ�
const int HEIGHT = 16;  // �� ����

struct Position {
    int x, y;
};

// �� ���� ����
void startSnakeGame() {
    // ���� �ʱ�ȭ
    std::vector<Position> snake = { {WIDTH / 2, HEIGHT / 2} }; // ���� �ʱ� ��ġ
    Position apple = { rand() % WIDTH, rand() % HEIGHT };      // ù ��� ��ġ
    Position direction = { 0, -1 };                           // �ʱ� ���� (����)
    bool running = true;
    bool ateApple = false;
    int score = 0;

    // ���� ���� ����
    while (running) {
        // ȭ�� �ʱ�ȭ
        std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, ' '));

        // �� �߰�
        for (int x = 0; x < WIDTH; ++x) {
            grid[0][x] = '#';
            grid[HEIGHT - 1][x] = '#';
        }
        for (int y = 0; y < HEIGHT; ++y) {
            grid[y][0] = '#';
            grid[y][WIDTH - 1] = '#';
        }

        // ��� �׸���
        grid[apple.y][apple.x] = 'O';

        // �� �׸���
        for (const auto& segment : snake) {
            grid[segment.y][segment.x] = '*';
        }

        // ȭ�� ���
        system("cls");
        for (const auto& row : grid) {
            for (const char cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
        std::cout << "����: " << score << "\n";
        std::cout << "���� ���: W (��), A (����), S (�Ʒ�), D (������), Q (����)\n";

        // �Է� ó��
        if (_kbhit()) {
            char input = _getch();
            if (input == 'w' && direction.y == 0) direction = { 0, -1 };
            if (input == 's' && direction.y == 0) direction = { 0, 1 };
            if (input == 'a' && direction.x == 0) direction = { -1, 0 };
            if (input == 'd' && direction.x == 0) direction = { 1, 0 };
            if (input == 'q') {
                running = false;
                break;
            }
        }

        // �� �̵�
        Position newHead = { snake.front().x + direction.x, snake.front().y + direction.y };
        snake.insert(snake.begin(), newHead);

        // �浹 ó��: ��
        if (newHead.x <= 0 || newHead.x >= WIDTH - 1 || newHead.y <= 0 || newHead.y >= HEIGHT - 1) {
            running = false;
            break;
        }

        // �浹 ó��: �ڱ� ��
        for (size_t i = 1; i < snake.size(); ++i) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                running = false;
                break;
            }
        }

        // ��� �Ա�
        if (newHead.x == apple.x && newHead.y == apple.y) {
            ateApple = true;
            score += 10;
            apple = { rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1 };
        }

        // ���� ���� (����� ���� ���� ���)
        if (!ateApple) {
            snake.pop_back();
        }
        else {
            ateApple = false;
        }

        // �ӵ� ����
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // ���� ���� �޽���
    system("cls");
    std::cout << "���� ����! ����� ����: " << score << "\n";
    std::cout << "���� �޴��� ���ư����� �ƹ� Ű�� ��������.\n";
    _getch();
}
