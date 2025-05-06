/*
I used chatgpt to help me to create some of the extra effects I wanted to make my text blink on and off for
starting the game and flashing back and forth between the winner text and the option to restart.
I also used to to help change the shapes of the slots on the game board to be circles as well as to get the colors
I wanted to be used for the pieces and board.
Also used chat gpt to help when I was struggling with getting the column numbers and rows to be cenetered to each column
and row, then to get the game score on the top right positioned the way I wanted it to be.
*/
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "connect_four.h"

const int CELL_SIZE = 80;
const int BOARD_COLS = 7;
const int BOARD_ROWS = 6;
const int WINDOW_PADDING = 80;
const int BOARD_WIDTH = BOARD_COLS * CELL_SIZE;
const int BOARD_HEIGHT = BOARD_ROWS * CELL_SIZE;
const int SCREEN_WIDTH = BOARD_WIDTH + WINDOW_PADDING * 2 + 80;
const int SCREEN_HEIGHT = BOARD_HEIGHT + WINDOW_PADDING * 2;

Uint32 blinkStartTime = 0;
bool showBlinkText = true;

Uint32 endBlinkStartTime = SDL_GetTicks();
bool showEndMessage = true;

int player1Score = 0;
int player2Score = 0;

enum class TextAlign { Center, Right, Left };

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if (TTF_Init() < 0) return false;

    window = SDL_CreateWindow("Connect Four",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer != nullptr;
}

void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY,
    int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

void drawText(SDL_Renderer* renderer, TTF_Font* font,
    const std::string& text, int x, int y,
    SDL_Color color,
    TextAlign align = TextAlign::Center) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    SDL_Rect dst;
    if (align == TextAlign::Center) {
        dst = { x - w / 2, y - h / 2, w, h };
    }
    else if (align == TextAlign::Right) {
        dst = { x - w, y - h / 2, w, h };
    }
    else {
        dst = { x, y - h / 2, w, h };
    }

    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawScores(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color white = { 255, 255, 255 };

    // Align with row number spacing (approx. 30px from right edge)
    int anchorX = SCREEN_WIDTH - WINDOW_PADDING + 30;
    int y1 = WINDOW_PADDING / 2 - 10;
    int y2 = y1 + 20;

    auto formatScore = [](const std::string& label, int score) {
        std::string dots = "....";
        std::string digits = std::to_string(score);
        int replaceCount = std::min((int)dots.length(), (int)digits.length());
        std::string prefix = dots.substr(0, dots.length() - replaceCount);
        return label + ":" + prefix + digits;
        };

    std::string p1Text = formatScore("P1", player1Score);
    std::string p2Text = formatScore("P2", player2Score);

    drawText(renderer, font, p1Text, anchorX, y1, white, TextAlign::Right);
    drawText(renderer, font, p2Text, anchorX, y2, white, TextAlign::Right);
}

int getSafeColumnFromMouse(int x) {
    const int padding = 10;
    x -= WINDOW_PADDING;
    if (x < 0) return -1;
    int col = x / CELL_SIZE;
    int offset = x % CELL_SIZE;
    if (offset < padding || offset >(CELL_SIZE - padding)) return -1;
    return col;
}

void drawBoard(SDL_Renderer* renderer, const ConnectFour& game,
    TTF_Font* font, TTF_Font* labelFont) {
    SDL_Color white = { 255, 255, 255 };
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            int x = col * CELL_SIZE + WINDOW_PADDING;
            int y = row * CELL_SIZE + WINDOW_PADDING;
            SDL_Rect cell = { x, y, CELL_SIZE, CELL_SIZE };
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &cell);

            ConnectFour::Piece piece = game.getPieceAt(row, col);
            switch (piece) {
            case ConnectFour::Piece::Player1:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
            case ConnectFour::Piece::Player2:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break;
            case ConnectFour::Piece::Empty:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); break;
            }

            int centerX = x + CELL_SIZE / 2;
            int centerY = y + CELL_SIZE / 2;
            drawFilledCircle(renderer, centerX, centerY, 30);
        }
    }

    for (int col = 0; col < BOARD_COLS; ++col) {
        int centerX = col * CELL_SIZE + WINDOW_PADDING + CELL_SIZE / 2;
        int y = WINDOW_PADDING + BOARD_HEIGHT + 25;
        drawText(renderer, labelFont, std::to_string(col + 1),
            centerX, y, white);
    }

    for (int row = 0; row < BOARD_ROWS; ++row) {
        int centerY = row * CELL_SIZE + WINDOW_PADDING + CELL_SIZE / 2;
        int x = WINDOW_PADDING - 30;
        drawText(renderer, labelFont, std::to_string(row + 1),
            x, centerY, white);
    }
}

void drawTopMessage(SDL_Renderer* renderer, TTF_Font* font,
    const ConnectFour& game) {
    SDL_Color white = { 255, 255, 255 };
    std::string msg;

    switch (game.getStatus()) {
    case ConnectFour::GameStatus::NotStarted:
        if (!showBlinkText) return;
        msg = "Press SPACE to begin";
        break;
    case ConnectFour::GameStatus::InProgress:
        msg = (game.getCurrentPlayer() == ConnectFour::Piece::Player1)
            ? "Player 1's turn" : "Player 2's turn";
        break;
    case ConnectFour::GameStatus::Player1Wins:
        msg = showEndMessage
            ? "Player 1 wins!" : "Press SPACE to restart";
        break;
    case ConnectFour::GameStatus::Player2Wins:
        msg = showEndMessage
            ? "Player 2 wins!" : "Press SPACE to restart";
        break;
    case ConnectFour::GameStatus::Draw:
        msg = showEndMessage
            ? "It's a draw!" : "Press SPACE to restart";
        break;
    }

    int centerX = SCREEN_WIDTH / 2;
    int y = WINDOW_PADDING / 2;
    drawText(renderer, font, msg, centerX, y, white);
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!initSDL(window, renderer)) return 1;

    TTF_Font* font = TTF_OpenFont("PublicPixel.ttf", 16);
    TTF_Font* labelFont = TTF_OpenFont("PublicPixel.ttf", 12);
    if (!font || !labelFont) return 1;

    ConnectFour game;
    std::cout << "Press SPACE to begin game.\n";

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_SPACE) {
                ConnectFour::GameStatus status = game.getStatus();
                if (status == ConnectFour::GameStatus::NotStarted ||
                    status == ConnectFour::GameStatus::Player1Wins ||
                    status == ConnectFour::GameStatus::Player2Wins ||
                    status == ConnectFour::GameStatus::Draw) {

                    game.resetBoard();
                    game.setStatus("start");
                    std::cout << "New game started! Click to place pieces.\n\n";
                    game.printTurn();

                    blinkStartTime = SDL_GetTicks();
                    endBlinkStartTime = SDL_GetTicks();
                    showBlinkText = true;
                    showEndMessage = true;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN &&
                game.getStatus() == ConnectFour::GameStatus::InProgress) {
                int col = getSafeColumnFromMouse(event.button.x);
                if (col == -1 || col >= BOARD_COLS) {
                    std::cout << "Click too close to column edge. "
                        << "No piece played.\n";
                    continue;
                }

                ConnectFour::Piece currentPlayer = game.getCurrentPlayer();
                game.play(col + 1);

                std::cout << ((currentPlayer == ConnectFour::Piece::Player1)
                    ? "Player 1" : "Player 2")
                    << " dropped a piece in column "
                    << (col + 1) << ".\n";

                game.checkStatus();
                ConnectFour::GameStatus result = game.getStatus();
                if (result == ConnectFour::GameStatus::Player1Wins)
                    player1Score++;
                if (result == ConnectFour::GameStatus::Player2Wins)
                    player2Score++;

                if (result == ConnectFour::GameStatus::InProgress) {
                    std::cout << std::endl;
                    game.printTurn();
                }
                else {
                    std::cout << std::endl;
                    game.printStatus();
                    std::cout << std::endl;
                    std::cout << "Game Over. Press SPACE to play again.\n";

                    endBlinkStartTime = SDL_GetTicks();
                    showEndMessage = true;
                }
            }
        }

        if (game.getStatus() == ConnectFour::GameStatus::NotStarted) {
            Uint32 currentTime = SDL_GetTicks();
            Uint32 elapsed = currentTime - blinkStartTime;

            if (showBlinkText && elapsed >= 1000) {
                showBlinkText = false;
                blinkStartTime = currentTime;
            }
            else if (!showBlinkText && elapsed >= 500) {
                showBlinkText = true;
                blinkStartTime = currentTime;
            }
        }

        if (game.getStatus() == ConnectFour::GameStatus::Player1Wins ||
            game.getStatus() == ConnectFour::GameStatus::Player2Wins ||
            game.getStatus() == ConnectFour::GameStatus::Draw) {

            Uint32 currentTime = SDL_GetTicks();
            Uint32 elapsed = currentTime - endBlinkStartTime;

            if (elapsed >= 1500) {
                showEndMessage = !showEndMessage;
                endBlinkStartTime = currentTime;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawTopMessage(renderer, font, game);
        drawBoard(renderer, game, font, labelFont);
        drawScores(renderer, labelFont);
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_CloseFont(labelFont);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
