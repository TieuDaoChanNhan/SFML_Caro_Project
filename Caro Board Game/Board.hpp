#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

class Board {
private:
    char** board;
    int n, m;
    int cellSize;

public:
    Board(int n, int m, int cellSize) : n(n), m(m), cellSize(cellSize) {
        board = new char* [n];
        for (int i = 0; i < n; i++) {
            board[i] = new char[m];
            for (int j = 0; j < m; j++) board[i][j] = ' ';
        }
    }

    // Destructor
    ~Board() {
        for (int i = 0; i < n; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    // Copy Constructor
    Board(const Board& other) : n(other.n), m(other.m), cellSize(other.cellSize) {
        board = new char* [n];
        for (int i = 0; i < n; i++) {
            board[i] = new char[m];
            for (int j = 0; j < m; j++) board[i][j] = other.board[i][j];
        }
    }

    // Assignment Operator
    Board& operator=(const Board& other) {
        if (this != &other) {
            for (int i = 0; i < n; i++) {
                delete[] board[i];
            }
            delete[] board;

            n = other.n;
            m = other.m;
            cellSize = other.cellSize;

            board = new char* [n];
            for (int i = 0; i < n; i++) {
                board[i] = new char[m];
                for (int j = 0; j < m; j++) board[i][j] = other.board[i][j];
            }
        }
        return *this;
    }

    char getCell(int x, int y) {
        return board[x][y];
    }

    int getCellSize() {
        return cellSize;
    }

    int getN() {
        return n;
    }

    int getM() {
        return m;
    }

    void setCell(int x, int y, char val) {
        board[x][y] = val;
    }

    void setN(int val) {
        n = val;
    }

    void setM(int val) {
        m = val;
    }

    void clearCell(int x, int y) {
        board[x][y] = ' ';
    }

    void resetBoard() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                board[i][j] = ' ';
            }
        }
    }

    bool isFullBoard() {
        bool check = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j] == ' ') check = false;
        return check;
    }

    std::string getBoardState() {
        std::string state = "";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                state += board[i][j];
            }
        }
        return state;
    }
};

#endif