﻿#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
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
    Player playerO;
    Player playerX;
    Player* currentPlayer;
    int isWin = -1;
    unsigned int height;
    unsigned int width;
    sf::RenderWindow window;
    UIUX_Begin uiuxBegin;
    UIUX_Game uiuxGame;
    UIUX_Victory uiuxVictory;
    Referee referee;
    std::vector<std::string> inputData;
    bool timerRunning;

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
        uiuxGame.restartTimer();
        playerO.resetMoves();
        playerX.resetMoves();
        board.resetBoard();
        currentPlayer = &playerO;
        isWin = -1;
        //inputData.clear();
        //doneInput = false;
    }

    void changeWindow() {
        if (inputData[0] == "player") playerO.setTypePlayer(1);
        else playerO.setTypePlayer(0);
        if (inputData[1] == "player") playerX.setTypePlayer(1);
        else playerX.setTypePlayer(0);
        board.setN(stringToNumber(inputData[4]));
        board.setM(stringToNumber(inputData[5]));
        playerO.setName(inputData[2]);
        playerX.setName(inputData[3]);

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
            uiuxGame.restartTimer();
            return;
        }

        if (uiuxGame.isNewButtonClicked(window, event)) {
            reset();
            return;
        }

        if (uiuxGame.isExitButtonClicked(window, event)) {
            window.close();
            return;
        }

        if (inputData.size() < 6) {
            uiuxBegin.inputBox(&inputData, event);
            if (inputData.size() == 6) {
                changeWindow();
                timerRunning = true; // Bắt đầu timer sau khi nhập xong
                uiuxGame.restartTimer();
            }
            return;
        }

        if (isWin == -1 && currentPlayer->decideMove(window, event, board, referee, *currentPlayer, isWin)) {
            changePlayer();
            uiuxGame.restartTimer();
        }

        if (isWin != -1) {
            sf::RectangleShape okButton = uiuxVictory.drawWinPopup((isWin == 0), currentPlayer->getName());

            if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                    if (okButton.getGlobalBounds().contains(mousePos)) {
                        reset();
                        timerRunning = true; // Bắt đầu timer sau khi reset
                        uiuxGame.restartTimer();
                    }
                }
            }
        }
    }

    void render() {
        window.clear(sf::Color::White);
        uiuxGame.drawBoard(board.getN(), board.getM());
        uiuxGame.drawButtons();

        if (inputData.size() < 6) {
            uiuxBegin.box.draw(window);
        }
        else {
            uiuxGame.drawAllMoves(playerO);
            uiuxGame.drawAllMoves(playerX);
            if (isWin != -1) uiuxVictory.drawWinPopup((isWin == 0), currentPlayer->getName());
        }
        if (isWin == 1) {
            std::vector<std::pair<int, int>> winningLine = referee.getWinningLine();
            if (!winningLine.empty()) {
                sf::VertexArray line(sf::PrimitiveType::LineStrip, winningLine.size()); // Sử dụng LineStrip
                for (size_t i = 0; i < winningLine.size(); ++i) {
                    int x = winningLine[i].first * board.getCellSize() + board.getCellSize() / 2;
                    int y = winningLine[i].second * board.getCellSize() + board.getCellSize() / 2 + 2;
                    line[i].position = sf::Vector2f(x, y);
                    line[i].color = sf::Color::Red; // Màu đường chiến thắng
                }
                window.draw(line);
            }
            uiuxVictory.drawWinPopup((isWin == 0), currentPlayer->getName());
        }

        uiuxGame.drawTimer(sf::Vector2f(10, 10)); // Vẽ timer

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
        uiuxGame(cellSize, &window, sf::seconds(30.0f)), // Thêm timeLimit
        uiuxVictory(cellSize, &window),
        referee(&isWin),
        timerRunning(false)
    {
    }

    void run() {
        while (window.isOpen()) {
            while (optional event = window.pollEvent()) {
                if (event) {
                    handleEvents(event.value());
                }
                render();
                if (timerRunning && uiuxGame.isTimeUp()) { // Chỉ kiểm tra timer nếu timerRunning là true
                    changePlayer();
                    uiuxGame.restartTimer();
                }
            }
        }
    }
};

#endif // GAMEMANAGER_HPP