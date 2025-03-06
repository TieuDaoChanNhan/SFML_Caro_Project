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

enum class GameState {
    Input,
    Playing,
    Win
};

class GameManager {
private:
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
    GameState gameState = GameState::Input;

public:
    GameManager()
        : board(n, m, cellSize), playerO('O'), playerX('X'), currentPlayer(&playerO),
        height(board.getN()* board.getCellSize()),
        width(board.getM()* board.getCellSize()),
        window(sf::VideoMode({ width, height }), "Caro Board Game"),
        uiuxBegin(cellSize, &window), uiuxGame(cellSize, &window),
        uiuxVictory(cellSize, &window), referee(&isWin) {}

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                handleEvents(event);
            }
            render();
        }
    }

    void handleEvents(sf::Event& event) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (gameState == GameState::Input && inputData.size() < 4 && event.type == sf::Event::TextEntered) {
            uiuxBegin.inputBox(&inputData, event);
            if (inputData.size() == 4) {
                changeWindow();
                gameState = GameState::Playing;
            }
        }

        if (gameState == GameState::Playing) {
            if (isWin == -1 && currentPlayer->decideMove(window, event, board, referee, isWin)) {
                changePlayer();
            }

            if (isWin != -1 && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (uiuxVictory.drawWinPopup((isWin == 0), currentPlayer->getName()).getGlobalBounds().contains(mousePos)) {
                    reset();
                    gameState = GameState::Input;
                }
            }
        }
    }

    void render() {
        window.clear(sf::Color::White);
        uiuxGame.drawBoard(board.getN(), board.getM());

        if (gameState == GameState::Input) {
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
        inputData.clear();
        gameState = GameState::Input;
    }

    int stringToNumber(const std::string& s) {
        int val = 0;
        for (char x : s) {
            val = val * 10 + (x - '0');
        }
        return val;
    }

    void changeWindow() {
        board.setN(stringToNumber(inputData[2]));
        board.setM(stringToNumber(inputData[3]));
        playerO.setName(inputData[0]);
        playerX.setName(inputData[1]);

        height = board.getN() * board.getCellSize();
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
};

#endif // GAMEMANAGER_HPP