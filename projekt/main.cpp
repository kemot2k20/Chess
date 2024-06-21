#include <bits/stdc++.h>
#include "game.h"
#include "ui.h"
#include "gameHelper.h"
#include "ncurses.h"

using namespace std;

int main() {
    UI ui;
    Game game(HUMAN_VS_HUMAN);
    GameHelper gamehelper;
    while (true) {
        ui.displayBoard(game.board.getFen());
        if (game.gameOver()) {
            ui.over("Game Over! Thank you for playing.");
            endwin();
            break;
        }
        int p = game.turn % 2; // 0 -> white's, 1 -> black's move
        if (game.players[p].isAI) {
            string AImove = game.ai.getMove(game.board);
            //cout << "AI played : " << AImove << '\n' << '\n';
            game.makeMove(AImove);
        } else {
            string uciMove; 
            while (true) {
                uciMove = ui.getUserMove(game.players[p].name);
                if (uciMove == "quit") {
                    ui.quitGame();
                    endwin();
                    return 0;
                }
                if (!gamehelper.isMoveLegal(game.board, uciMove)) {
                    ui.illegalMove();
                    ui.displayBoard(game.board.getFen());
                    //cout << "Illegal move!\n";
                } else {
                    game.makeMove(uciMove);
                    break;
                }
            }
        }
    }
    return 0;
}