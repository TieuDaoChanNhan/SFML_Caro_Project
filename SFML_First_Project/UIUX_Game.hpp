#ifndef UIUX_GAME_HPP
#define UIUX_GAME_HPP

#include"UIUX.hpp"
#include<iostream>

using namespace std;

class UIUX_Game : public UIUX {
public:
	UIUX_Game(int cellSize, sf::RenderWindow* window) : UIUX(cellSize, window) {};
	void drawBoard(int n, int m) {
		//cout << n << " " << m << " " << getCellSize() << "\n";
		// Vẽ các đường ngang
		for (int i = 0; i <= n; i++) {
			// Tạo mảng vertex cho đường thẳng
			sf::VertexArray line(sf::PrimitiveType::Lines, 2);

			float posX, posY;

			posX = 0; posY = i * getCellSize();
			line[0].position = sf::Vector2f({ posX, posY });
			line[0].color = sf::Color::Black;

			posX = m * getCellSize(); posY = i * getCellSize();
			line[1].position = sf::Vector2f({ posX, posY });
			line[1].color = sf::Color::Black;

			getWindow()->draw(line);
		}

		// Vẽ các đường dọc
		for (int i = 0; i <= m; i++) {
			// Tạo mảng vertex cho đường thẳng
			sf::VertexArray line(sf::PrimitiveType::Lines, 2);

			float posX, posY;

			posX = i * getCellSize(); posY = 0;
			line[0].position = sf::Vector2f({ posX, posY });
			line[0].color = sf::Color::Black;

			posX = i * getCellSize(); posY = n * getCellSize();
			line[1].position = sf::Vector2f({ posX, posY });
			line[1].color = sf::Color::Black;

			getWindow()->draw(line);
		}
	}
	void drawAllMoves(Human& player) {
		vector<pair<int, int>> moves = player.getMoves();
		for (auto p : moves) drawMove(p.first, p.second, player.getSymbol());
	}
	void drawMove(int x, int y, char player) {
		//cout << x << " " << y << " " << player << "\n";
		if (player == 'O') {
			sf::Text O(getFont());
			O.setString("O");
			O.setCharacterSize(40);
			O.setFillColor(sf::Color::Red);

			// Tính toán vị trí trung tâm cho chữ "O"
			float xPos = x * getCellSize() + getCellSize() / 2 - O.getLocalBounds().size.x / 2 - 2;
			float yPos = y * getCellSize() + getCellSize() / 2 - O.getLocalBounds().size.y / 2 - 10; // trừ để căn chỉnh lại cho đẹp mắt

			O.setPosition({ xPos, yPos });
			getWindow()->draw(O);
			//cout << xPos << " " << yPos << " " << 'O' << "\n";
		}
		else {
			sf::Text X(getFont());
			X.setString("X");
			X.setCharacterSize(40);
			X.setFillColor(sf::Color::Blue);

			// Tính toán vị trí trung tâm cho chữ "X"
			float xPos = x * getCellSize() + getCellSize() / 2 - X.getLocalBounds().size.x / 2 - 2;
			float yPos = y * getCellSize() + getCellSize() / 2 - X.getLocalBounds().size.y / 2 - 10; // trừ để căn chỉnh lại cho đẹp mắt

			X.setPosition({ xPos, yPos });
			getWindow()->draw(X);
			//cout << xPos << " " << yPos << " " << 'X' << "\n";
		}
	}
};

#endif // !UIUX_GAME_HPP
