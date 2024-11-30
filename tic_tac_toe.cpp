#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void printBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << board[i] << " ";
        if ((i + 1) % 3 == 0)
            cout << "\n";
        else
            cout << "|";
    }
    cout << "\n";
}

int checkWinner(const vector<char>& board) {
    // Check rows, columns, and diagonals
    int winConditions[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
                                {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
                                {0, 4, 8}, {2, 4, 6}}; // diagonals

    for (auto& condition : winConditions) {
        if (board[condition[0]] == board[condition[1]] && board[condition[1]] == board[condition[2]] && board[condition[0]] != ' ')
            return board[condition[0]] == 'X' ? 1 : -1; // 1 for Player X wins, -1 for Player O wins
    }
    return 0; // No winner
}

bool isBoardFull(const vector<char>& board) {
    for (char cell : board) {
        if (cell == ' ') return false;
    }
    return true;
}

int minMax(vector<char>& board, int depth, bool isMaximizingPlayer) {
    int winner = checkWinner(board);
    if (winner == 1) return -1+depth;  // Player X wins
    if (winner == -1) return 1-depth;  // Player O wins
    if (isBoardFull(board)) return 0;  // Draw

    if (isMaximizingPlayer) {
        int best = -INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';  // Computer's move
                best = max(best, minMax(board, depth + 1, false));
                board[i] = ' ';  // Undo move
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';  // Player's move
                best = min(best, minMax(board, depth + 1, true));
                board[i] = ' ';  // Undo move
            }
        }
        return best;
    }
}

int findBestMove(vector<char>& board) {
    int bestVal = -INT_MAX;
    int bestMove = -1;

    // Try all possible moves and find the best one
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';  // Computer's move
            int moveVal = minMax(board, 0, false);
            board[i] = ' ';  // Undo move

            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

void playerMove(vector<char>& board, char player) {
    int move;
    do {
        cout << "Player " << player << ", enter your move (1-9): ";
        cin >> move;
        move--;  // Convert to 0-indexed
    } while (move < 0 || move >= 9 || board[move] != ' ');
    board[move] = player;
}

void playGame() {
    vector<char> board(9, ' ');
    printBoard(board);

    while (true) {
        // Player's move (X)
        playerMove(board, 'X');
        printBoard(board);

        int winner = checkWinner(board);
        if (winner == 1) {
            cout << "Player X wins!\n";
            break;
        }
        if (isBoardFull(board)) {
            cout << "It's a draw!\n";
            break;
        }

        // Computer's move (O)
        cout << "Computer's move (O):\n";
        int bestMove = findBestMove(board);
        board[bestMove] = 'O';
        printBoard(board);

        winner = checkWinner(board);
        if (winner == -1) {
            cout << "Computer wins!\n";
            break;
        }
        if (isBoardFull(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    playGame();
    return 0;
}
