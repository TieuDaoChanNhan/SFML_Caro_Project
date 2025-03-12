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
    sf::Text text; // Text inside the textbox
    sf::RectangleShape box; // Background box of the textbox
    std::string content = ""; // Content of the textbox
    bool selected; // Indicates if the textbox is selected
    sf::Text headerText; // Header text of the textbox
    sf::RectangleShape topBar; // Top bar of the textbox
    sf::VertexArray underline; // Underline of the textbox
    sf::Color defaultBoxColor; // Default color of the box
    sf::Color hoverBoxColor; // Hover color of the box
    sf::Color selectedUnderlineColor; // Color of underline when selected
    sf::Color defaultUnderlineColor; // Default color of underline

public:
    TextBox(sf::Font& font, sf::RenderWindow* window, const std::string& header)
        : selected(true), text(font), headerText(font), // Auto select when created
        defaultBoxColor(sf::Color(50, 150, 250)),
        hoverBoxColor(sf::Color(70, 170, 255)),
        selectedUnderlineColor(sf::Color::Yellow),
        defaultUnderlineColor(sf::Color::White)
    {
        box.setSize(sf::Vector2f(550, 180));
        box.setPosition({ (window->getSize().x - box.getSize().x) / 2, (window->getSize().y - box.getSize().y) / 2 });
        box.setFillColor(defaultBoxColor);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);

        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition({ box.getPosition().x + (box.getSize().x - text.getLocalBounds().size.x) / 2, box.getPosition().y + (box.getSize().y - text.getLocalBounds().size.y) * 2 / 3 });

        headerText.setString(header);
        headerText.setCharacterSize(30);
        headerText.setFillColor(sf::Color::White);
        headerText.setPosition({ box.getPosition().x + (box.getSize().x - headerText.getLocalBounds().size.x) / 2, box.getPosition().y + (box.getSize().y - headerText.getLocalBounds().size.y) / 3 });

        topBar.setSize(sf::Vector2f(box.getSize().x, 40));
        topBar.setOutlineColor(sf::Color::Black);
        topBar.setOutlineThickness(2);
        sf::Color darkBlue(25, 118, 210);
        topBar.setFillColor(darkBlue);
        underline = sf::VertexArray(sf::PrimitiveType::Lines, 2);
        underline[0].color = defaultUnderlineColor;
        underline[1].color = defaultUnderlineColor;

        underline[0].position = sf::Vector2f(box.getPosition().x + 50, text.getPosition().y + 25);
        underline[1].position = sf::Vector2f(box.getPosition().x + 500 + text.getLocalBounds().size.x, text.getPosition().y + 25);
    }

    void draw(sf::RenderWindow& window) {
        // Hover effect only when mouse is over
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        if (box.getGlobalBounds().contains(mousePosFloat)) {
            box.setFillColor(hoverBoxColor);
        }
        else {
            box.setFillColor(defaultBoxColor);
        }

        window.draw(box);
        window.draw(headerText);
        text.setString(content);
        text.setPosition({ box.getPosition().x + (box.getSize().x - text.getLocalBounds().size.x) / 2, box.getPosition().y + (box.getSize().y - text.getLocalBounds().size.y) * 2 / 3 });
        window.draw(text);

        // Draw underline, change color when selected.
        sf::Color underlinecolor = selected ? selectedUnderlineColor : defaultUnderlineColor;
        underline[0].color = underlinecolor;
        underline[1].color = underlinecolor;
        window.draw(underline);

        // Draw top bar of textbox
        topBar.setPosition({ box.getPosition().x, box.getPosition().y - 5 });
        window.draw(topBar);
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

    void setSelected(sf::Event& event, sf::RenderWindow* window) {
        // Remove selection by mouse click
    }

    bool isSelected() const {
        return selected;
    }

    std::string getContent() const {
        return content;
    }

    bool isPressedEnter(sf::Event& event) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) return true;
        return false;
    }

    void reset(const std::string& newHeader) {
        content = "";
        headerText.setString(newHeader);
    }

    void resetContent() {
        content = "";
    }
};

#endif // TEXTBOX_HPP