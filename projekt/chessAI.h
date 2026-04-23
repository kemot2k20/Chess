#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <vector>
#include <string>
#include <unordered_map>
#include "chess-library-master/include/chess.hpp"

using U64 = std::uint64_t;

class AI {
private:
    chess::Color ME;
    chess::Color OPP;
    int botDifficulty;
    std::unordered_map<U64, int> cnt, mapka;
    std::unordered_map<U64, std::vector<std::pair<unsigned short, std::string>>> openingBook;

    int mg_table[12][64];
    int eg_table[12][64];
    
    void init_tables();

    int utility(chess::Board board, chess::Color turn);
    int getDepth();
    std::pair<int, std::string> minimax(chess::Board board, int alpha, int beta, chess::Color to_play, int depth);
    std::string decodePolyGlotMove(unsigned short polyMove);
    void loadOpeningBook(std::string filename);
    std::string getMoveFromOpeningBook(chess::Board board);

public:
    AI(chess::Color ME = chess::Color::BLACK, int botDifficulty = 1);
    std::string getMove(chess::Board board);
};

#endif
