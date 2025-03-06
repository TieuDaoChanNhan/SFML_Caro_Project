#ifndef BOT_HPP
#define BOT_HPP

#include "Player.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Bot : public Player {
private:
    // --- Private Members ---
    vector<pair<int, int>> moves;

public:
    // --- Constructor ---
    Bot(char symbol) : Player(symbol) {}

    // --- Game Logic Functions ---
    void addMove(int x, int y) {
        // Máy tính chọn nước đi thông qua thuật toán Minimax hoặc AI
    }

    void resetMoves() {
        if (!moves.empty()) moves.clear();
    }
};

#endif // !BOT_HPP