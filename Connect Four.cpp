#include <iostream>
#include <vector>

using namespace std;

// Class to represent the board of the Connect Four game
class Board {
private:
    int rows, cols;
    vector<vector<char>> grid;  // 2D vector representing the grid

public:
    Board(int r = 6, int c = 7) : rows(r), cols(c), grid(r, vector<char>(c, '.')) {}

    // Print the current board state
    void displayBoard() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Check if a column is full
    bool isColumnFull(int col) {
        return grid[0][col] != '.';
    }

    // Drop a piece into the board
    bool dropPiece(int col, char piece) {
        if (isColumnFull(col)) {
            return false;
        }
        for (int i = rows - 1; i >= 0; i--) {
            if (grid[i][col] == '.') {
                grid[i][col] = piece;
                return true;
            }
        }
        return false;
    }

    // Check if there is a winning condition
    bool checkWin(char piece) {
        // Check horizontal, vertical, and diagonal win conditions
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (checkDirection(i, j, 1, 0, piece) ||  // Horizontal
                    checkDirection(i, j, 0, 1, piece) ||  // Vertical
                    checkDirection(i, j, 1, 1, piece) ||  // Diagonal Down-right
                    checkDirection(i, j, 1, -1, piece)) { // Diagonal Down-left
                    return true;
                }
            }
        }
        return false;
    }

private:
    // Helper function to check four consecutive pieces in any direction
    bool checkDirection(int row, int col, int rowDir, int colDir, char piece) {
        int count = 0;
        for (int i = 0; i < 4; i++) {
            int r = row + i * rowDir;
            int c = col + i * colDir;
            if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == piece) {
                count++;
            } else {
                break;
            }
        }
        return count == 4;
    }
};

// Class representing a player
class Player {
private:
    string name;
    char piece;

public:
    Player(string n, char p) : name(n), piece(p) {}

    string getName() const {
        return name;
    }

    char getPiece() const {
        return piece;
    }
};

// Class to manage the game logic
class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:
    Game(string p1Name, char p1Piece, string p2Name, char p2Piece)
        : player1(p1Name, p1Piece), player2(p2Name, p2Piece), currentPlayer(&player1) {}

    void start() {
        int moves = 0;
        while (true) {
            board.displayBoard();
            int col;
            cout << currentPlayer->getName() << "'s turn (Piece: " << currentPlayer->getPiece() << "). Choose a column (0-6): ";
            cin >> col;

            if (col < 0 || col >= 7 || board.isColumnFull(col)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            board.dropPiece(col, currentPlayer->getPiece());
            moves++;

            if (board.checkWin(currentPlayer->getPiece())) {
                board.displayBoard();
                cout << currentPlayer->getName() << " wins the game!\n";
                break;
            }

            if (moves == 42) {
                board.displayBoard();
                cout << "It's a draw!\n";
                break;
            }

            switchPlayer();
        }
    }

private:
    void switchPlayer() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }
};

// Main function
int main() {
    cout << "Welcome to Connect Four!\n";
    string p1Name, p2Name;
    cout << "Enter Player 1 name: ";
    cin >> p1Name;
    cout << "Enter Player 2 name: ";
    cin >> p2Name;

    Game game(p1Name, 'X', p2Name, 'O');
    game.start();

    return 0;
}
