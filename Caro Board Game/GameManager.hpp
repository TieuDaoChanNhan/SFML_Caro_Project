#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Human.hpp"
#include "Board.hpp"
#include "Referee.hpp"
#include "UIUX_Begin.hpp"
#include "UIUX_Game.hpp"
#include "UIUX_Victory.hpp"

class GameManager {
private:
    int addSpace = 100;
    int n = 15, m = 15, cellSize = 70;
    Board board;
    Human playerO;
    Human playerX;
    Human* currentPlayer;
    int isWin = -1;
    unsigned int height;
    unsigned int width;
    sf::RenderWindow window;
    UIUX_Begin uiuxBegin;
    UIUX_Game uiuxGame;
    UIUX_Victory uiuxVictory;
    Referee referee;
    std::vector<std::string> inputData;
    bool doneInput = false;

    int stringToNumber(const std::string& s) {
        int val = 0;
        for (char x : s) {
            val = val * 10 + (x - '0');
        }
        return val;
    }

    void changePlayer() {
        if (isWin != -1) return;
        currentPlayer = (currentPlayer == &playerO) ? &playerX : &playerO;
    }

    void reset() {
        playerO.resetMoves();
        playerX.resetMoves();
        board.resetBoard();
        currentPlayer = &playerO;
        isWin = -1;
        //inputData.clear();
        doneInput = false;
    }

    void changeWindow() {
        board.setN(stringToNumber(inputData[2]));
        board.setM(stringToNumber(inputData[3]));
        playerO.setName(inputData[0]);
        playerX.setName(inputData[1]);

        height = board.getN() * board.getCellSize() + addSpace;
        width = board.getM() * board.getCellSize();

        window.setSize(sf::Vector2u(width, height));

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        int posX = (desktop.size.x - width) / 2;
        int posY = (desktop.size.y - height) / 2;

        window.setPosition(sf::Vector2i(posX, posY));

        uiuxGame.setCellSize(board.getCellSize());

        sf::View view(sf::FloatRect({ 0, 0 }, { static_cast<float>(width), static_cast<float>(height) }));
        window.setView(view);
    }

    void handleEvents(sf::Event& event) {
        if (event.is<sf::Event::Closed>()) {
            window.close();
        }

        if (uiuxGame.isUndoButtonClicked(window, event)) {
            changePlayer();
            currentPlayer->removeLastMove(board);
            return;
        }

        if (inputData.size() < 4) {
            uiuxBegin.inputBox(&inputData, event);
            if (inputData.size() == 4) changeWindow();
        }
        else {
            doneInput = true;
        }

        if (doneInput) {
            if (isWin == -1 && currentPlayer->decideMove(window, event, board, referee, isWin)) changePlayer();

            if (isWin != -1) {
                sf::RectangleShape okButton = uiuxVictory.drawWinPopup((isWin == 0), currentPlayer->getName());

                if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                        sf::Vector2f mousePos(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                        if (okButton.getGlobalBounds().contains(mousePos)) reset();
                    }
                }
            }

        }
    }

    void render() {
        window.clear(sf::Color::White);
        uiuxGame.drawBoard(board.getN(), board.getM());
        uiuxGame.drawUndoButton();

        if (inputData.size() < 4) {
            uiuxBegin.box.draw(window);
        }
        else {
            uiuxGame.drawAllMoves(playerO);
            uiuxGame.drawAllMoves(playerX);
            if (isWin != -1) {
                uiuxVictory.drawWinPopup((isWin == 0), currentPlayer->getName());
            }
        }
        window.display();
    }

public:
    GameManager() :
        board(n, m, cellSize),
        playerO('O'),
        playerX('X'),
        currentPlayer(&playerO),
        height(board.getN()* board.getCellSize() + addSpace),
        width(board.getM()* board.getCellSize()),
        window(sf::VideoMode({ width, height }), "Caro Board Game"),
        uiuxBegin(cellSize, &window),
        uiuxGame(cellSize, &window),
        uiuxVictory(cellSize, &window),
        referee(&isWin) {}

    void run() {
        while (window.isOpen()) {
            while (optional event = window.pollEvent()) {
                if (event) {
                    handleEvents(event.value());
                }
                render();
            }
        }
    }
};

#endif // GAMEMANAGER_HPP