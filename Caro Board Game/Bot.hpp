// BOT_HPP
#ifndef BOT_HPP
#define BOT_HPP

#include "Player.hpp"
#include "Referee.hpp"
#include "Board.hpp"
#include "BotAlgorithm.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Bot : public Player {
private:
    // --- Private Members ---
    vector<pair<int, int>> moves;
    BotAlgorithm AI;
public:
    // --- Constructor ---
    Bot(char symbol) : Player(symbol) {}

    bool decideMove(sf::RenderWindow& window, sf::Event& event, Board& board, Referee& referee, int& isWin) override {
        pair<int, int> dec = AI.findMove(board, referee, getSymbol());
        int x = dec.first, y = dec.second;
        board.setCell(x, y, getSymbol());
        addMove(x, y);
        cout << x << " " << y << "\n";
        for (int i = 0; i < board.getN(); i++) {
            for (int j = 0; j < board.getM(); j++) {
                if (board.getCell(i, j) == ' ') cout << ".";
                else cout << board.getCell(i, j);
            }
            cout << "\n";
        }
        referee.checkWin(board);
        cout << "win: " << isWin << "\n";
        return true;
    }
};

#endif // !BOT_HPP