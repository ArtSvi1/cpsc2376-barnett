/*
Used chatgpt to help with the logic of the win conditions. Also used chatgpt if I ran into a bug I couldn't figure out how to fix.
For example in the print board function I was getting an error for trying to cout an enum, asked gpt and made the pieceToChar func
*/
#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <vector>

enum class Piece {
    Empty = ' ',
    Player1 = 'X',
    Player2 = 'O'
};

enum class GameStatus {
    NotStarted,
    InProgress,
    Player1Wins,
    Player2Wins,
    Draw
};

const int ROWS{ 6 }, COLS{ 7 };

bool isNumber(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

int getInt(const std::string& prompt) {
    std::string input;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (isNumber(input)) {
            return std::stoi(input);
        }

        std::cout << "Invalid input. Please enter a valid number.\n";
    }
}

char getChar(const std::string& prompt) {
    char input;

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Invalid input. Please enter a single character.\n";
        }
        else {
            return std::tolower(input);
        }
    }
}

char validTwoChar(const std::string& prompt, char a, char b) {
    char input;

    while (true) {
        input = getChar(prompt);

        if (input == a || input == b) {
            return input;
        }
        else {
            std::cout << "Invalid input. Please enter '"<< a <<"' or '" << b << "'.\n";
        }
    }
}

char pieceToChar(Piece piece) {
    return static_cast<char>(piece);
}

void printRules() {
    std::cout << "\nTo win the game, players must connect four of their pieces diagonally, horizontally, or vertically.\n"
        "Each player will take turns dropping a piece into a column on the board.\n"
        "These pieces will drop the the lowest empty spot within the column. The pieces can stack on top of each other.\n"
        "Player 1 will be dropping pieces with an X. Player 2 will be dropping pieces with an O.\n"
        "Good luck and have fun!\n";
}

void makeBoard(std::vector<std::vector<Piece>>& board) {
    board.resize(ROWS, std::vector<Piece>(COLS, Piece::Empty));
}

void printBoard(const std::vector<std::vector<Piece>>& board) {
    std::cout << std::endl;

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            std::cout << "[" << pieceToChar(board[row][col]) << "]";
        }
        std::cout << std::endl;
    }
    std::cout << " 1  2  3  4  5  6  7" << std::endl;
}

Piece getCurrentPlayer(const std::vector<std::vector<Piece>>& board) {
    int numX{ 0 }, numO{ 0 };

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (board[row][col] == Piece::Player1) {
                numX++;
            }
            else if (board[row][col] == Piece::Player2) {
                numO++;
            }
        }
    }
    Piece player;

    if (numX == 0 || numX == numO) {
        return Piece::Player1;
    }
    else {
        return Piece::Player2;
    }
}

void printTurn(const std::vector<std::vector<Piece>>& board) {
    if (getCurrentPlayer(board) == Piece::Player1) {
        std::cout << "Player 1's turn:\n";
    }
    else {
        std::cout << "Player 2's turn:\n";
    }
}

void play(std::vector<std::vector<Piece>>& board, int column) {
    Piece currentPlayer = getCurrentPlayer(board);
    bool piecePlayed = false;
    column--;

    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][column] == Piece::Empty) {
            board[row][column] = currentPlayer;
            piecePlayed = true;
            break;
        }
    }
    if (piecePlayed) {
        std::cout << "Piece played successfully.\n";
    }
    else {
        std::cout << "Column full. Please select a different column.\n";
    }
    
}

bool checkWin(const std::vector<std::vector<Piece>>& board, Piece player) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col <= COLS - 4; ++col) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return true;
            }
        }
    }
    for (int col = 0; col < COLS; ++col) {
        for (int row = 0; row <= ROWS - 4; ++row) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return true;
            }
        }
    }
    for (int row = 3; row < ROWS; ++row) {
        for (int col = 0; col <= COLS - 4; ++col) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return true;
            }
        }
    }
    for (int row = 0; row <= ROWS - 4; ++row) {
        for (int col = 0; col <= COLS - 4; ++col) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return true;
            }
        }
    }

    return false;
}

bool isBoardFull(const std::vector<std::vector<Piece>>& board) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (board[row][col] == Piece::Empty) {
                return false;
            }
        }
    }
    return true;
}

GameStatus gameStatus(const std::vector<std::vector<Piece>>& board) {
    if (checkWin(board, Piece::Player1)) {
        return GameStatus::Player1Wins;
    }
    else if (checkWin(board, Piece::Player2)) {
        return GameStatus::Player2Wins;
    }
    else if (isBoardFull(board)) {
        return GameStatus::Draw;
    }
    else {
        return GameStatus::InProgress;
    }
}

bool printStatus(const std::vector<std::vector<Piece>>& board) {
    if (gameStatus(board) == GameStatus::Player1Wins) {
        std::cout << "Player 1 wins!\n";
        return true;
    }
    else if (gameStatus(board) == GameStatus::Player2Wins) {
        std::cout << "Player 2 wins!\n";
        return true;
    }
    else if (gameStatus(board) == GameStatus::Draw) {
        std::cout << "The game was a draw!\n";
        return true;
    }
    else {
        std::cout << "Game is still ongoing.\n";
        return false;
    }
}

int main() {
    std::vector<std::vector<Piece>> board;
    GameStatus status = GameStatus::NotStarted;

    std::cout << "Welcome to Connect Four! Below are the rules for playing this game!\n";
    printRules();

    while (true) {
        if (status == GameStatus::NotStarted) {
            std::cout << "\nGame Options:\n"
                "1. Start Game\n"
                "2. Exit\n";

            int choice = getInt("Enter choice: ");

            if (choice == 1) {
                std::cout << "Starting game...\n";
                makeBoard(board);
                status = GameStatus::InProgress;
                std::cout << "Game started successfully!\n";
            }
            else if (choice == 2) {
                std::cout << "Exiting game...\n";
                break;
            }
            else {
                std::cout << "Invalid choice. Please type 1 or 2.\n";
            }
        }
        else if (status == GameStatus::InProgress) {
            printBoard(board);

            std::cout << "\n1. Play Turn\n"
                "2. Check Game Status\n"
                "3. Print Rules\n"
                "4. End Game\n";

            int choice = getInt("Enter choice: ");

            if (choice == 1) {
                printTurn(board);
                while (true) {
                    int col = getInt("Column: ");
                    if (col > 0 && col <= COLS) {
                        play(board, col);
                        break;
                    }
                    else {
                        std::cout << "Invalid column number. Enter a number 1-7\n";
                    }
                }
                if (printStatus(board)) {
                    printBoard(board);
                    status = GameStatus::NotStarted;
                    board.clear();
                }
            }
            else if (choice == 2) {
                if (printStatus(board)) {
                    status = GameStatus::NotStarted;
                    board.clear();
                }
            }
            else if (choice == 3) {
                printRules();
            }
            else if (choice == 4) {
                char y{ 'y' }, n{ 'n' };
                char confirmExit = validTwoChar("Are you sure you want to end the current game? (y/n): ", y, n);

                if (confirmExit == 'y') {
                    std::cout << "Ending the game...\n";
                    status = GameStatus::NotStarted;
                    board.clear();
                }
                else {
                    std::cout << "Game continues...\n";
                }

            }
        }
        else {
            std::cout << "Internal error: Unknown Game Status. Exiting program...";
            return 1;
        }
    }
    return 0;
}
