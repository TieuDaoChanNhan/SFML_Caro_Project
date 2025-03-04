#ifndef REFEREE_HPP
#define REFEREE_HPP

#include "Board.hpp"
#include<iostream>

using namespace std;

class Referee {
private:
	bool checkInside(Board& board, int xPos, int yPos) { // Check vị trí đang ở trong bảng
		return (xPos >= 0 && xPos < board.getN() && yPos >= 0 && yPos < board.getM());
	}
	bool checkDirection(Board& board, int xPos, int yPos, int xMove, int yMove) {
		char currentPlayer = board.getCell(xPos, yPos);
		int xCrr, yCrr; // Biến kiểm soát vị trí x và y hiện tại trong khi check
		int cnt = 1; // Đếm số lượng ô giống nhau

		xCrr = xPos; yCrr = yPos;
		while (checkInside(board, xCrr - xMove, yCrr - yMove) && board.getCell(xCrr - xMove, yCrr - yMove) == currentPlayer) {
			xCrr -= xMove; yCrr -= yMove;
			cnt++;
		}

		xCrr = xPos; yCrr = yPos;
		while (checkInside(board, xCrr + xMove, yCrr + yMove) && board.getCell(xCrr + xMove, yCrr + yMove) == currentPlayer) {
			xCrr += xMove; yCrr += yMove;
			cnt++;
		}

		if (cnt >= 5) {
			//cout << xPos << " " << yPos << " " << xMove << " " << yMove << " " << cnt << "\n";
			return true;
		}
		return false;
	}
public:
	bool checkWin(Board& board) {
		/*for (int i = 0; i < board.getN(); i++) {
			for (int j = 0; j < board.getM(); j++)
				if (board.getCell(i, j) == ' ') cout << ".";
				else cout << board.getCell(i, j);
			cout << "\n";
		}*/

		for (int i = 0; i < board.getN(); i++)
			for (int j = 0; j < board.getM(); j++) {
				if (board.getCell(i,j) == ' ') continue;
				int xPos = i, yPos = j;

				int xMove, yMove; // Biến thêm vào vị trí x và y để đi check ngang dọc chéo

				// Check hàng dọc
				xMove = 1; yMove = 0;
				if (checkDirection(board, xPos, yPos, xMove, yMove)) return true;

				// Check hàng ngang
				xMove = 0; yMove = 1;
				if (checkDirection(board, xPos, yPos, xMove, yMove)) return true;

				// Check hàng dọc
				xMove = 1; yMove = 1;
				if (checkDirection(board, xPos, yPos, xMove, yMove)) return true;

				xMove = 1; yMove = -1;
				if (checkDirection(board, xPos, yPos, xMove, yMove)) return true;
			};

		return false; //Check 3 lần không được tức là game chưa end
	}

};

#endif // !REFEREE_HPP
