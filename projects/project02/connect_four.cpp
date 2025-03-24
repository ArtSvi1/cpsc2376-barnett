#include "connect_four.h"

ConnectFour::ConnectFour() : board(ROWS, std::vector<Piece>(COLS, Piece::Empty)), status(GameStatus::NotStarted) {
}

ConnectFour::GameStatus ConnectFour::getStatus() const {
    return this->status;
}

bool ConnectFour::printStatus() {
    if (status == GameStatus::Player1Wins) {
        std::cout << "Player 1 wins!\n";
        return true;
    }
    else if (status == GameStatus::Player2Wins) {
        std::cout << "Player 2 wins!\n";
        return true;
    }
    else if (status == GameStatus::Draw) {
        std::cout << "The game was a draw!\n";
        return true;
    }
    else {
        std::cout << "Game is still ongoing.\n";
        return false;
    }
}

char ConnectFour::pieceToChar(Piece piece) const{
    return static_cast<char>(piece);
}

void ConnectFour::display() const {
    std::cout << std::endl;

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            std::cout << "[" << pieceToChar(board[row][col]) << "]";
        }
        std::cout << std::endl;
    }

    std::cout << " 1  2  3  4  5  6  7" << std::endl;
}

ConnectFour::Piece ConnectFour::getCurrentPlayer() {
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

    if (numX == 0 || numX == numO) {
        return Piece::Player1;
    }
    else {
        return Piece::Player2;
    }
}

void ConnectFour::printTurn() {
    if (getCurrentPlayer() == Piece::Player1) {
        std::cout << "Player 1's turn:\n";
    }
    else {
        std::cout << "Player 2's turn:\n";
    }
}

void ConnectFour::play(int column) {
    Piece currentPlayer = getCurrentPlayer();
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

bool ConnectFour::checkWin(Piece player) {
    // Horizontal win con logic
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

    // Vertical win con logic
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

    // Bottom Left to Top Right win con logic
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

    // Top Left to Bottom Right win con logic
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
    
    // No win con found
    return false;
}

bool ConnectFour::isBoardFull() const {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (board[row][col] == Piece::Empty) {
                return false;
            }
        }
    }
    return true;
}