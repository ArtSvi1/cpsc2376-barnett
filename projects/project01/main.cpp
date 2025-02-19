#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <vector>

const int ROWS{ 6 }, COLS{ 7 };

enum class GameStatus {
    NotStarted,
    InProgress,
    Player1Wins,
    Player2Wins,
    Draw
};

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

void printRules() {
    std::cout << "\nTo win the game, players must connect four of their pieces diagonally, horizontally, or vertically.\n"
        "Each player will take turns dropping a piece into a column on the board.\n"
        "These pieces will drop the the lowest empty spot within the column. The pieces can stack on top of each other.\n"
        "Player 1 will be dropping pieces with an X. Player 2 will be dropping pieces with an O.\n"
        "Good luck and have fun!\n";
}

void makeBoard() {
    
}

void printBoard() {

}

void play() {

}

void gameStatus() {

}

int main() {
    std::vector<std::vector<char>> board;
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
            makeBoard();
            printBoard();

            std::cout << "\n1. Play Turn\n"
                "2. Check Game Status\n"
                "3. Print Rules\n"
                "4. End Game\n";

            int choice = getInt("Enter choice: ");

            if (choice == 1) {

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
