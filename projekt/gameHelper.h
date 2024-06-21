#ifndef CHESS_HELPER_H
#define CHESS_HELPER_H

#include <bits/stdc++.h>
#include "chess-library-master/include/chess.hpp"

using namespace chess;
using namespace std;

struct GameHelper {
    bool isGameOver(Board board);
    bool isCheckMate(Board board);
    bool isStaleMate(Board board);
    bool isMoveLegal(Board board, string uciMove);
    Board initialBoard();
    Color opposite(Color color);
    Movelist getMoves(Board board);
};

#endif