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
    vector<pair<int, int>> moves; // Stores the moves made by the bot
    BotAlgorithm AI;              // Instance of the AI algorithm

public:
    // --- Constructor ---
    Bot(char symbol) : Player(symbol) {} // Constructor initializes the bot with its symbol

    // --- Decision Making Function ---
    bool decideMove(sf::RenderWindow& window, sf::Event& event, Board& board, Referee& referee, int& isWin) override {
        // Find the best move using the AI algorithm
        pair<int, int> dec = AI.findMove(board, referee, getSymbol());
        int x = dec.first, y = dec.second; // Extract the move coordinates

        // Apply the move to the board
        board.setCell(x, y, getSymbol());
        addMove(x, y); // Add the move to the bot's move history

        // Debugging output: print the move coordinates
        //cout << x << " " << y << "\n";

        // Debugging output: print the current state of the board
        //for (int i = 0; i < board.getN(); i++) {
        //    for (int j = 0; j < board.getM(); j++) {
        //        if (board.getCell(i, j) == ' ') cout << "."; // Empty cell
        //        else cout << board.getCell(i, j);             // Occupied cell
        //    }
        //    cout << "\n";
        //}

        // Check for a win after the move
        referee.checkWin(board);

        // Debugging output: print the win status
        //cout << "win: " << isWin << "\n";

        return true; // Indicate that a move was made
    }
};

#endif // !BOT_HPP