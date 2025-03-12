#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

class Board {
private:
    // --- Board Data ---
    char** board; // 2D array representing the board
    int n, m;      // Board dimensions (n rows, m columns)
    int cellSize; // Size of a cell on the board

public:
    // --- Constructor ---
    Board(int n, int m, int cellSize) : n(n), m(m), cellSize(cellSize) {
        // Allocate memory for the board
        board = new char* [n];
        for (int i = 0; i < n; i++) {
            board[i] = new char[m];
            // Initialize all cells on the board as empty (' ')
            for (int j = 0; j < m; j++) board[i][j] = ' ';
        }
    }

    // --- Destructor ---
    ~Board() {
        // Deallocate memory allocated for the board
        for (int i = 0; i < n; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    // --- Copy Constructor ---
    Board(const Board& other) : n(other.n), m(other.m), cellSize(other.cellSize) {
        // Allocate memory and copy data from another board
        board = new char* [n];
        for (int i = 0; i < n; i++) {
            board[i] = new char[m];
            for (int j = 0; j < m; j++) board[i][j] = other.board[i][j];
        }
    }

    // --- Assignment Operator ---
    Board& operator=(const Board& other) {
        // Check for self-assignment
        if (this != &other) {
            // Deallocate current memory
            for (int i = 0; i < n; i++) {
                delete[] board[i];
            }
            delete[] board;

            // Copy data from another board
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

    // --- Position Check ---
    bool isInside(int x, int y) {
        // Check if the position (x, y) is within the board
        return (x >= 0 && x < n && y >= 0 && y < m);
    }

    // --- Cell Access ---
    char getCell(int x, int y) {
        // Get the value of the cell at position (x, y)
        return board[x][y];
    }

    // --- Cell Size Access ---
    int getCellSize() {
        // Get the size of a cell
        return cellSize;
    }

    // --- Board Size Access ---
    int getN() {
        // Get the number of rows
        return n;
    }

    int getM() {
        // Get the number of columns
        return m;
    }

    // --- Cell Setting ---
    void setCell(int x, int y, char val) {
        // Set the value of the cell at position (x, y)
        board[x][y] = val;
    }

    // --- Board Size Setting ---
    void setN(int val) {
        // Set the number of rows
        n = val;
    }

    void setM(int val) {
        // Set the number of columns
        m = val;
    }

    // --- Cell Clearing ---
    void clearCell(int x, int y) {
        // Set the value of the cell at position (x, y) to empty (' ')
        board[x][y] = ' ';
    }

    // --- Board Resetting ---
    void resetBoard() {
        // Set all cells on the board to empty (' ')
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                board[i][j] = ' ';
            }
        }
    }

    // --- Full Board Check ---
    bool isFullBoard() {
        // Check if all cells on the board are filled
        bool check = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j] == ' ') check = false;
        return check;
    }

    // --- Board State Retrieval ---
    std::string getBoardState() {
        // Get the board state as a string
        std::string state = "";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                state += board[i][j];
            }
        }
        return state;
    }
};

#endif // BOARD_HPP