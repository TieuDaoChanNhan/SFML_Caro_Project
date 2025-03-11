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
	int dfs(Board& board, Referee& referee, int depth, char currentSymbol) {
		cnt++;
		int judge = referee.evaluateGameState(board);
		if (judge == 0) return 0;
		else
			if (judge == 1)
				if (depth % 2 == 0) return 1;
				else return -1;
		if (depth == 6) return 0;
		char nextSymbol;
		if (currentSymbol == 'X') nextSymbol = 'O';
		else nextSymbol = 'X';
		int point, px, py;
		if (depth % 2 == 0) point = INT_MIN;
		else point = INT_MAX;
		//int cntMove = 0;
		for (int i = 0; i < board.getN(); i++)
			for (int j = 0; j < board.getM(); j++) {
				if (board.getCell(i, j) != ' ') continue;
				//cntMove++;
				board.setCell(i, j, currentSymbol);
				string state = board.getBoardState();
				if (!st.count(state)) {
					st.insert(state);
					int returnPoint = dfs(board, referee, depth + 1, nextSymbol);
					if (depth % 2 == 0 && point < returnPoint) px = i, py = j, point = returnPoint;
					if (depth % 2 == 1 && point > returnPoint) px = i, py = j, point = returnPoint;
				}
				board.setCell(i, j, ' ');
			}
		//cout << "Move: " << cntMove << "\n";
		if (depth == 0) x = px, y = py;
		return 0;
	}
public:
	pair<int, int> findMove(Board& board, Referee& referee, char currentSymbol) {
		cnt = 0;
		dfs(board, referee, 0, currentSymbol);
		//cout << "Count: " << cnt << "\n";
		st.clear();
		return make_pair(x, y);
	}
};

#endif // !BOTALGORITHM_HPP
