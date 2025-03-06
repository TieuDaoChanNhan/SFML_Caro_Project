#ifndef UIUX_GAME_HPP
#define UIUX_GAME_HPP

#include "UIUX.hpp"
#include <iostream>

using namespace std;

class UIUX_Game : public UIUX {
private:
    sf::RectangleShape undoButton;
    sf::Text undoText;
public:
    // --- Constructor ---
    UIUX_Game(int cellSize, sf::RenderWindow* window) : UIUX(cellSize, window), undoText(getFont()) {};

    // --- Drawing Functions ---
    void drawUndoButton() {
        undoButton.setSize(sf::Vector2f(70, 40));
        undoButton.setFillColor(sf::Color::Yellow);
        undoButton.setOutlineColor(sf::Color::Black);
        undoButton.setOutlineThickness(2);
        undoText.setString("Undo");
        undoText.setCharacterSize(20);
        undoText.setFillColor(sf::Color::Black);
        float px = getWindow()->getSize().x / 2 - undoButton.getSize().x / 2; // Đặt ở giữa theo chiều ngang
        float py = getWindow()->getSize().y - (100 / 2) - (undoButton.getSize().y / 2); // Đặt ở giữa theo chiều dọc của phần không gian thêm

        undoButton.setPosition({ px, py });

        float tx = px + (undoButton.getSize().x - undoText.getLocalBounds().size.x) / 2;
        float ty = py + (undoButton.getSize().y - undoText.getLocalBounds().size.y) / 2 - 5;
        undoText.setPosition({ tx, ty });

        getWindow()->draw(undoButton);
        getWindow()->draw(undoText);
    }

    bool isUndoButtonClicked(sf::RenderWindow& window, sf::Event& event) {
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (undoButton.getGlobalBounds().contains(mousePosFloat)) return true;
            }
        }
        return false;
    }

    void drawBoard(int n, int m) {
        // Vẽ các đường ngang
        for (int i = 0; i <= n; i++) {
            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            float posX, posY;

            posX = 0;
            posY = i * getCellSize();
            line[0].position = sf::Vector2f({ posX, posY });
            line[0].color = sf::Color::Black;

            posX = m * getCellSize();
            posY = i * getCellSize();
            line[1].position = sf::Vector2f({ posX, posY });
            line[1].color = sf::Color::Black;

            getWindow()->draw(line);
        }

        // Vẽ các đường dọc
        for (int i = 0; i <= m; i++) {
            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            float posX, posY;

            posX = i * getCellSize();
            posY = 0;
            line[0].position = sf::Vector2f({ posX, posY });
            line[0].color = sf::Color::Black;

            posX = i * getCellSize();
            posY = n * getCellSize();
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
        if (player == 'O') {
            sf::Text O(getFont());
            O.setString("O");
            O.setCharacterSize(40);
            O.setFillColor(sf::Color::Red);

            float xPos = x * getCellSize() + getCellSize() / 2 - O.getLocalBounds().size.x / 2 - 2;
            float yPos = y * getCellSize() + getCellSize() / 2 - O.getLocalBounds().size.y / 2 - 10;

            O.setPosition({ xPos, yPos });
            getWindow()->draw(O);
        }
        else {
            sf::Text X(getFont());
            X.setString("X");
            X.setCharacterSize(40);
            X.setFillColor(sf::Color::Blue);

            float xPos = x * getCellSize() + getCellSize() / 2 - X.getLocalBounds().size.x / 2 - 2;
            float yPos = y * getCellSize() + getCellSize() / 2 - X.getLocalBounds().size.y / 2 - 10;

            X.setPosition({ xPos, yPos });
            getWindow()->draw(X);
        }
    }
};

#endif // !UIUX_GAME_HPP