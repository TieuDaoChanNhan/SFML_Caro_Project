#ifndef HUMAN_HPP
#define HUMAN_HPP

#include"Player.hpp"
#include"Referee.hpp"
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Human : public Player {
public:
    Human(char symbol) : Player(symbol) {}

    bool decideMove(sf::RenderWindow& window, sf::Event& event, Board& board, Referee& referee, int isWin) {
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left && isWin == -1) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = mousePos.x / board.getCellSize();
                int y = mousePos.y / board.getCellSize();

                if (board.getCell(x, y) == ' ') {
                    board.setCell(x, y, getSymbol());
                    addMove(x, y);
                    referee.checkWin(board);
                    return true;
                }
            }
        }
        return false;
    }
};

#endif // !HUMAN_HPP
