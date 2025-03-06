#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include "Referee.hpp"
#include "BotAlgorithm.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Player {
private:
    // --- Private Members ---
    char symbol;
    vector<pair<int, int>> moves;
    string name;
    int type; // AI or Human
    BotAlgorithm AI;
public:
    // --- Constructor ---
    Player(char symbol) : symbol(symbol) {}

    // --- Accessors (Getters) ---
    char getSymbol() {
        return symbol;
    }

    vector<pair<int, int>>& getMoves() {
        return moves;
    }

    string getName() {
        return name;
    }

    // --- Mutators (Setters) ---
    void addMove(int x, int y) {
        moves.push_back(make_pair(x, y));
    }

    void resetMoves() {
        if (!moves.empty()) moves.clear();
    }

    void setName(string val) {
        name = val;
    }

    void setTypePlayer(int val) {
        type = val;
    }

    void removeLastMove(Board& board) {
        if (!moves.empty()) {
            int x = moves.back().first;
            int y = moves.back().second;
            board.clearCell(x, y);
            moves.pop_back();
        }
    }

    // --- Game Logic Functions ---
    bool decideMove(sf::RenderWindow& window, sf::Event& event, Board& board, Referee& referee, Player& player, int isWin) {
        if (type) {
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
        else {
            pair<int,int> dec = AI.findMove(board, referee, player.symbol);
            int x = dec.first, y = dec.second;
            //cout << x << " " << y << "\n";
            board.setCell(x, y, getSymbol());
            addMove(x, y);
            referee.checkWin(board);
            return true;
        }
    }
};

#endif // !PLAYER_HPP