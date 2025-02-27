#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

int n = 15, m = 15; // Kích thước bàn cờ (có thể thay đổi sau này);
char board[100][100]; // Mảng chứa bàn cờ ảo
char currentSigned = 'O'; // Kí hiệu hiện tại sẽ điền vào bảng (bắt đầu là O)
int cellSize = 40; // Kích thước mỗi ô trong bàn cờ
unsigned int height = 15 * cellSize;
unsigned int width = 15 * cellSize;
pair<int, int> saveO[10007], saveX[10007];
int slO = 0, slX = 0;

void changeSigned() { // Hàm đổi người chơi
	if (currentSigned == 'O') currentSigned = 'X';
	else currentSigned = 'O';
}

void drawMove(sf::RenderWindow& window, int x, int y, char player) { // Hàm vẽ bước đi vẽ vào ô của người chơi hiện tại
	
	// Tạo font chữ
	sf::Font font;
	if (!font.openFromFile("./arial.ttf")) {
		cout << "Error Loading Font" << "\n";
		return;
	}

	if (player == 'O') {
		char c[2] = "O";
		sf::Text O(font);
		O.setString("O");
		O.setCharacterSize(30);
		O.setFillColor(sf::Color::Red);
		float xPos = x * cellSize + 10;
		float yPos = y * cellSize + 10;
		O.setPosition({ xPos, yPos });
		window.draw(O);
	}
	else {
		char c[2] = "X";
		sf::Text X(font);
		X.setString("X");
		X.setCharacterSize(30);
		X.setFillColor(sf::Color::Blue);
		float xPos = x * cellSize + 10;
		float yPos = y * cellSize + 10;
		X.setPosition({ xPos, yPos });
		window.draw(X);
	}
}

bool checkInside(int xPos, int yPos) { // Check vị trí đang ở trong bảng
	return (xPos >= 0 && xPos < n && yPos >= 0 && yPos < m);
}

bool checkDirection(int xPos, int yPos, int xMove, int yMove) {
	int xCrr, yCrr; // Biến kiểm soát vị trí x và y hiện tại trong khi check
	int cnt = 1; // Đếm số lượng ô giống nhau

	xCrr = xPos; yCrr = yPos;
	while (checkInside(xCrr - xMove, yCrr - yMove) && (board[xCrr - xMove][yCrr - yMove] == currentSigned)) {
		xCrr -= xMove; yCrr -= yMove;
		cnt++;
	}

	xCrr = xPos; yCrr = yPos;
	while (checkInside(xCrr - xMove, yCrr - yMove) && (board[xCrr + xMove][yCrr + yMove] == currentSigned)) {
		xCrr += xMove; yCrr += yMove;
		cnt++;
	}

	if (cnt >= 5) return true;
	return false;
}

bool checkWin(int xPos, int yPos) {
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

void drawBoard(sf::RenderWindow& window) {
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

int main() {

	sf::RenderWindow window(sf::VideoMode({height, width}), "Caro Board Game");
	
	//Setup bàn cờ ban đầu
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			board[i][j] = ' ';

	bool isWin = false;

	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) { // Kiểm tra có sự kiện nào xảy ra trong cửa sổ ứng dụng
			if (event -> is <sf::Event::Closed>()) {
				window.close();
			}

			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
				if (mouseButtonPressed->button == sf::Mouse::Button::Left){ // Khi người chơi bấm chuột trái
					sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Lấy vị trí con chuột
					int x = mousePos.x / cellSize;
					int y = mousePos.y / cellSize;

					if (board[x][y] == ' ') { // Nếu ô đó chưa được chọn
						board[x][y] = currentSigned;
						if (currentSigned == 'O') saveO[slO++] = make_pair(x, y);
						else saveX[slX++] = make_pair(x, y);
					}
					
					// Kiểm tra chiến thắng
					isWin = checkWin(x, y);

					// Chuyển người chơi
					changeSigned();
				}
			}
		}

		window.clear(sf::Color::White); // Làm mới màn hình với nền trắng

		drawBoard(window); // Vẽ bảng cờ caro

		for (int i = 0; i < slO; i++) drawMove(window, saveO[i].first, saveO[i].second, 'O');

		for (int i = 0; i < slX; i++) drawMove(window, saveX[i].first, saveX[i].second, 'X');

		window.display();

		if (isWin) {
			changeSigned();
			cout << "Cogratulation Player " << currentSigned << " for winning!";
			window.close();
		}
	}
	return 0;
}