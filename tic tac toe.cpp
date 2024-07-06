#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to find the index of the maximum element
int maxElementIndex(const vector<int>& vec) {
    int maxIndex = 0;
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] > vec[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Function to find the index of the minimum element
int minElementIndex(const vector<int>& vec) {
    int minIndex = 0;
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

// Abstract base class for a player
class Player {
public:
    char symbol;
    virtual void makeMove(vector<char>& board) = 0;
};

// Human player class
class HumanPlayer : public Player {
public:
    HumanPlayer(char symbol) { this->symbol = symbol; }
    
    void makeMove(vector<char>& board) {
        int move;
        cout << "Enter your move (1-9): ";
        cin >> move;
        while (move < 1 || move > 9 || board[move - 1] != ' ') {
            cout << "Invalid move. Try again: ";
            cin >> move;
        }
        board[move - 1] = symbol;
    }
};

// AI player class
class AIPlayer : public Player {
public:
    int difficulty;
    
    AIPlayer(char symbol, int difficulty) {
        this->symbol = symbol;
        this->difficulty = difficulty;
    }
    
    void makeMove(vector<char>& board) {
        int move;
        if (difficulty == 1) {
            // Easy: Random move
            do {
                move = rand() % 9;
            } while (board[move] != ' ');
        } else if (difficulty == 2) {
            // Medium: Random move with a chance to block
            move = findBestMove(board);
        } else {
            // Hard: Best move using minimax
            move = minimax(board, symbol).first;
        }
        board[move] = symbol;
    }

private:
    int findBestMove(const vector<char>& board) {
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                return i;
            }
        }
        return rand() % 9;
    }

    pair<int, int> minimax(vector<char> board, char currentPlayer) {
        // Check for terminal state
        if (checkWin(board, 'X')) return make_pair(-1, 10);
        if (checkWin(board, 'O')) return make_pair(-1, -10);
        if (isBoardFull(board)) return make_pair(-1, 0);

        vector<int> moves;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                moves.push_back(i);
            }
        }

        vector<int> scores;
        for (int i = 0; i < moves.size(); ++i) {
            int move = moves[i];
            board[move] = currentPlayer;
            int score = minimax(board, currentPlayer == 'X' ? 'O' : 'X').second;
            scores.push_back(score);
            board[move] = ' ';
        }

        int bestMove = 0;
        if (currentPlayer == 'X') {
            bestMove = maxElementIndex(scores);
        } else {
            bestMove = minElementIndex(scores);
        }

        return make_pair(moves[bestMove], scores[bestMove]);
    }

    bool checkWin(const vector<char>& board, char player) {
        const int winConditions[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (int i = 0; i < 8; ++i) {
            if (board[winConditions[i][0]] == player && board[winConditions[i][1]] == player && board[winConditions[i][2]] == player) {
                return true;
            }
        }
        return false;
    }

    bool isBoardFull(const vector<char>& board) {
        for (int i = 0; i < board.size(); ++i) {
            if (board[i] == ' ') {
                return false;
            }
        }
        return true;
    }
};

// Game class to manage the game state
class Game {
private:
    vector<char> board;
    Player* player1;
    Player* player2;
    
public:
    Game(Player* p1, Player* p2) : player1(p1), player2(p2) {
        board = vector<char>(9, ' ');
    }
    
    void displayBoard() {
        cout << "Current board:" << endl;
        for (int i = 0; i < 9; ++i) {
            cout << board[i] << (i % 3 == 2 ? '\n' : '|');
            if (i % 3 == 2 && i != 8) cout << "-----\n";
        }
    }

    void play() {
        Player* currentPlayer = player1;
        while (true) {
            displayBoard();
            currentPlayer->makeMove(board);
            if (checkWin(currentPlayer->symbol)) {
                displayBoard();
                cout << currentPlayer->symbol << " wins!" << endl;
                break;
            }
            if (isBoardFull()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }
    }

private:
    bool checkWin(char player) {
        const int winConditions[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (int i = 0; i < 8; ++i) {
            if (board[winConditions[i][0]] == player && board[winConditions[i][1]] == player && board[winConditions[i][2]] == player) {
                return true;
            }
        }
        return false;
    }

    bool isBoardFull() {
        for (int i = 0; i < board.size(); ++i) {
            if (board[i] == ' ') {
                return false;
            }
        }
        return true;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    char playAgain;

    do {
        cout << "Welcome to Tic-Tac-Toe!" << endl;
        cout << "Choose difficulty level:" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        while (choice < 1 || choice > 3) {
            cout << "Invalid choice. Try again: ";
            cin >> choice;
        }

        HumanPlayer human('X');
        AIPlayer ai('O', choice);
        Game game(&human, &ai);
        game.play();

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing Tic-Tac-Toe. Goodbye!" << endl;

    return 0;
}

