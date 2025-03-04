#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include"Human.hpp"
#include"Board.hpp"
#include"Referee.hpp"
#include"UIUX.hpp"

using namespace std;

int n = 15, m = 15, cellSize = 60;
Board board(n, m, cellSize);
Human playerO('O');
Human playerX('X');
Human* currentPlayer = &playerO;
Referee referee;
bool isWin = false;
unsigned int height = board.getN() * board.getCellSize();
unsigned int width = board.getM() * board.getCellSize();

void changePlayer() {
	if (currentPlayer == &playerO) {
		currentPlayer = &playerX;
	}
	else {
		currentPlayer = &playerO;
	}
}

void reset() {
	playerO.resetMoves();
	playerX.resetMoves();
	board.resetBoard();
}

int main() {

	sf::RenderWindow window(sf::VideoMode({ height, width }), "Caro Board Game");
	UIUX uiux(cellSize, &window);

	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) { // Kiểm tra có sự kiện nào xảy ra trong cửa sổ ứng dụng
			if (event->is <sf::Event::Closed>()) {
				window.close();
			}
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseButtonPressed->button == sf::Mouse::Button::Left && !isWin) { // Khi người chơi bấm chuột trái
					sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Lấy vị trí con chuột
					int x = mousePos.x / board.getCellSize();
					int y = mousePos.y / board.getCellSize();

					if (board.getCell(x, y) == ' ') { // Nếu ô đó chưa được chọn
						board.setCell(x, y, currentPlayer->getSymbol());
						if (currentPlayer->getSymbol() == 'O') playerO.addMove(x, y);
						else playerX.addMove(x, y);
						// Kiểm tra chiến thắng
						isWin = referee.checkWin(board);

						// Chuyển người chơi
						if (!isWin) changePlayer();
					}
				}
			}
			window.clear(sf::Color::White);

			uiux.drawBoard(board.getN(), board.getM());

			playerO.drawAllMoves(uiux);
			playerX.drawAllMoves(uiux);

			if (isWin) {
				sf::RectangleShape okButton = uiux.drawWinPopup(currentPlayer->getSymbol());

				if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
					if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
						sf::Vector2f mousePos(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
						if (okButton.getGlobalBounds().contains(mousePos)) {
							isWin = false;
						}
					}
				}

				reset();
			}
			window.display();
		}
	}
	return 0;
}