#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

const int WIDTH = 20;   // 맵 너비
const int HEIGHT = 16;  // 맵 높이

struct Position {
    int x, y;
};

// 뱀 게임 실행
void startSnakeGame() {
    // 게임 초기화
    std::vector<Position> snake = { {WIDTH / 2, HEIGHT / 2} }; // 뱀의 초기 위치
    Position apple = { rand() % WIDTH, rand() % HEIGHT };      // 첫 사과 위치
    Position direction = { 0, -1 };                           // 초기 방향 (위쪽)
    bool running = true;
    bool ateApple = false;
    int score = 0;

    // 메인 게임 루프
    while (running) {
        // 화면 초기화
        std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, ' '));

        // 벽 추가
        for (int x = 0; x < WIDTH; ++x) {
            grid[0][x] = '#';
            grid[HEIGHT - 1][x] = '#';
        }
        for (int y = 0; y < HEIGHT; ++y) {
            grid[y][0] = '#';
            grid[y][WIDTH - 1] = '#';
        }

        // 사과 그리기
        grid[apple.y][apple.x] = 'O';

        // 뱀 그리기
        for (const auto& segment : snake) {
            grid[segment.y][segment.x] = '*';
        }

        // 화면 출력
        system("cls");
        for (const auto& row : grid) {
            for (const char cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
        std::cout << "점수: " << score << "\n";
        std::cout << "조작 방법: W (위), A (왼쪽), S (아래), D (오른쪽), Q (종료)\n";

        // 입력 처리
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

        // 뱀 이동
        Position newHead = { snake.front().x + direction.x, snake.front().y + direction.y };
        snake.insert(snake.begin(), newHead);

        // 충돌 처리: 벽
        if (newHead.x <= 0 || newHead.x >= WIDTH - 1 || newHead.y <= 0 || newHead.y >= HEIGHT - 1) {
            running = false;
            break;
        }

        // 충돌 처리: 자기 몸
        for (size_t i = 1; i < snake.size(); ++i) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                running = false;
                break;
            }
        }

        // 사과 먹기
        if (newHead.x == apple.x && newHead.y == apple.y) {
            ateApple = true;
            score += 10;
            apple = { rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1 };
        }

        // 꼬리 제거 (사과를 먹지 않은 경우)
        if (!ateApple) {
            snake.pop_back();
        }
        else {
            ateApple = false;
        }

        // 속도 조절
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // 게임 종료 메시지
    system("cls");
    std::cout << "게임 오버! 당신의 점수: " << score << "\n";
    std::cout << "메인 메뉴로 돌아가려면 아무 키나 누르세요.\n";
    _getch();
}
