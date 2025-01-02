#include <iostream>
#include <vector>
#include <conio.h> // _kbhit()와 _getch() 사용
#include <thread>
#include <chrono>
#include <string>  // std::stoi 사용

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
    system("cls"); // 콘솔 화면 지우기
    for (const auto& row : screen) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
}

void updateScreen(std::vector<std::vector<char>>& screen, const Ball& ball, const Paddle& paddle, const std::vector<std::pair<int, int>>& bricks) {
    // 화면 초기화
    for (auto& row : screen) {
        std::fill(row.begin(), row.end(), ' ');
    }

    // 벽돌 배치
    for (const auto& brick : bricks) {
        screen[brick.second][brick.first] = '#';
    }

    // 공 배치
    screen[ball.y][ball.x] = 'O';

    // 패들 배치 (길이 8)
    for (int i = 0; i < paddle.width; ++i) {
        screen[HEIGHT - 1][paddle.x + i] = '=';
    }
}

bool playWallBreak() {
    std::vector<std::vector<char>> screen(HEIGHT, std::vector<char>(WIDTH, ' '));

    // 초기 상태
    Ball ball = { WIDTH / 2, HEIGHT / 2, 1, -1 };
    Paddle paddle = { WIDTH / 2 - 4, 8 }; // 패들 길이 8로 증가
    std::vector<std::pair<int, int>> bricks;

    // 벽돌 초기화
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < WIDTH; x += 3) {
            bricks.emplace_back(x, y);
        }
    }

    bool running = true;

    while (running) {
        // 입력 처리
        if (_kbhit()) {
            char input = _getch();
            if (input == 'a' && paddle.x > 0) paddle.x--;
            if (input == 'd' && paddle.x + paddle.width < WIDTH) paddle.x++;
            if (input == 'q') return false; // 즉시 메인 페이지로 돌아감
        }

        // 공 움직임
        ball.x += ball.dx;
        ball.y += ball.dy;

        // 충돌 처리: 경계
        if (ball.x <= 0 || ball.x >= WIDTH - 1) ball.dx = -ball.dx;
        if (ball.y <= 0) ball.dy = -ball.dy;

        // 충돌 처리: 패들
        if (ball.y == HEIGHT - 2 && ball.x >= paddle.x && ball.x < paddle.x + paddle.width) {
            ball.dy = -ball.dy;
        }

        // 충돌 처리: 벽돌
        for (auto it = bricks.begin(); it != bricks.end();) {
            if (ball.x == it->first && ball.y == it->second) {
                ball.dy = -ball.dy;
                it = bricks.erase(it); // 벽돌 제거
            }
            else {
                ++it;
            }
        }

        // 공이 아래로 떨어지면 게임 종료
        if (ball.y >= HEIGHT - 1) {
            running = false;
        }

        // 화면 갱신
        updateScreen(screen, ball, paddle, bricks);
        draw(screen);

        // 속도 조절
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return true; // 정상적으로 게임 종료
}

void startWallBreak() {
    while (true) {
        // 안내 화면 출력
        std::cout << "\n=== 벽돌 깨기 ===\n";
        std::cout << "1. 게임 시작\n";
        std::cout << "2. 메인 메뉴로 돌아가기\n";
        std::cout << "게임 방법:\n";
        std::cout << "- 'a'를 눌러 왼쪽으로 이동.\n";
        std::cout << "- 'd'를 눌러 오른쪽으로 이동.\n";
        std::cout << "- 게임 중 'q'를 눌러 종료.\n";
        std::cout << "옵션을 선택하세요: ";

        std::string input;
        std::cin >> input;

        // 입력이 'q'일 경우 메인 메뉴로 즉시 복귀
        if (input == "q") {
            std::cout << "메인 메뉴로 돌아갑니다...\n";
            break;
        }

        // 숫자 입력 확인
        int choice;
        try {
            choice = std::stoi(input); // 문자열을 숫자로 변환
        }
        catch (...) {
            std::cout << "잘못된 입력입니다. 1, 2 또는 'q'를 입력해주세요.\n";
            continue; // 다시 입력 받기
        }

        if (choice == 1) {
            if (!playWallBreak()) {
                break; // 게임 중 'q'를 눌러 메인 메뉴로 돌아감
            }
            std::cout << "\n게임 오버!\n";
            std::cout << "1. 재시작\n2. 메인 메뉴로 돌아가기\n";
            std::cin >> input;

            if (input == "1") {
                continue; // 게임 재시작
            }
            else if (input == "2") {
                break; // 메인 메뉴로 돌아감
            }
            else {
                std::cout << "잘못된 선택입니다. 메인 메뉴로 종료합니다.\n";
                break;
            }
        }
        else if (choice == 2) {
            break; // 메인 메뉴로 돌아감
        }
        else {
            std::cout << "잘못된 선택입니다. 1, 2 또는 'q'를 입력해주세요.\n";
        }
    }
}
