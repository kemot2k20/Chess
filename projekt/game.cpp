#include <bits/stdc++.h>
#include "game.h"
#include "player.h"
#include "ui.h"
#include "ncurses.h"
#include "chess-library-master/include/chess.hpp"

using namespace chess;
using namespace std;

Game::Game(GameMode gameMode) {
    gameHelper = GameHelper();
    board = gameHelper.initialBoard();
    turn = 0;
    
    string p0="p0", p1="p1"; // Deklaracja zmiennych przed switch

    switch (gameMode) {
        case HUMAN_VS_HUMAN:
            cout << "Write 1st player's name : \n";
            cin >> p0;
            cout << "Write 2nd player's name : \n";
            cin >> p1;

            players.push_back(Player(p0, false, Color::WHITE));
            players.push_back(Player(p1, false, Color::BLACK));
            break;
            
        case HUMAN_VS_AI:
            cout << "Write your name : \n";
            cin >> p0;
            cout << "Set bot difficulty from 1 to 5 (1 is the easiest, 5 the hardest) : \n";

            int botDifficulty;
            while (true) {
                cin >> botDifficulty;
                if (botDifficulty > 5 || botDifficulty < 1) {
                    cout << "Given difficulty is not correct! Try again: ";
                } else {
                    break;
                }
            }

            string playerColor;
            while (true) {
                cout << "Choose your color, write 'white' or 'black':\n";
                cin >> playerColor;

                if (playerColor == "white") {
                    players.push_back(Player(p0, false, Color::WHITE));
                    players.push_back(Player("", true, Color::BLACK)); // Gracz 2 jako AI
                    ai = AI(Color::BLACK, botDifficulty);
                    break;
                } else if (playerColor == "black") {
                    players.push_back(Player("", true, Color::WHITE)); // Gracz 1 jako AI
                    players.push_back(Player(p0, false, Color::BLACK));
                    ai = AI(Color::WHITE, botDifficulty);
                    break;
                }

                cout << "This color doesn't exist, write 'white' or 'black' to choose.\n";
            }
            break;
    }
}

bool Game::gameOver() {
    return gameHelper.isGameOver(board);
}

void Game::makeMove(string uciMove) {
    Move move = uci::uciToMove(board, uciMove);
    board.makeMove(move);
    turn ++;
}

void Game::gameLoop() {
    UI ui;
    while (true) {
        ui.displayBoard(board.getFen());
        if (gameOver()) {
            ui.over("Game Over! Thank you for playing.");
            endwin();
            break;
        }
        int p = turn % 2; // 0 -> white's, 1 -> black's move
        if (players[p].isAI) {
            string AImove = ai.getMove(board);
            makeMove(AImove);
        } else {
            string uciMove; 
            while (true) {
                uciMove = ui.getUserMove(players[p].name);
                if (uciMove == "quit") {
                    ui.quitGame();
                    endwin();
                    return;
                }
                if (!gameHelper.isMoveLegal(board, uciMove)) {
                    ui.illegalMove();
                    ui.displayBoard(board.getFen());
                } else {
                    makeMove(uciMove);
                    break;
                }
            }
        }
    }
}

void Game::startGame() {
    gameLoop();
}
