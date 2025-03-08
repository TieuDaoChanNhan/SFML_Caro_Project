#ifndef UIUX_BEGIN_HPP
#define UIUX_BEGIN_HPP

#include "UIUX.hpp"
#include "TextBox.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class UIUX_Begin : public UIUX {
private:
    // --- Private Members ---
    int tmp = -1;

public:
    // --- Constructor ---
    UIUX_Begin(int cellSize, sf::RenderWindow* window) : UIUX(cellSize, window) {}

    // --- Public Members ---
    TextBox box = TextBox(getFont(), getWindow(), "");

    // --- Input Handling Functions ---
    void inputBox(vector<string>* input, sf::Event& event) {
        if (input->size() != tmp) {
            tmp++;
            if (input->size() == 0) box = TextBox(getFont(), getWindow(), "Player O's type (player or bot):");
            if (input->size() == 1) box = TextBox(getFont(), getWindow(), "Player X's type (player or bot):");
            if (input->size() == 2) box = TextBox(getFont(), getWindow(), "Player O's name:");
            if (input->size() == 3) box = TextBox(getFont(), getWindow(), "Player X's name:");
            if (input->size() == 4) box = TextBox(getFont(), getWindow(), "Width of board:");
            if (input->size() == 5) box = TextBox(getFont(), getWindow(), "Length of board:");
        }
        box.setSelected(event, getWindow());
        box.handleInput(event);
        if (box.isPressedEnter(event) && box.getContent() != "") {
            input->push_back(box.getContent());
        }
    }
};

#endif // !UIUX_BEGIN_HPP