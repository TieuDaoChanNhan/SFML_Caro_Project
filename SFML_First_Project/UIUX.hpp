#ifndef UIUX_HPP
#define UIUX_HPP

#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class UIUX {
private:
	sf::Font font;
	int cellSize;
	sf::RenderWindow* window;
	bool loadFont() {
		// Tạo font chữ
		if (!font.openFromFile("./arial.ttf")) {
			cout << "Error Loading Font" << "\n";
			return 0;
		}
		return 1;
	}
public:
	UIUX(int cellSize, sf::RenderWindow* window) :cellSize(cellSize), window(window) {
		loadFont();
	};
	void drawBoard(int n, int m) {
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

			window->draw(line);
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

			window->draw(line);
		}
	}
	void drawMove(int x, int y, char player) {
		//cout << x << " " << y << " " << player << "\n";
		if (player == 'O') {
			sf::Text O(font);
			O.setString("O");
			O.setCharacterSize(40);
			O.setFillColor(sf::Color::Red);

			// Tính toán vị trí trung tâm cho chữ "O"
			float xPos = x * cellSize + cellSize / 2 - O.getLocalBounds().size.x / 2 - 2;
			float yPos = y * cellSize + cellSize / 2 - O.getLocalBounds().size.y / 2 - 10; // trừ để căn chỉnh lại cho đẹp mắt

			O.setPosition({ xPos, yPos });
			window->draw(O);
			//cout << xPos << " " << yPos << " " << 'O' << "\n";
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
			window->draw(X);
			//cout << xPos << " " << yPos << " " << 'X' << "\n";
		}
	}
	sf::RectangleShape drawWinPopup(char winnerSymbol) {
		float px, py;
		// Tạo hộp thoại thông báo chiến thắng
		sf::RectangleShape popup(sf::Vector2f(500, 150));
		px = (window->getSize().x - popup.getSize().x) / 2;
		py = (window->getSize().y - popup.getSize().y) / 2;
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

		window->draw(popup);
		window->draw(popupText);
		window->draw(okButton);
		window->draw(okText);

		return okButton;
	}
};

#endif // !UIUX_HPP
