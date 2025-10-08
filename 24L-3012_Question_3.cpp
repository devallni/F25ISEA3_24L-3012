#include <iostream>
#include <string>

using namespace std;

const int SIZE = 3;

/**
 * @brief Prints the current Tic-tac-toe grid.
 *
 * @param board A 2D array representing the current state of the board.
 */
void displayBoard(char board[SIZE][SIZE]) {
    cout << "\nCurrent Board:\n";
    cout << "-------------\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << "| ";
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

/**
 * @brief Checks if the given move is valid.
 *
 * @param board The current game board.
 * @param row The row index of the move.
 * @param col The column index of the move.
 * @return true if the cell is within bounds and empty; false otherwise.
 */
bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ';
}

/**
 * @brief Checks if a player has won the game.
 *
 * @param board The current game board.
 * @param player The player's symbol ('X' or 'O').
 * @return true if the player has three in a row (any direction).
 */
bool checkWin(char board[SIZE][SIZE], char player) {
    // Rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }

    // Diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;

    return false;
}

/**
 * @brief Checks if the board is completely filled.
 *
 * @param board The current game board.
 * @return true if all cells are filled, false otherwise.
 */
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ')
                return false;
    return true;
}

/**
 * @brief Main game loop for two-player Tic-tac-toe.
 *
 * Allows two players to take turns placing 'X' and 'O' on a 3x3 grid.
 * Displays the board after each move and announces the winner or a draw.
 *
 * @return int Exit status (0 for normal termination).
 */
int main() {
    char board[SIZE][SIZE];

    // Initialize empty board
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';

    char currentPlayer = 'X';
    bool gameOver = false;
    
    cout << "        TIC-TAC-TOE GAME         \n";
    cout << "Player 1: X     Player 2: O\n\n";

    displayBoard(board);

    while (!gameOver) {
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column: 1-3 each): ";
        cin >> row >> col;

        row--;
        col--;

        if (!isValidMove(board, row, col)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins the game!\n";
            gameOver = true;
        }
        else if (isBoardFull(board)) {
            cout << "Game drawn!\n";
            gameOver = true;
        }
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    return 0;
}
