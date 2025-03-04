#ifndef HUMAN_CPP
#define HUMAN_CPP

#include"Player.hpp"
#include"UIUX.hpp"
#include<iostream>
#include<vector>

using namespace std;

class Human : public Player {
private:
    vector<pair<int, int>> moves;
public:
    Human(char symbol) : Player(symbol) {}

    // Di chuyển của người chơi thật (sử dụng sự kiện chuột)
    void addMove(int x, int y) {
        moves.push_back(make_pair(x, y));
    }

    void drawAllMoves(UIUX uiux) {
        for (auto p : moves) {
            uiux.drawMove(p.first, p.second, getSymbol());
        }
    }

    void resetMoves() {
        if (!moves.empty()) moves.clear();
    }
};

#endif // !HUMAN_CPP
