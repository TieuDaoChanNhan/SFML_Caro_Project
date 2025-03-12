#ifndef BOTALGORITHM_HPP
#define BOTALGORITHM_HPP

#include <iostream>
#include <set>
#include "Referee.hpp"
#include "Board.hpp"

class BotAlgorithm {
private:
    // --- Private Members ---
    int x = -1, y = -1; // The chosen move coordinates after algorithm execution
    int cnt = 0;        // Counter for the number of visited states
    std::set<std::string> st; // Set to store visited board states
    int hx[4] = { 0, 1, 0, -1 }, hy[4] = { 1, 0, -1, 0 }; // Directions for checking adjacent cells

    // --- Helper Functions ---
    bool checkNeed(Board& board, int x, int y) {
        // Checks if a cell needs to be explored (has adjacent occupied cells)
        for (int i = 0; i < 4; i++) {
            int nx = x + hx[i], ny = y + hy[i];
            if (!board.isInside(nx, ny)) continue; // Skip if out of bounds
            if (board.getCell(nx, ny) != ' ') return true; // Return true if an adjacent cell is occupied
        }
        return false; // Return false if no adjacent cells are occupied
    }

    int dfs(Board& board, Referee& referee, int depth, char currentSymbol) {
        // Depth-First Search algorithm with Minimax logic
        cnt++; // Increment the state counter
        int judge = referee.evaluateGameState(board); // Evaluate the current board state

        // Debugging (commented out)
        /*for (int i = 0; i < board.getN(); i++) {
            for (int j = 0; j < board.getM(); j++) {
                cout << board.getCell(i, j);
            }
            cout << "\n";
        }
        cout << judge << "\n";*/

        if (judge == 0) return 0; // Draw
        else if (judge == 1) {
            if (depth % 2 == 1) return 1; // Win for the minimizing player
            else return -1; // Win for the maximizing player
        }
        if (depth == 7) return 0; // Maximum search depth reached

        char nextSymbol = (currentSymbol == 'X') ? 'O' : 'X'; // Switch to the next player's symbol
        int point, px, py; // Variables to store the best point and move coordinates

        if (depth % 2 == 0) point = INT_MIN; // Maximizing player
        else point = INT_MAX; // Minimizing player

        for (int i = 0; i < board.getN(); i++)
            for (int j = 0; j < board.getM(); j++) {
                // Debugging (commented out)
                //cout << depth << ": " << i << " " << j << " " << board.getCell(i, j) << "\n";

                if (board.getCell(i, j) != ' ') continue; // Skip if the cell is not empty
                if (!checkNeed(board, i, j)) continue; // Skip if the cell doesn't need to be explored

                board.setCell(i, j, currentSymbol); // Make the move
                std::string state = board.getBoardState(); // Get the board state as a string

                if (!st.count(state)) { // Check if the state has been visited
                    st.insert(state); // Mark the state as visited
                    int returnPoint = dfs(board, referee, depth + 1, nextSymbol); // Recursive call to dfs
                    if (depth % 2 == 0 && point < returnPoint) px = i, py = j, point = returnPoint; // Update max point
                    if (depth % 2 == 1 && point > returnPoint) px = i, py = j, point = returnPoint; // Update min point

                    // Debugging (commented out)
                    //cout << depth << ": " << i << " " << j << " " << depth << " " << point << " " << returnPoint << " " << px << " " << py << "\n";
                }
                board.setCell(i, j, ' '); // Undo the move
            }
        if (depth == 0) x = px, y = py; // Store the best move at the root level

        // Debugging (commented out)
        //cout << "Move: " << point << "\n";

        if (point == INT_MAX || point == INT_MIN) return 0; // Return 0 for terminal nodes
        else return point; // Return the point
    }

    void reset() {
        // Resets the algorithm's state
        cnt = 0;
        st.clear();
        x = -1; y = -1;
    }

public:
    std::pair<int, int> findMove(Board board, Referee& referee, char currentSymbol) {
        // Finds the best move using the dfs algorithm
        reset();
        int point = dfs(board, referee, 0, currentSymbol); // Start the dfs from depth 0

        // Debugging (commented out)
        //cout << "Point: " << point << "\n";
        //cout << "Count: " << cnt << "\n";

        return std::make_pair(x, y); // Return the best move coordinates
    }
};

#endif // !BOTALGORITHM_HPP