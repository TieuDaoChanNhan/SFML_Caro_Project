#ifndef REFEREE_HPP
#define REFEREE_HPP

#include "Board.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Referee {
private:
    int* isWin;
    vector<pair<int, int>> winningLine; // Thêm vector để lưu trữ đường chiến thắng

    bool checkInside(Board& board, int xPos, int yPos) {
        return (xPos >= 0 && xPos < board.getN() && yPos >= 0 && yPos < board.getM());
    }

    bool checkDirection(Board& board, int xPos, int yPos, int xMove, int yMove) {
        char currentPlayer = board.getCell(xPos, yPos);
        int xCrr, yCrr;
        int cnt = 1;

        winningLine.clear(); // Xóa đường chiến thắng cũ
        winningLine.push_back(make_pair(xPos, yPos)); // Thêm ô đầu tiên

        xCrr = xPos; yCrr = yPos;
        while (checkInside(board, xCrr - xMove, yCrr - yMove) && board.getCell(xCrr - xMove, yCrr - yMove) == currentPlayer) {
            xCrr -= xMove; yCrr -= yMove;
            cnt++;
            winningLine.push_back(make_pair(xCrr, yCrr)); // Thêm ô vào đường chiến thắng
        }

        xCrr = xPos; yCrr = yPos;
        while (checkInside(board, xCrr + xMove, yCrr + yMove) && board.getCell(xCrr + xMove, yCrr + yMove) == currentPlayer) {
            xCrr += xMove; yCrr += yMove;
            cnt++;
            winningLine.push_back(make_pair(xCrr, yCrr)); // Thêm ô vào đường chiến thắng
        }

        if (cnt >= 3) { // Số ô liên tiếp để thắng
            return true;
        }
        return false;
    }

public:
    Referee(int* isWin) : isWin(isWin) {}

    void checkWin(Board& board) {
        for (int i = 0; i < board.getN(); i++) {
            for (int j = 0; j < board.getM(); j++) {
                if (board.getCell(i, j) == ' ') continue;
                int xPos = i, yPos = j;

                int xMove, yMove;

                xMove = 1; yMove = 0;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }

                xMove = 0; yMove = 1;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }

                xMove = 1; yMove = 1;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }

                xMove = 1; yMove = -1;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) {
                    *isWin = 1;
                    return;
                }
            }
        }
        if (board.isFullBoard()) *isWin = 0;
    }

    int evaluateGameState(Board& board) {
        for (int i = 0; i < board.getN(); i++) {
            for (int j = 0; j < board.getM(); j++) {
                if (board.getCell(i, j) == ' ') continue;
                int xPos = i, yPos = j;

                int xMove, yMove;

                xMove = 1; yMove = 0;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1;

                xMove = 0; yMove = 1;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1;

                xMove = 1; yMove = 1;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1;

                xMove = 1; yMove = -1;
                if (checkDirection(board, xPos, yPos, xMove, yMove)) return 1;
            }
        }
        if (board.isFullBoard()) return 0;
        return -1;
    }

    vector<pair<int, int>> getWinningLine() { // Thêm hàm getter
        return winningLine;
    }
};

#endif