#ifndef BOARD_HPP
#define BOARD_HPP

class Board {
private:
    // --- Private Members ---
    char** board;       // Mảng 2D chứa trạng thái của từng ô trên bàn cờ
    int n, m;           // Kích thước bàn cờ (n = số dòng, m = số cột)
    int cellSize;       // Kích thước của mỗi ô vuông trên bàn cờ

public:
    // --- Constructor ---
    Board(int n, int m, int cellSize) : n(n), m(m), cellSize(cellSize) {
        // Cấp phát bộ nhớ cho bàn cờ
        board = new char* [n];
        for (int i = 0; i < n; i++) {
            board[i] = new char[m];
            for (int j = 0; j < m; j++) board[i][j] = ' ';
        }
    }

    // --- Accessors (Getters) ---
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

    // --- Mutators (Setters) ---
    void setCell(int x, int y, char val) {
        board[x][y] = val;
    }

    void setN(int val) {
        n = val;
    }

    void setM(int val) {
        m = val;
    }

    // --- Game Logic Functions ---
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
};

#endif