#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include "Referee.hpp"
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
public:
    // --- Constructor ---
    Player(char symbol) : symbol(symbol) {}
    virtual bool decideMove(sf::RenderWindow& window, sf::Event& event, Board& board, Referee& referee, int& isWin) = 0;
    virtual ~Player() {}

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

    void removeLastMove(Board& board) {
        if (!moves.empty()) {
            int x = moves.back().first;
            int y = moves.back().second;
            board.clearCell(x, y);
            moves.pop_back();
        }
    }
};

#endif // !PLAYER_HPP