#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class TextBox {
private:
    sf::Text text;
    sf::RectangleShape box;
    std::string content;
    bool selected;
    sf::Text headerText;
    sf::RectangleShape okButton;
    sf::Text okText;

public:
    TextBox(sf::Font& font, sf::RenderWindow* window, const std::string& header)
        : selected(false), text(font), headerText(font), okText(font) {
        //selected = true;
        float posX, posY;

        // Khởi tạo text box
        box.setSize(sf::Vector2f(400, 200));
        box.setPosition({ (window->getSize().x - box.getSize().x) / 2, (window->getSize().y - box.getSize().y) / 2 });
        box.setFillColor(sf::Color::Blue);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);

        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition({ box.getPosition().x + (box.getSize().x - headerText.getLocalBounds().size.x) / 2, box.getPosition().y + (box.getSize().y - headerText.getLocalBounds().size.y) * 3 / 5 });

        // Khởi tạo header text
        headerText.setString(header);
        headerText.setCharacterSize(30);
        headerText.setFillColor(sf::Color::White);
        headerText.setPosition({ box.getPosition().x + (box.getSize().x - headerText.getLocalBounds().size.x) / 2, box.getPosition().y + (box.getSize().y - headerText.getLocalBounds().size.y) / 4 });
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(headerText);
        text.setString(content);
        text.setPosition({ box.getPosition().x + (box.getSize().x - text.getLocalBounds().size.x) / 2, box.getPosition().y + (box.getSize().y - text.getLocalBounds().size.y) * 3 / 5 });
        window.draw(text);
    }

    void handleInput(sf::Event event) {
        if (selected) {
            if (const auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
                if (textEntered->unicode < 128) {
                    if (textEntered->unicode == '\b' && !content.empty()) {
                        content.pop_back();
                    }
                    else if (textEntered->unicode != '\b') {
                        content += static_cast<char>(textEntered->unicode);
                    }
                }
            }
        }
    }

    bool isSelected() const {
        return selected;
    }

    void setSelected(sf::Event& event, sf::RenderWindow* window) {
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (box.getGlobalBounds().contains(mousePosFloat)) {
                    selected = true;
                }
                else {
                    selected = false;
                }
            }
        }
    }

    std::string getContent() const {
        return content;
    }

    bool isPressedEnter(sf::Event& event) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) return true;
        return false;
    }

    bool isOkButtonClicked(sf::Vector2f mousePos) const {
        return okButton.getGlobalBounds().contains(mousePos);
    }

    void reset(const std::string& newHeader) {
        content.clear();
        headerText.setString(newHeader);
    }
};

#endif // TEXTBOX_HPP