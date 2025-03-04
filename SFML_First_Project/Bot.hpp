#ifndef BOT_HPP
#define BOT_HPP

#include "Player.hpp"
#include<iostream>
#include<vector>

using namespace std;

class Bot : public Player {
private:
    vector<pair<int, int>> moves;
public:
    Bot(char symbol) : Player(symbol) {}

    // Di chuyển của bot (máy tính sử dụng thuật toán Minimax hoặc AI)
    void addMove(int x, int y) {
        // Máy tính chọn nước đi thông qua thuật toán Minimax hoặc AI
    }

    void resetMoves() {
        if (!moves.empty()) moves.clear();
    }
};

#endif // !BOT_HPP
