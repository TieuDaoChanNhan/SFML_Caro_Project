#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include<vector>
#include<string>

using namespace std;

class Player {
private:
	char symbol;
	vector<pair<int, int>> moves;
	string name;
public:
	Player(char symbol) :symbol(symbol) {};
	char getSymbol() {
		return symbol;
	}
	void addMove(int x, int y) {
		moves.push_back(make_pair(x, y));
	}
	void resetMoves() {
		if (!moves.empty()) moves.clear();
	}
	vector<pair<int, int>>& getMoves() {
		return moves;
	}
	void setName(string val) {
		name = val;
	}
	string getName() {
		return name;
	}
};

#endif // !PLAYER_HPP
