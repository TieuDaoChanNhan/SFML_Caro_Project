#ifndef UIUX_HPP
#define UIUX_HPP

#include <iostream>
#include "Human.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class UIUX {
private:
    // --- Private Members ---
    sf::Font font;
    int cellSize;
    sf::RenderWindow* window;

protected:
    // --- Protected Helper Functions ---
    bool loadFont() {
        if (!font.openFromFile("./arial.ttf")) {
            cout << "Error Loading Font" << "\n";
            return false;
        }
        return true;
    }

public:
    // --- Constructor ---
    UIUX(int cellSize, sf::RenderWindow* window) : cellSize(cellSize), window(window) {
        if (!loadFont()) {
            cout << "UIUX constructor: Failed to load font." << endl;
        }
    };

    // --- Public Accessors and Mutators ---
    sf::RenderWindow* getWindow() {
        return window;
    }

    sf::Font& getFont() {
        return font;
    }

    int getCellSize() {
        return cellSize;
    }

    void setCellSize(int cellSize) {
        this->cellSize = cellSize;
    }
};

#endif // !UIUX_HPP