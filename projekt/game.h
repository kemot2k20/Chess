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
    void startGame(); // displays starting position using gameGUI
    void endGame(); // ends current game and waiting for input
public:
    GameHelper gameHelper;
    vector<Player> players;
    AI ai;
    Board board;
    int turn;
    bool gameOver();
    void makeMove(string uciMove);
    Game(GameMode gameMode = HUMAN_VS_AI);
};

#endif