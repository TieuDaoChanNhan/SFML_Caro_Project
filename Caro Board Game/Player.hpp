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
    char symbol; // Player's symbol (e.g., 'X' or 'O')
    vector<pair<int, int>> moves; // Stores the moves made by the player
    string name; // Player's name

public:
    // --- Constructor ---
    Player(char symbol) : symbol(symbol) {} // Constructor initializes the player with their symbol

    // --- Pure Virtual Function ---
    virtual bool decideMove(sf::RenderWindow& window, sf::Event& event, Board& board, Referee& referee, int& isWin) = 0; // Function to decide the player's move (to be implemented by derived classes)
    virtual ~Player() {} // Virtual destructor for proper memory management

    // --- Accessors (Getters) ---
    char getSymbol() {
        // Returns the player's symbol
        return symbol;
    }

    vector<pair<int, int>>& getMoves() {
        // Returns the vector of moves made by the player
        return moves;
    }

    string getName() {
        // Returns the player's name
        return name;
    }

    // --- Mutators (Setters) ---
    void addMove(int x, int y) {
        // Adds a move to the player's move history
        moves.push_back(make_pair(x, y));
    }

    void resetMoves() {
        // Clears the player's move history
        if (!moves.empty()) moves.clear();
    }

    void setName(string val) {
        // Sets the player's name
        name = val;
    }

    void removeLastMove(Board& board) {
        // Removes the last move made by the player and updates the board
        if (!moves.empty()) {
            int x = moves.back().first;
            int y = moves.back().second;
            board.clearCell(x, y); // Clear the cell on the board
            moves.pop_back(); // Remove the move from the move history
        }
    }
};

#endif // !PLAYER_HPP