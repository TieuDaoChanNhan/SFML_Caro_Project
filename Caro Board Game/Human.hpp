// HUMAN_HPP
#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Player.hpp"
#include "Referee.hpp"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class Human : public Player {
public:
    // --- Constructor ---
    Human(char symbol) : Player(symbol) {} // Constructor initializes the human player with their symbol

    // --- Game Logic Functions ---
    bool decideMove(sf::RenderWindow& window, sf::Event& event, Board& board, Referee& referee, int& isWin) override {
        // Handle mouse button press events
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            // Check if the left mouse button was pressed and the game is ongoing
            if (mouseButtonPressed->button == sf::Mouse::Button::Left && isWin == -1) {
                // Get the mouse position relative to the game window
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Calculate the cell coordinates based on the mouse position and cell size
                int x = mousePos.x / board.getCellSize();
                int y = mousePos.y / board.getCellSize();

                // Check if the cell is within the board bounds and is empty
                if (board.isInside(x, y) && board.getCell(x, y) == ' ') {
                    // Place the player's symbol on the board
                    board.setCell(x, y, getSymbol());

                    // Add the move to the player's move history
                    addMove(x, y);

                    // Check for a win after the move
                    referee.checkWin(board);

                    // Indicate that a move was made
                    return true;
                }
            }
        }
        // Indicate that no move was made
        return false;
    }
};

#endif // !HUMAN_HPP