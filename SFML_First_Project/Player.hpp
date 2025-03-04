#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"

class Player {
private:
	char symbol;
public:
	Player(char symbol) :symbol(symbol) {};
	char getSymbol() {
		return symbol;
	}
	virtual void addMove(int x, int y) {

	}
};

#endif // !PLAYER_HPP
