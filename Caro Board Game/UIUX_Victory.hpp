#ifndef UIUX_VICTORY_HPP
#define UIUX_VICTORY_HPP

#include "UIUX.hpp"
#include <iostream>

using namespace std;

class UIUX_Victory : public UIUX {
public:
    // --- Constructor ---
    UIUX_Victory(int cellSize, sf::RenderWindow* window) : UIUX(cellSize, window) {}

    // --- Drawing Functions ---
    sf::RectangleShape drawWinPopup(bool draw, string winnerSymbol) {
        float px, py;

        // Tạo hộp thoại thông báo chiến thắng
        sf::RectangleShape popup(sf::Vector2f(500, 150));
        px = (getWindow()->getSize().x - popup.getSize().x) / 2;
        py = (getWindow()->getSize().y - popup.getSize().y) / 2;
        popup.setPosition({ px, py });
        popup.setFillColor(sf::Color::Blue);
        popup.setOutlineColor(sf::Color::Black);
        popup.setOutlineThickness(2);

        sf::Text popupText(getFont());
        string winMessage;
        if (!draw) {
            winMessage += "Congratulation player ";
            winMessage += winnerSymbol;
            winMessage += " on winning!";
        }
        else {
            winMessage = "This game is draw!";
        }
        popupText.setString(winMessage);
        popupText.setCharacterSize(24);
        px = popup.getPosition().x + (popup.getSize().x - popupText.getLocalBounds().size.x) / 2;
        py = popup.getPosition().y + (popup.getSize().y - popupText.getLocalBounds().size.y) / 5;
        popupText.setPosition({ px, py });
        popupText.setFillColor(sf::Color::White);

        // Tạo nút "Clear"
        sf::RectangleShape okButton(sf::Vector2f(100, 50));
        px = popup.getPosition().x + (popup.getSize().x - okButton.getSize().x) / 2;
        py = popup.getPosition().y + (popup.getSize().y - okButton.getSize().y) * 4 / 5;
        okButton.setPosition({ px, py });
        okButton.setFillColor(sf::Color::Green);

        sf::Text okText(getFont());
        okText.setString("Clear");
        okText.setCharacterSize(20);
        px = okButton.getPosition().x + (okButton.getSize().x - okText.getLocalBounds().size.x) / 2;
        py = okButton.getPosition().y + (okButton.getSize().y - okText.getLocalBounds().size.y) / 2;
        okText.setPosition({ px, py });
        okText.setFillColor(sf::Color::White);

        getWindow()->draw(popup);
        getWindow()->draw(popupText);
        getWindow()->draw(okButton);
        getWindow()->draw(okText);

        return okButton;
    }
};

#endif // !UIUX_VICTORY_HPP