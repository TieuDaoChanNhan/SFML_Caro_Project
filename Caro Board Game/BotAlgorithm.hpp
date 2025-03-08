#ifndef BOTALGORITHM_HPP
#define BOTALGORITHM_HPP

#include<iostream>
#include<set>
#include"Referee.hpp"
#include"Board.hpp"

class BotAlgorithm {
private:
	int x = -1, y = -1; // vị trí được chọn sau khi sử dụng thuật toán
	set<string> st;
	int dfs(Board& board, Referee& referee, int depth, char currentSymbol) {
		string state = board.getBoardState();
		if (st.count(state)) return 0;
		st.insert(state);
		int judge = referee.evaluateGameState(board);
		//cout << depth << " " << judge << " " << "\n";
		/*for (int i = 0; i < board.getN(); i++) {
			for (int j = 0; j < board.getM(); j++) {
				if (board.getCell(i, j) == ' ') cout << ".";
				else cout << board.getCell(i, j);
			}
			cout << "\n";
		}*/
		if (judge == 0) return 0;
		else
			if (judge == 1)
				if (depth % 2 == 0) return 1;
				else return -1;
		if (depth == 10) return 0;
		char nextSymbol;
		if (currentSymbol == 'X') nextSymbol = 'O';
		else nextSymbol = 'X';
		int point, px, py;
		if (depth % 2 == 0) point = INT_MIN;
		else point = INT_MAX;
		for (int i = 0; i < board.getN(); i++)
			for (int j = 0; j < board.getM(); j++) {
				if (board.getCell(i, j) != ' ') continue;
				board.setCell(i, j, currentSymbol);
				int returnPoint = dfs(board, referee, depth + 1, nextSymbol);
				board.setCell(i, j, ' ');
				if (depth % 2 == 0 && point < returnPoint) px = i, py = j, point = returnPoint;
				if (depth % 2 == 1 && point > returnPoint) px = i, py = j, point = returnPoint;
			}
		if (depth == 0) x = px, y = py;
		return 0;
	}
public:
	pair<int, int> findMove(Board& board, Referee& referee, char currentSymbol) {
		dfs(board, referee, 0, currentSymbol);
		st.clear();
		return make_pair(x, y);
	}
};

#endif // !BOTALGORITHM_HPP
