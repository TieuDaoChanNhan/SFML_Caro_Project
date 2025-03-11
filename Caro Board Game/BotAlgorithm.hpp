#ifndef BOTALGORITHM_HPP
#define BOTALGORITHM_HPP

#include<iostream>
#include<set>
#include"Referee.hpp"
#include"Board.hpp"

class BotAlgorithm {
private:
	int x = -1, y = -1; // vị trí được chọn sau khi sử dụng thuật toán
	int cnt = 0;
	set<string> st;
	int hx[4] = { 0,1,0,-1 }, hy[4] = { 1,0,-1,0 };

	bool checkNeed(Board& board, int x, int y) {
		for (int i = 0; i < 4; i++) {
			int nx = x + hx[i], ny = y + hy[i];
			if (!board.isInside(nx, ny)) continue;
			if (board.getCell(nx, ny) != ' ') return true;
		}
		return false;
	}

	int dfs(Board& board, Referee& referee, int depth, char currentSymbol) {
		cnt++;
		int judge = referee.evaluateGameState(board);
		/*for (int i = 0; i < board.getN(); i++) {
			for (int j = 0; j < board.getM(); j++) {
				cout << board.getCell(i, j);
			}
			cout << "\n";
		}
		cout << judge << "\n";*/
		if (judge == 0) return 0;
		else
			if (judge == 1)
				if (depth % 2 == 1) return 1;
				else return -1;
		if (depth == 7) return 0;
		char nextSymbol;
		if (currentSymbol == 'X') nextSymbol = 'O';
		else nextSymbol = 'X';
		int point, px, py;
		if (depth % 2 == 0) point = INT_MIN;
		else point = INT_MAX;
		//int cntMove = 0;
		for (int i = 0; i < board.getN(); i++)
			for (int j = 0; j < board.getM(); j++) {
				//cout << depth << ": " << i << " " << j << " " << board.getCell(i, j) << "\n";
				if (board.getCell(i, j) != ' ') continue;
				if (!checkNeed(board, i, j)) continue;
				//cntMove++;
				board.setCell(i, j, currentSymbol);
				string state = board.getBoardState();
				if (!st.count(state)) {
					st.insert(state);
					int returnPoint = dfs(board, referee, depth + 1, nextSymbol);
					if (depth % 2 == 0 && point < returnPoint) px = i, py = j, point = returnPoint;
					if (depth % 2 == 1 && point > returnPoint) px = i, py = j, point = returnPoint;
					//cout << depth << ": " << i << " " << j << " " << depth << " " << point << " " << returnPoint << " " << px << " " << py << "\n";
				}
				board.setCell(i, j, ' ');
			}
		if (depth == 0) x = px, y = py;
		//cout << "Move: " << point << "\n";
		if (point == INT_MAX || point == INT_MIN) return 0;
		else return point;
	}
	void reset() {
		cnt = 0;
		st.clear();
		x = -1; y = -1;
	}
public:
	pair<int, int> findMove(Board board, Referee& referee, char currentSymbol) {
		reset();
		int point = dfs(board, referee, 0, currentSymbol);
		//cout << "Point: " << point << "\n";
		//cout << "Count: " << cnt << "\n";
		return make_pair(x, y);
	}
};

#endif // !BOTALGORITHM_HPP
