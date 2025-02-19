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

void gameStatus() {

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
                int col = getInt("Column: ");
                play(board, col);
            }
            else if (choice == 2) {
                
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
