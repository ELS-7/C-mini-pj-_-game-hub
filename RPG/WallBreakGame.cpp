#include <iostream>
#include <vector>
#include <conio.h> // _kbhit()�� _getch() ���
#include <thread>
#include <chrono>
#include <string>  // std::stoi ���

const int WIDTH = 30;
const int HEIGHT = 20;

struct Ball {
    int x, y;
    int dx, dy;
};

struct Paddle {
    int x;
    int width;
};

void draw(const std::vector<std::vector<char>>& screen) {
    system("cls"); // �ܼ� ȭ�� �����
    for (const auto& row : screen) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
}

void updateScreen(std::vector<std::vector<char>>& screen, const Ball& ball, const Paddle& paddle, const std::vector<std::pair<int, int>>& bricks) {
    // ȭ�� �ʱ�ȭ
    for (auto& row : screen) {
        std::fill(row.begin(), row.end(), ' ');
    }

    // ���� ��ġ
    for (const auto& brick : bricks) {
        screen[brick.second][brick.first] = '#';
    }

    // �� ��ġ
    screen[ball.y][ball.x] = 'O';

    // �е� ��ġ (���� 8)
    for (int i = 0; i < paddle.width; ++i) {
        screen[HEIGHT - 1][paddle.x + i] = '=';
    }
}

bool playWallBreak() {
    std::vector<std::vector<char>> screen(HEIGHT, std::vector<char>(WIDTH, ' '));

    // �ʱ� ����
    Ball ball = { WIDTH / 2, HEIGHT / 2, 1, -1 };
    Paddle paddle = { WIDTH / 2 - 4, 8 }; // �е� ���� 8�� ����
    std::vector<std::pair<int, int>> bricks;

    // ���� �ʱ�ȭ
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < WIDTH; x += 3) {
            bricks.emplace_back(x, y);
        }
    }

    bool running = true;

    while (running) {
        // �Է� ó��
        if (_kbhit()) {
            char input = _getch();
            if (input == 'a' && paddle.x > 0) paddle.x--;
            if (input == 'd' && paddle.x + paddle.width < WIDTH) paddle.x++;
            if (input == 'q') return false; // ��� ���� �������� ���ư�
        }

        // �� ������
        ball.x += ball.dx;
        ball.y += ball.dy;

        // �浹 ó��: ���
        if (ball.x <= 0 || ball.x >= WIDTH - 1) ball.dx = -ball.dx;
        if (ball.y <= 0) ball.dy = -ball.dy;

        // �浹 ó��: �е�
        if (ball.y == HEIGHT - 2 && ball.x >= paddle.x && ball.x < paddle.x + paddle.width) {
            ball.dy = -ball.dy;
        }

        // �浹 ó��: ����
        for (auto it = bricks.begin(); it != bricks.end();) {
            if (ball.x == it->first && ball.y == it->second) {
                ball.dy = -ball.dy;
                it = bricks.erase(it); // ���� ����
            }
            else {
                ++it;
            }
        }

        // ���� �Ʒ��� �������� ���� ����
        if (ball.y >= HEIGHT - 1) {
            running = false;
        }

        // ȭ�� ����
        updateScreen(screen, ball, paddle, bricks);
        draw(screen);

        // �ӵ� ����
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return true; // ���������� ���� ����
}

void startWallBreak() {
    while (true) {
        // �ȳ� ȭ�� ���
        std::cout << "\n=== ���� ���� ===\n";
        std::cout << "1. ���� ����\n";
        std::cout << "2. ���� �޴��� ���ư���\n";
        std::cout << "���� ���:\n";
        std::cout << "- 'a'�� ���� �������� �̵�.\n";
        std::cout << "- 'd'�� ���� ���������� �̵�.\n";
        std::cout << "- ���� �� 'q'�� ���� ����.\n";
        std::cout << "�ɼ��� �����ϼ���: ";

        std::string input;
        std::cin >> input;

        // �Է��� 'q'�� ��� ���� �޴��� ��� ����
        if (input == "q") {
            std::cout << "���� �޴��� ���ư��ϴ�...\n";
            break;
        }

        // ���� �Է� Ȯ��
        int choice;
        try {
            choice = std::stoi(input); // ���ڿ��� ���ڷ� ��ȯ
        }
        catch (...) {
            std::cout << "�߸��� �Է��Դϴ�. 1, 2 �Ǵ� 'q'�� �Է����ּ���.\n";
            continue; // �ٽ� �Է� �ޱ�
        }

        if (choice == 1) {
            if (!playWallBreak()) {
                break; // ���� �� 'q'�� ���� ���� �޴��� ���ư�
            }
            std::cout << "\n���� ����!\n";
            std::cout << "1. �����\n2. ���� �޴��� ���ư���\n";
            std::cin >> input;

            if (input == "1") {
                continue; // ���� �����
            }
            else if (input == "2") {
                break; // ���� �޴��� ���ư�
            }
            else {
                std::cout << "�߸��� �����Դϴ�. ���� �޴��� �����մϴ�.\n";
                break;
            }
        }
        else if (choice == 2) {
            break; // ���� �޴��� ���ư�
        }
        else {
            std::cout << "�߸��� �����Դϴ�. 1, 2 �Ǵ� 'q'�� �Է����ּ���.\n";
        }
    }
}
