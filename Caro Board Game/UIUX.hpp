#ifndef UIUX_HPP
#define UIUX_HPP

#include <iostream>
#include "Player.hpp"
#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <chrono>
#include <thread>

using namespace std;

class UIUX {
private:
    // --- Private Members ---
    sf::Font font;
    int cellSize;
    sf::RenderWindow* window;

    /// --- Begin Members ---
    int tmp = -1;
    bool checkValid(char c) {
        int pos;
        pos = c - 'a';
        bool checkCharacter = (pos >= 0 && pos < 26);
        pos = c - '0';
        bool checkNumber = (pos >= 0 && pos < 10);
        return (checkCharacter || checkNumber);
    }

    /// --- Game Members ---
    sf::RectangleShape undoButton, newButton, exitButton, informBox, resetButton;
    sf::Text undoText, newText, exitText, informText, resetText;
    sf::Text timerText;
    sf::RectangleShape timerSpace;
    string currentTime;
    sf::Color defaultButtonColor = sf::Color::Yellow;
    sf::Color hoverButtonColor = sf::Color(255, 255, 150); // Màu vàng nhạt hơn khi hover
    bool isHoover;
public:
    bool loadFont() {
        if (!font.openFromFile("./arial.ttf")) {
            cout << "Error Loading Font" << "\n";
            return false;
        }
        return true;
    }
    // --- Constructor ---
    UIUX(int cellSize, sf::RenderWindow* window) : cellSize(cellSize), window(window), undoText(getFont()), newText(getFont()), exitText(getFont()), timerText(getFont()), informText(getFont()), resetText(getFont()) {
        if (!loadFont()) {
            cout << "UIUX constructor: Failed to load font." << endl;
        }

        undoText.setFont(font);
        newText.setFont(font);
        exitText.setFont(font);
        informText.setFont(font);
        resetText.setFont(font);

        undoButton.setSize(sf::Vector2f(70, 40));
        undoButton.setFillColor(sf::Color::Yellow);
        undoButton.setOutlineColor(sf::Color::Black);
        undoButton.setOutlineThickness(2);

        newButton.setSize(sf::Vector2f(70, 40));
        newButton.setFillColor(sf::Color::Yellow);
        newButton.setOutlineColor(sf::Color::Black);
        newButton.setOutlineThickness(2);

        exitButton.setSize(sf::Vector2f(70, 40));
        exitButton.setFillColor(sf::Color::Yellow);
        exitButton.setOutlineColor(sf::Color::Black);
        exitButton.setOutlineThickness(2);

        timerSpace.setSize(sf::Vector2f(90, 40));
        timerSpace.setFillColor(sf::Color::Yellow);
        timerSpace.setOutlineColor(sf::Color::Black);
        timerSpace.setOutlineThickness(2);

        informBox.setSize(sf::Vector2f(400, 60));
        informBox.setFillColor(sf::Color::Cyan);
        informBox.setOutlineColor(sf::Color::Black);
        informBox.setOutlineThickness(2);

        resetButton.setSize(sf::Vector2f(70, 40));
        resetButton.setFillColor(sf::Color::Yellow);
        resetButton.setOutlineColor(sf::Color::Black);
        resetButton.setOutlineThickness(2);

        undoText.setString("Undo");
        undoText.setCharacterSize(20);
        undoText.setFillColor(sf::Color::Black);

        newText.setString("New");
        newText.setCharacterSize(20);
        newText.setFillColor(sf::Color::Black);

        exitText.setString("Exit");
        exitText.setCharacterSize(20);
        exitText.setFillColor(sf::Color::Black);

        timerText.setCharacterSize(20);
        timerText.setFillColor(sf::Color::Black);

        informText.setCharacterSize(30);
        informText.setFillColor(sf::Color::Black);
        informText.setString("Welcome to the game!");

        resetText.setString("Reset");
        resetText.setCharacterSize(20);
        resetText.setFillColor(sf::Color::Black);
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

    // --- Begin UIUX ---
    TextBox box = TextBox(getFont(), getWindow(), "");

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
            //cout << "x: " << tmp << " " << box.getContent() << "\n";
            input->push_back(box.getContent());
            box.reset(""); // Reset textbox để nhập tiếp
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Thêm độ trễ 100ms
        }
    }

    void resetIndex() {
        tmp = -1;
    }

    /// --- UIUX Game ---

    void setHoover(bool val) {
        isHoover = val;
    }

    // --- Drawing Functions ---
    void drawButtons() {
        drawSpecificButton(undoButton, undoText, 4);
        drawSpecificButton(newButton, newText, 2);
        drawSpecificButton(exitButton, exitText, 6);
        drawSpecificButton(resetButton, resetText, 8);
    }

    void drawInform() {
        float px = (getWindow()->getSize().x / 2 - informBox.getSize().x / 2);
        float py = getWindow()->getSize().y - 200 + (200 - informBox.getSize().y) / 5;
        //cout << "x: " << py << "\n";

        informBox.setPosition({ px, py });

        float tx = px + (informBox.getSize().x - informText.getLocalBounds().size.x) / 2;
        float ty = py + (informBox.getSize().y - informText.getLocalBounds().size.y) / 2 - 5;
        informText.setPosition({ tx, ty });

        getWindow()->draw(informBox);
        getWindow()->draw(informText);
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

    bool isNewButtonClicked(sf::RenderWindow& window, sf::Event& event) {
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (newButton.getGlobalBounds().contains(mousePosFloat)) return true;
            }
        }
        return false;
    }

    bool isExitButtonClicked(sf::RenderWindow& window, sf::Event& event) {
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (exitButton.getGlobalBounds().contains(mousePosFloat)) return true;
            }
        }
        return false;
    }

    bool isResetButtonClicked(sf::RenderWindow& window, sf::Event& event) {
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (resetButton.getGlobalBounds().contains(mousePosFloat)) return true;
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

    void drawAllMoves(Player& player) {
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

    void drawSpecificButton(sf::RectangleShape& button, sf::Text& text, int pos) {
        float px = (getWindow()->getSize().x / 2 - button.getSize().x / 2) * pos / 6;
        float py = getWindow()->getSize().y - 200 + (200 - button.getSize().y) * 4 / 5;

        button.setPosition({ px, py });

        float tx = px + (button.getSize().x - text.getLocalBounds().size.x) / 2;
        float ty = py + (button.getSize().y - text.getLocalBounds().size.y) / 2 - 5;
        text.setPosition({ tx, ty });

        // Hiệu ứng hover
        if (isHoover && pos != 10) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*getWindow());
            sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (button.getGlobalBounds().contains(mousePosFloat)) {
                button.setFillColor(hoverButtonColor);
            }
            else {
                button.setFillColor(defaultButtonColor);
            }
        }

        getWindow()->draw(button);
        getWindow()->draw(text);
    }

    void drawTimer(sf::Time remainingTime, bool isPaused) {
        currentTime = std::to_string(static_cast<int>(remainingTime.asSeconds()));
        if (currentTime[0] == '-') currentTime = "0";
        currentTime = "Time: " + currentTime;
        timerText.setString(currentTime);
        if (isPaused) {
            timerSpace.setFillColor(sf::Color(150, 150, 150)); // Màu xám khi tạm dừng
        }
        else {
            timerSpace.setFillColor(sf::Color::Yellow); // Màu vàng khi chạy
        }
        drawSpecificButton(timerSpace, timerText, 10);
    }

    void setInformText(string val) {
        informText.setString(val);
    }

    bool isTimerClicked(sf::RenderWindow& window, sf::Event& event) {
        if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (timerSpace.getGlobalBounds().contains(mousePosFloat)) return true;
            }
        }
        return false;
    }
};

#endif // !UIUX_HPP