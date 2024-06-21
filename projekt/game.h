#ifndef GAME_H
#define GAME_H

#include <bits/stdc++.h>
#include "player.h"
#include "gameHelper.h"
#include "chessAI.h"
#include "chess-library-master/include/chess.hpp"

using namespace std;
using namespace chess;

enum GameMode
{
    HUMAN_VS_HUMAN,
    HUMAN_VS_AI
};

class Game {
private:
    GameHelper gameHelper;
    vector<Player> players;
    AI ai;
    Board board;
    int turn;
    bool gameOver();
    void makeMove(string uciMove);
    void gameLoop();
public:
    Game(GameMode gameMode = HUMAN_VS_AI);
    void startGame();
};

#endif
