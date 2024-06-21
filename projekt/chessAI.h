#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <bits/stdc++.h>
#include "chess-library-master/include/chess.hpp"

using namespace chess;
using namespace std;
using U64 = std::uint64_t;

class AI {
    Color ME;
    Color OPP;
    int botDifficulty;
    unordered_map<U64, int> cnt, mapka;
    unordered_map<U64, vector<pair<unsigned short, string>>> openingBook;

    int utility(Board board, Color turn);
    int getDepth();
    pair<int, string> minimax(Board board, int alpha, int beta, Color to_play, int depth);
    string decodePolyGlotMove(unsigned short polyMove);
    void loadOpeningBook(string filename);
    string getMoveFromOpeningBook(Board board);
public:
    AI(Color ME = Color::BLACK, int botDifficulty = 1);
    string getMove(Board board);
};

#endif