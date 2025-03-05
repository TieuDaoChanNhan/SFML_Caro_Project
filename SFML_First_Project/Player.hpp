#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include <vector>
#include <string>

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
};

#endif // !PLAYER_HPP