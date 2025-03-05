#ifndef UIUX_BEGIN_HPP
#define UIUX_BEGIN_HPP

#include "UIUX.hpp"
#include "TextBox.hpp"
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class UIUX_Begin : public UIUX {
private:
    int tmp = -1;
public:
    UIUX_Begin(int cellSize, sf::RenderWindow* window) : UIUX(cellSize, window) {};
    TextBox box = TextBox(getFont(), getWindow(), "");
    void inputBox(vector<string>* input, sf::Event& event) {
        if (input->size() != tmp) {
            tmp++;
            //cout << "current event" << " " << tmp << "\n";
            if (input->size() == 0) box = TextBox(getFont(), getWindow(), "Player O's name:");
            if (input->size() == 1) box = TextBox(getFont(), getWindow(), "Player X's name:");
            if (input->size() == 2) box = TextBox(getFont(), getWindow(), "Width of board:");
            if (input->size() == 3) box = TextBox(getFont(), getWindow(), "Length of board:");
        }
        box.setSelected(event, getWindow());
        box.handleInput(event);
        //if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        //    if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
        //        sf::Vector2f mousePos(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
        //        if (box.isOkButtonClicked(mousePos) && box.getContent() == "") {
        //            //cout << "button clicked!" << " " << box.getContent() << "\n";
        //            input->push_back(box.getContent());
        //            return;
        //        }
        //    }
        //}
        if (box.isPressedEnter(event) && box.getContent() != "") {
            //cout << "enter pressed!" << " " << box.getContent() << "\n";
            input->push_back(box.getContent());
        }
    }
};

#endif // !UIUX_BEGIN_HPP