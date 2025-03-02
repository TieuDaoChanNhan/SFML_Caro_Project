#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Board {
public:
	Board(int n, int m, int cellSize) :n(n), m(m), cellSize(cellSize) {
		// Cấp phát bộ nhớ cho bàn cờ
		board = new char* [n];
		for (int i = 0; i < n; i++) {
			board[i] = new char[m];
			for (int j = 0; j < m; j++) board[i][j] = ' ';
		}
	}
	char getCell(int x, int y) {
		return board[x][y];
	}
	void setCell(int x, int y, char val) {
		board[x][y] = val;
	}
	int getCellSize() {
		return cellSize;
	}
	int getN() {
		return n;
	}
	int getM() {
		return m;
	}
private:
	int n, m, cellSize;
	char** board;
};

class Player {
private:
	char symbol;
public:
	Player(char symbol) :symbol(symbol) {};
	char getSymbol(){
		return symbol;
	}
};

class UI {
private:
	sf::Font font;
	int cellSize;
public:
	UI(int cellSize) :cellSize(cellSize) {};
	void drawBoard(sf::RenderWindow& window, int n, int m) {
		// Vẽ các đường ngang
		for (int i = 0; i <= n; i++) {
			// Tạo mảng vertex cho đường thẳng
			sf::VertexArray line(sf::PrimitiveType::Lines, 2);

			float posX, posY;

			posX = 0; posY = i * cellSize;
			line[0].position = sf::Vector2f({ posX, posY });
			line[0].color = sf::Color::Black;

			posX = m * cellSize; posY = i * cellSize;
			line[1].position = sf::Vector2f({ posX, posY });
			line[1].color = sf::Color::Black;

			window.draw(line);
		}

		// Vẽ các đường dọc
		for (int i = 0; i <= m; i++) {
			// Tạo mảng vertex cho đường thẳng
			sf::VertexArray line(sf::PrimitiveType::Lines, 2);

			float posX, posY;

			posX = i * cellSize; posY = 0;
			line[0].position = sf::Vector2f({ posX, posY });
			line[0].color = sf::Color::Black;

			posX = i * cellSize; posY = n * cellSize;
			line[1].position = sf::Vector2f({ posX, posY });
			line[1].color = sf::Color::Black;

			window.draw(line);
		}
	}
	bool loadFont() {
		// Tạo font chữ
		if (!font.openFromFile("./arial.ttf")) {
			cout << "Error Loading Font" << "\n";
			return 0;
		}
		return 1;
	}
	void drawMove(sf::RenderWindow& window, int x, int y, char player) {
		if (player == 'O') {
			sf::Text O(font);
			O.setString("O");
			O.setCharacterSize(40);
			O.setFillColor(sf::Color::Red);

			// Tính toán vị trí trung tâm cho chữ "O"
			float xPos = x * cellSize + cellSize / 2 - O.getLocalBounds().size.x / 2 - 2;
			float yPos = y * cellSize + cellSize / 2 - O.getLocalBounds().size.y / 2 - 10; // trừ để căn chỉnh lại cho đẹp mắt

			O.setPosition({ xPos, yPos });
			window.draw(O);
		}
		else {
			sf::Text X(font);
			X.setString("X");
			X.setCharacterSize(40);
			X.setFillColor(sf::Color::Blue);

			// Tính toán vị trí trung tâm cho chữ "X"
			float xPos = x * cellSize + cellSize / 2 - X.getLocalBounds().size.x / 2 - 2;
			float yPos = y * cellSize + cellSize / 2 - X.getLocalBounds().size.y / 2 - 10; // trừ để căn chỉnh lại cho đẹp mắt

			X.setPosition({ xPos, yPos });
			window.draw(X);
		}
	}
	sf::RectangleShape drawWinPopup(sf::RenderWindow& window, char winnerSymbol) {
		float px, py;
		// Tạo hộp thoại thông báo chiến thắng
		sf::RectangleShape popup(sf::Vector2f(500, 150));
		px = (window.getSize().x - popup.getSize().x) / 2;
		py = (window.getSize().y - popup.getSize().y) / 2;
		popup.setPosition({ px, py });
		popup.setFillColor(sf::Color::Blue);

		sf::Text popupText(font);
		string winMessage = "Congratulation player ";
		winMessage += winnerSymbol;
		winMessage += " on winning!";
		popupText.setString(winMessage);
		popupText.setCharacterSize(24);
		px = popup.getPosition().x + (popup.getSize().x - popupText.getLocalBounds().size.x) / 2;
		py = popup.getPosition().y + (popup.getSize().y - popupText.getLocalBounds().size.y) / 5;
		popupText.setPosition({ px, py });
		popupText.setFillColor(sf::Color::White);

		// Tạo nút "OK"
		sf::RectangleShape okButton(sf::Vector2f(100, 50));
		px = popup.getPosition().x + (popup.getSize().x - okButton.getSize().x) / 2;
		py = popup.getPosition().y + (popup.getSize().y - okButton.getSize().y) * 4 / 5;
		okButton.setPosition({ px, py });
		okButton.setFillColor(sf::Color::Green);

		sf::Text okText(font);
		okText.setString("Clear");
		okText.setCharacterSize(20);
		px = okButton.getPosition().x + (okButton.getSize().x - okText.getLocalBounds().size.x) / 2;
		py = okButton.getPosition().y + (okButton.getSize().y - okText.getLocalBounds().size.y) / 2;
		okText.setPosition({ px, py });
		okText.setFillColor(sf::Color::White);

		window.draw(popup);
		window.draw(popupText);
		window.draw(okButton);
		window.draw(okText);

		return okButton;
	}
};

class Game {
private:
	Board board;
	Player playerO, playerX;
	Player* currentPlayer;
	UI ui;
	vector<pair<int, int>> movesO, movesX;
	bool isWin;

public:
	Game(int n, int m, int cellSize)
		: board(n, m, cellSize), playerO('O'), playerX('X'), ui(cellSize), isWin(false) {
		currentPlayer = &playerO;
		ui.loadFont();
	}
	
	void run() {
		unsigned int height = board.getN() * board.getCellSize();
		unsigned int width = board.getM() * board.getCellSize();

		sf::RenderWindow window(sf::VideoMode({ height, width }), "Caro Board Game");

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

						if (board.getCell(x,y) == ' ') { // Nếu ô đó chưa được chọn
							board.setCell(x, y, currentPlayer->getSymbol());
							if (currentPlayer->getSymbol() == 'O') movesO.push_back(make_pair(x, y));
							else movesX.push_back(make_pair(x, y));
							// Kiểm tra chiến thắng
							isWin = checkWin(x, y);

							// Chuyển người chơi
							if (!isWin) changePlayer();
						}
					}
				}
				window.clear(sf::Color::White);

				ui.drawBoard(window, board.getN(), board.getM());
				 
				for (auto p : movesO) ui.drawMove(window, p.first, p.second, 'O');

				for (auto p : movesX) ui.drawMove(window, p.first, p.second, 'X');

				if (isWin) {
					sf::RectangleShape okButton = ui.drawWinPopup(window, currentPlayer->getSymbol());

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

	}

	void changePlayer() {
		if (currentPlayer == &playerO) currentPlayer = &playerX;
		else currentPlayer = &playerO;
	}

	bool checkInside(int xPos, int yPos) { // Check vị trí đang ở trong bảng
		return (xPos >= 0 && xPos < board.getN() && yPos >= 0 && yPos < board.getM());
	}
	bool checkDirection(int xPos, int yPos, int xMove, int yMove) {
		int xCrr, yCrr; // Biến kiểm soát vị trí x và y hiện tại trong khi check
		int cnt = 1; // Đếm số lượng ô giống nhau

		xCrr = xPos; yCrr = yPos;
		while (checkInside(xCrr - xMove, yCrr - yMove) && board.getCell(xCrr - xMove, yCrr - yMove) == currentPlayer->getSymbol()) {
			xCrr -= xMove; yCrr -= yMove;
			cnt++;
		}

		xCrr = xPos; yCrr = yPos;
		while (checkInside(xCrr + xMove, yCrr + yMove) && board.getCell(xCrr + xMove, yCrr + yMove) == currentPlayer->getSymbol()) {
			xCrr += xMove; yCrr += yMove;
			cnt++;
		}

		if (cnt >= 5) return true;
		return false;
	}
	bool checkWin(int xPos, int yPos) {
		for (int i = 0; i < board.getN(); i++) {
			for (int j = 0; j < board.getM(); j++)
				if (board.getCell(i, j) == ' ') cout << ".";
				else cout << board.getCell(i, j);
			cout << "\n";
		}
		int xMove, yMove; // Biến thêm vào vị trí x và y để đi check ngang dọc chéo

		// Check hàng dọc
		xMove = 1; yMove = 0;
		if (checkDirection(xPos, yPos, xMove, yMove)) return true;

		// Check hàng ngang
		xMove = 0; yMove = 1;
		if (checkDirection(xPos, yPos, xMove, yMove)) return true;

		// Check hàng dọc
		xMove = 1; yMove = 1;
		if (checkDirection(xPos, yPos, xMove, yMove)) return true;

		xMove = 1; yMove = -1;
		if (checkDirection(xPos, yPos, xMove, yMove)) return true;

		return false; //Check 3 lần không được tức là game chưa end
	}

	void reset() {
		if (!movesO.empty() && !movesX.empty()) {
			movesO.clear();
			movesX.clear();
			for (int i = 0; i < board.getN(); i++)
				for (int j = 0; j < board.getM(); j++)
					board.setCell(i, j, ' ');
		}
	}
};

int main() {
	Game game(15, 15, 70);
	game.run();
	return 0;
}