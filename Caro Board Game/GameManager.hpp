#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Referee.hpp"
#include "UIUX.hpp"
#include "Timer.hpp"
#include "Human.hpp"
#include "Bot.hpp"
#include <chrono>
#include <thread>

using namespace std;

class GameManager {
private:
    int addSpace = 200;
    int n = 15, m = 15, cellSize = 70;
    Board board;
    Player* playerO;
    Player* playerX;
    Player* currentPlayer;
    int isWin = -1;
    unsigned int height;
    unsigned int width;
    sf::RenderWindow window;
    UIUX uiux;
    Referee referee;
    std::vector<std::string> inputData;
    Timer timer;
    bool isDoneInput = false;

    int stringToNumber(const std::string& s) {
        int val = 0;
        for (char x : s) {
            val = val * 10 + (x - '0');
        }
        return val;
    }

    void changePlayer() {
        if (isWin != -1) return;
        currentPlayer = (currentPlayer == playerO) ? playerX : playerO;
    }

    void reset() {
        timer.setTimelimit(sf::seconds(30.f));
        timer.restartTimer();
        playerO->resetMoves();
        playerX->resetMoves();
        board.resetBoard();
        currentPlayer = playerO;
        isWin = -1;
        isDoneInput = false;
    }

    void changeWindow() {
        if (inputData[0] == "player") playerO = new Human('O');
        else playerO = new Bot('O');
        if (inputData[1] == "player") playerX = new Human('X');
        else playerX = new Bot('X');
        board.setN(stringToNumber(inputData[4]));
        board.setM(stringToNumber(inputData[5]));
        playerO->setName(inputData[2]);
        playerX->setName(inputData[3]);

        height = board.getN() * board.getCellSize() + addSpace;
        width = board.getM() * board.getCellSize();

        window.setSize(sf::Vector2u(width, height));

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        int posX = (desktop.size.x - width) / 2;
        int posY = (desktop.size.y - height) / 2;

        window.setPosition(sf::Vector2i(posX, posY));

        uiux.setCellSize(board.getCellSize());

        sf::View view(sf::FloatRect({ 0, 0 }, { static_cast<float>(width), static_cast<float>(height) }));
        window.setView(view);

        currentPlayer = playerO; // Set currentPlayer after creating player objects
    }

    void handleEvents(sf::Event& event) {
        if (event.is<sf::Event::Closed>()) {
            window.close();
        }

        if (uiux.isTimerClicked(window, event)) {
            timer.changeState();
            return;
        }

        if (isWin == -1 && uiux.isUndoButtonClicked(window, event)) {
            changePlayer();
            currentPlayer->removeLastMove(board);
            timer.restartTimer();
            return;
        }

        if (uiux.isNewButtonClicked(window, event)) {
            reset();
            return;
        }

        if (uiux.isExitButtonClicked(window, event)) {
            window.close();
            return;
        }

        if (uiux.isResetButtonClicked(window, event)) {
            reset();
            inputData.clear();
            uiux.resetIndex();
            return;
        }

        if (inputData.size() < 6) {
            uiux.inputBox(&inputData, event);
            if (inputData.size() == 6) {
                isDoneInput = true;
                changeWindow();
                timer.setTimelimit(sf::seconds(30.f));
                timer.restartTimer();
            }
            return;
        }

        uiux.setInformText("Now is " + currentPlayer->getName() + "'s turn");

        if (isWin == -1 && currentPlayer->decideMove(window, event, board, referee, isWin)) {
            changePlayer();
            timer.restartTimer();
        }

        if (isWin != -1) {
            timer.setTimelimit(sf::seconds(0.f));
            if (isWin == 1) uiux.setInformText("Congratulation, " + currentPlayer->getName() + " wins!");
            else uiux.setInformText("This game is draw!");
        }
    }

    void render() {
        uiux.setHoover(isDoneInput && (isWin == -1));
        window.clear(sf::Color::White);
        uiux.drawBoard(board.getN(), board.getM());
        uiux.drawButtons();
        uiux.drawInform();

        if (inputData.size() < 6) {
            uiux.box.draw(window);
        }
        else {
            uiux.drawAllMoves(*playerO);
            uiux.drawAllMoves(*playerX);
        }
        if (isWin == 1) {
            std::vector<std::pair<int, int>> winningLine = referee.getWinningLine();
            if (!winningLine.empty()) {
                sf::VertexArray line(sf::PrimitiveType::LineStrip, winningLine.size());
                for (size_t i = 0; i < winningLine.size(); ++i) {
                    int x = winningLine[i].first * board.getCellSize() + board.getCellSize() / 2;
                    int y = winningLine[i].second * board.getCellSize() + board.getCellSize() / 2 + 2;
                    line[i].position = sf::Vector2f(x, y);
                    line[i].color = sf::Color::Red;
                }
                window.draw(line);
            }
        }

        uiux.drawTimer(timer.getRemainingTime(), timer.getState());

        window.display();
    }

public:
    GameManager() :
        board(n, m, cellSize),
        playerO(nullptr),
        playerX(nullptr),
        currentPlayer(nullptr),
        height(board.getN()* board.getCellSize() + addSpace),
        width(board.getM()* board.getCellSize()),
        window(sf::VideoMode({ width, height }), "Caro Board Game"),
        uiux(cellSize, &window),
        referee(&isWin),
        timer()
    {
        /*string s1 = "player", s2 = "bot", s3 = "hieu", s4 = "hung", s5 = "4", s6 = "4";
        inputData.push_back(s1);
        inputData.push_back(s2);
        inputData.push_back(s3);
        inputData.push_back(s4);
        inputData.push_back(s5);
        inputData.push_back(s6);
        isDoneInput = true;
        changeWindow();
        timer.setTimelimit(sf::seconds(30.f));
        timer.restartTimer();*/
    }

    ~GameManager() {
        delete playerO;
        delete playerX;
    }

    void run() {
        sf::Clock clock;
        sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

        while (window.isOpen()) {
            sf::Time elapsed = clock.restart();

            while (optional event = window.pollEvent()) {
                if (event) {
                    handleEvents(event.value());
                }
            }

            render();

            if (timer.getTimeLimit() == sf::seconds(30.f) && timer.isTimeUp()) {
                changePlayer();
                timer.restartTimer();
            }

            sf::Time sleepTime = timePerFrame - elapsed;
            if (sleepTime > sf::Time::Zero) {
                std::this_thread::sleep_for(std::chrono::microseconds(sleepTime.asMicroseconds()));
            }
        }
    }
};

#endif // GAMEMANAGER_HPP