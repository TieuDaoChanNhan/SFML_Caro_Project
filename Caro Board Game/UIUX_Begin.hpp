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
#include <thread>
#include <chrono>

using namespace std;

class UIUX_Begin : public UIUX {
private:
    // --- Private Members ---
    int tmp = -1;
    bool checkValid(char c) {
        int pos;
        pos = c - 'a';
        bool checkCharacter =  (pos >= 0 && pos < 26);
        pos = c - '0';
        bool checkNumber = (pos >= 0 && pos < 10);
        return (checkCharacter || checkNumber);
    }
public:
    // --- Constructor ---
    UIUX_Begin(int cellSize, sf::RenderWindow* window) : UIUX(cellSize, window) {}

    // --- Public Members ---
    TextBox box = TextBox(getFont(), getWindow(), "");

    // --- Input Handling Functions ---
    void inputBox(vector<string>* input, sf::Event& event) {
        if (input->size() != tmp) {
            tmp++;
            switch (input->size()) {
            case 0:
                box = TextBox(getFont(), getWindow(), "Type player O's type (player or bot):");
                break;
            case 1:
                box = TextBox(getFont(), getWindow(), "Type player X's type (player or bot):");
                break;
            case 2:
                box = TextBox(getFont(), getWindow(), "Type player O's name:");
                break;
            case 3:
                box = TextBox(getFont(), getWindow(), "Type player X's name:");
                break;
            case 4:
                box = TextBox(getFont(), getWindow(), "Type width of board:");
                break;
            case 5:
                box = TextBox(getFont(), getWindow(), "Type length of board:");
                break;
            }
        }

        box.handleInput(event);

        if (box.getContent().size() != 0 && !checkValid(box.getContent()[0])) {
            box.resetContent();
            return;
        }

        if (box.isPressedEnter(event)) {
            cout << "x: " << tmp << " " << box.getContent() << "\n";
            input->push_back(box.getContent());
            box.reset(""); // Reset textbox để nhập tiếp
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Thêm độ trễ 100ms
        }
    }

    void resetIndex() {
        tmp = -1;
    }
};

#endif // !UIUX_BEGIN_HPP