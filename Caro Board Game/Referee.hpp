#ifndef REFEREE_HPP
#define REFEREE_HPP

#include "Board.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Referee {
private:
    int* isWin; // Pointer to the win status variable
    vector<pair<int, int>> winningLine; // Stores the winning line coordinates

    bool checkInside(Board& board, int xPos, int yPos) {
        // Checks if a position is within the board boundaries
        return (xPos >= 0 && xPos < board.getN() && yPos >= 0 && yPos < board.getM());
    }

    bool checkDirection(Board& board, int xPos, int yPos, int xMove, int yMove) {
        // Checks if there are 5 consecutive symbols in a given direction
        char currentPlayer = board.getCell(xPos, yPos);
        int xCrr, yCrr;
        int cnt = 1;

        winningLine.clear(); // Clear the previous winning line
        winningLine.push_back(make_pair(xPos, yPos)); // Add the starting cell to the winning line

        xCrr = xPos; yCrr = yPos;
        while (checkInside(board, xCrr - xMove, yCrr - yMove) && board.getCell(xCrr - xMove, yCrr - yMove) == currentPlayer) {
            xCrr -= xMove; yCrr -= yMove;
            cnt++;
            winningLine.push_back(make_pair(xCrr, yCrr)); // Add the cell to the winning line
        }

        xCrr = xPos; yCrr = yPos;
        while (checkInside(board, xCrr + xMove, yCrr + yMove) && board.getCell(xCrr + xMove, yCrr + yMove) == currentPlayer) {
            xCrr += xMove; yCrr += yMove;
            cnt++;
            winningLine.push_back(make_pair(xCrr, yCrr)); // Add the cell to the winning line
        }

        if (cnt >= 5) { // Check if there are 5 consecutive symbols
            return true;
        }
        return false;
    }

public:
    Referee(int* isWin) : isWin(isWin) {} // Constructor initializes the referee with the win status pointer

    void checkWin(Board& board) {
        // Checks if there is a winner or a draw
        for (int i = 0; i < board.getN(); i++) {
            for (int j = 0; j < board.getM(); j++) {
                if (board.getCell(i, j) == ' ') continue; // Skip empty cells
                int xPos = i, yPos = j;

                int xMove, yMove;

                xMove = 1; yMove = 0; // Check horizontal
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }

                xMove = 0; yMove = 1; // Check vertical
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }

                xMove = 1; yMove = 1; // Check diagonal (top-left to bottom-right)
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }

                xMove = 1; yMove = -1; // Check diagonal (top-right to bottom-left)
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }
            }
        }
        if (board.isFullBoard()) *isWin = 0; // Check for a draw
    }

    int evaluateGameState(Board& board) {
        // Evaluates the current game state for AI purposes
        for (int i = 0; i < board.getN(); i++) {
            for (int j = 0; j < board.getM(); j++) {
                if (board.getCell(i, j) == ' ') continue; // Skip empty cells
                int xPos = i, yPos = j;

                int xMove, yMove;

                xMove = 1; yMove = 0; // Check horizontal
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1; // Win

                xMove = 0; yMove = 1; // Check vertical
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1; // Win

                xMove = 1; yMove = 1; // Check diagonal (top-left to bottom-right)
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1; // Win

                xMove = 1; yMove = -1; // Check diagonal (top-right to bottom-left)
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1; // Win
            }
        }
        if (board.isFullBoard()) return 0; // Draw
        return -1; // Ongoing game
    }

    vector<pair<int, int>> getWinningLine() {
        // Returns the winning line coordinates
        return winningLine;
    }
};

#endif