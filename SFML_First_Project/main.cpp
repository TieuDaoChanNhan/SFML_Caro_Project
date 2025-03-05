#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Human.hpp"
#include "Board.hpp"
#include "Referee.hpp"
#include "UIUX_Begin.hpp"
#include "UIUX_Game.hpp"
#include "UIUX_Victory.hpp"

using namespace std;

int n = 15, m = 15, cellSize = 70;
Board board(n, m, cellSize);
Human playerO('O');
Human playerX('X');
Human* currentPlayer = &playerO;
int isWin = -1;
unsigned int height = board.getN() * board.getCellSize();
unsigned int width = board.getM() * board.getCellSize();
sf::RenderWindow window(sf::VideoMode({ width, height }), "Caro Board Game");
UIUX_Begin uiuxBegin(cellSize, &window);
UIUX_Game uiuxGame(cellSize, &window);
UIUX_Victory uiuxVictory(cellSize, &window);
Referee referee(&isWin);
vector<string> inputData;
bool doneInput = false;

void changePlayer() {
    if (isWin != -1) return;
    if (currentPlayer == &playerO) {
        currentPlayer = &playerX;
    }
    else {
        currentPlayer = &playerO;
    }
}

void reset() {
    playerO.resetMoves();
    playerX.resetMoves();
    board.resetBoard();
    currentPlayer = &playerO;
    isWin = -1;
}

int stringToNumber(string s) {
    int val = 0;
    for (auto x : s)
        val = val * 10 + (x - '0');
    return val;
}

void changeWindow() {
    board.setN(stringToNumber(inputData[2]));
    board.setM(stringToNumber(inputData[3]));
    playerO.setName(inputData[0]);
    playerX.setName(inputData[1]);

    // Tính toán kích thước mới
    height = board.getN() * board.getCellSize();
    width = board.getM() * board.getCellSize();

    // Thay đổi kích thước cửa sổ
    window.setSize(sf::Vector2u(width, height));

    // Tính toán vị trí mới để cửa sổ nằm giữa màn hình
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int posX = (desktop.size.x - width) / 2;
    int posY = (desktop.size.y - height) / 2;

    // Thay đổi vị trí cửa sổ
    window.setPosition(sf::Vector2i(posX, posY));

    // Cập nhật cellSize trong UIUX_Game
    uiuxGame.setCellSize(board.getCellSize());

    // Cập nhật sf::View
    float dx = width, dy = height;
    sf::View view(sf::FloatRect({ 0, 0 }, { dx, dy }));
    window.setView(view);
}

int main() {
    while (window.isOpen()) {
        while (optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            window.clear(sf::Color::White);

            uiuxGame.drawBoard(board.getN(), board.getM());

            // Màn hình nhập cấu hình và thông tin
            if (inputData.size() < 4) {
                if (event.has_value()) {
                    sf::Event& actualEvent = event.value();
                    uiuxBegin.inputBox(&inputData, actualEvent);
                    if (inputData.size() == 4) changeWindow();
                }
                uiuxBegin.box.draw(window);
            }
            else {
                doneInput = true;
            }

            if (doneInput) {
                if (event.has_value()) {
                    sf::Event& actualEvent = event.value();
                    if (isWin == -1)
                        if (currentPlayer->decideMove(window, actualEvent, board, referee, isWin)) changePlayer();
                }

                uiuxGame.drawAllMoves(playerO);
                uiuxGame.drawAllMoves(playerX);
                //cout << currentPlayer->getName() << " " << isWin << "\n";
                if (isWin != -1) {
                    sf::RectangleShape okButton = uiuxVictory.drawWinPopup((isWin == 0), currentPlayer->getName());

                    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                            sf::Vector2f mousePos(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                            if (okButton.getGlobalBounds().contains(mousePos)) reset();
                        }
                    }
                }
            }
            window.display();
        }
    }
    return 0;
}