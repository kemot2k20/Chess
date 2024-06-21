#include <bits/stdc++.h>
#include "chess-library-master/include/chess.hpp"
#include "gameHelper.h"

using namespace std;
using namespace chess;

bool GameHelper::isGameOver(Board board) {
    Movelist moves;
    movegen::legalmoves(moves, board);
    return moves.empty();
}

bool GameHelper::isCheckMate(Board board) {
    Movelist moves;
    movegen::legalmoves(moves, board);
    if (moves.empty() && board.inCheck()) return true;
    return false;
}

bool GameHelper::isStaleMate(Board board) {
    Movelist moves;
    movegen::legalmoves(moves, board);
    if (moves.empty() && !board.inCheck()) return true;
    return false;
}

bool GameHelper::isMoveLegal(Board board, string uciMove) {
    Movelist moves;
    movegen::legalmoves(moves, board);
    for (auto m : moves) {
        if (uci::moveToUci(m) == uciMove) return true;
    }
    return false;
}

Board GameHelper::initialBoard() {
    return Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Color GameHelper::opposite(Color color) {
    return color == Color::WHITE ? Color::BLACK : Color::WHITE;
}

Movelist GameHelper::getMoves(Board board) {
    Movelist moves;
    movegen::legalmoves(moves, board);
    return moves;
}