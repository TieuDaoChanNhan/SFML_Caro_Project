# Caro Game

Caro is a popular traditional board game where two players alternate marking X and O on the board. The objective is to form a sequence of 5 consecutive symbols horizontally, vertically, or diagonally.

This project is developed using **C++** with graphical rendering provided by the **SFML** library. It supports both Player vs Player (PvP) and Player vs AI game modes.

## Current Versions

- **Version 1.0 (Completed)**:
  - Player vs Player mode.
  - Customizable board size (n x m).
  - Mouse click event handling to place O/X.
  - Victory condition checking (5 consecutive cells).

- **Version 2.0 (Completed)**:
  - Added Player vs AI mode.
  - Implemented the **Minimax** algorithm with a search depth of **10**.
  - Effective AI gameplay on a **3x3** board.

## Technologies Used

- Programming language: **C++**
- Graphics library: **SFML**
- Version control: **Git & GitHub**

## Installation and Execution

### Prerequisites
- **C++** compiler (g++, Clang, or MSVC)
- **SFML** library ([SFML installation guide](https://www.sfml-dev.org/download.php))

### Project Setup

Clone the repository from GitHub:
```bash
git clone https://github.com/TieuDaoChanNhan/SFML_Caro_Project.git
cd SFML_Caro_Project
```

Compile and run the program:
```bash
g++ *.cpp -o CaroGame -lsfml-graphics -lsfml-window -lsfml-system
./CaroGame
```

## Future Development

- Extend AI algorithm for larger board sizes.
- Optimize performance and enhance user experience.
- Additional features such as game timer, undo moves, and main menu.

---

Thank you for your interest in this project! Enjoy playing the game.

