#include <bits/stdc++.h>
#include "chessAI.h"
#include "gameHelper.h"
#include "chess-library-master/include/chess.hpp"

using namespace chess;
using U64 = std::uint64_t;
using namespace chess;

const int Mirror64Board[64] = {
    56	,	57	,	58	,	59	,	60	,	61	,	62	,	63	,
    48	,	49	,	50	,	51	,	52	,	53	,	54	,	55	,
    40	,	41	,	42	,	43	,	44	,	45	,	46	,	47	,
    32	,	33	,	34	,	35	,	36	,	37	,	38	,	39	,
    24	,	25	,	26	,	27	,	28	,	29	,	30	,	31	,
    16	,	17	,	18	,	19	,	20	,	21	,	22	,	23	,
    8	,	9	,	10	,	11	,	12	,	13	,	14	,	15	,
    0	,	1	,	2	,	3	,	4	,	5	,	6	,	7
};

const int INF = 1'000'000'000;

const int mg_value[6] = { 82, 337, 365, 477, 1025,  0};
const int eg_value[6] = { 94, 281, 297, 512,  936,  0};

const int mg_pawn_table[64] = {
      0,   0,   0,   0,   0,   0,  0,   0,
     98, 134,  61,  95,  68, 126, 34, -11,
     -6,   7,  26,  31,  65,  56, 25, -20,
    -14,  13,   6,  21,  23,  12, 17, -23,
    -27,  -2,  -5,  12,  17,   6, 10, -25,
    -26,  -4,  -4, -10,   3,   3, 33, -12,
    -35,  -1, -20, -23, -15,  24, 38, -22,
      0,   0,   0,   0,   0,   0,  0,   0,
};

const int eg_pawn_table[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
    178, 173, 158, 134, 147, 132, 165, 187,
     94, 100,  85,  67,  56,  53,  82,  84,
     32,  24,  13,   5,  -2,   4,  17,  17,
     13,   9,  -3,  -7,  -7,  -8,   3,  -1,
      4,   7,  -6,   1,   0,  -5,  -1,  -8,
     13,   8,   8,  10,  13,   0,   2,  -7,
      0,   0,   0,   0,   0,   0,   0,   0,
};

const int mg_knight_table[64] = {
    -167, -89, -34, -49,  61, -97, -15, -107,
     -73, -41,  72,  36,  23,  62,   7,  -17,
     -47,  60,  37,  65,  84, 129,  73,   44,
      -9,  17,  19,  53,  37,  69,  18,   22,
     -13,   4,  16,  13,  28,  19,  21,   -8,
     -23,  -9,  12,  10,  19,  17,  25,  -16,
     -29, -53, -12,  -3,  -1,  18, -14,  -19,
    -105, -21, -58, -33, -17, -28, -19,  -23,
};

const int eg_knight_table[64] = {
    -58, -38, -13, -28, -31, -27, -63, -99,
    -25,  -8, -25,  -2,  -9, -25, -24, -52,
    -24, -20,  10,   9,  -1,  -9, -19, -41,
    -17,   3,  22,  22,  22,  11,   8, -18,
    -18,  -6,  16,  25,  16,  17,   4, -18,
    -23,  -3,  -1,  15,  10,  -3, -20, -22,
    -42, -20, -10,  -5,  -2, -20, -23, -44,
    -29, -51, -23, -15, -22, -18, -50, -64,
};

const int mg_bishop_table[64] = {
    -29,   4, -82, -37, -25, -42,   7,  -8,
    -26,  16, -18, -13,  30,  59,  18, -47,
    -16,  37,  43,  40,  35,  50,  37,  -2,
     -4,   5,  19,  50,  37,  37,   7,  -2,
     -6,  13,  13,  26,  34,  12,  10,   4,
      0,  15,  15,  15,  14,  27,  18,  10,
      4,  15,  16,   0,   7,  21,  33,   1,
    -33,  -3, -14, -21, -13, -12, -39, -21,
};

const int eg_bishop_table[64] = {
    -14, -21, -11,  -8, -7,  -9, -17, -24,
     -8,  -4,   7, -12, -3, -13,  -4, -14,
      2,  -8,   0,  -1, -2,   6,   0,   4,
     -3,   9,  12,   9, 14,  10,   3,   2,
     -6,   3,  13,  19,  7,  10,  -3,  -9,
    -12,  -3,   8,  10, 13,   3,  -7, -15,
    -14, -18,  -7,  -1,  4,  -9, -15, -27,
    -23,  -9, -23,  -5, -9, -16,  -5, -17,
};

const int mg_rook_table[64] = {
     32,  42,  32,  51, 63,  9,  31,  43,
     27,  32,  58,  62, 80, 67,  26,  44,
     -5,  19,  26,  36, 17, 45,  61,  16,
    -24, -11,   7,  26, 24, 35,  -8, -20,
    -36, -26, -12,  -1,  9, -7,   6, -23,
    -45, -25, -16, -17,  3,  0,  -5, -33,
    -44, -16, -20,  -9, -1, 11,  -6, -71,
    -19, -13,   1,  17, 16,  7, -37, -26,
};

const int eg_rook_table[64] = {
    13, 10, 18, 15, 12,  12,   8,   5,
    11, 13, 13, 11, -3,   3,   8,   3,
     7,  7,  7,  5,  4,  -3,  -5,  -3,
     4,  3, 13,  1,  2,   1,  -1,   2,
     3,  5,  8,  4, -5,  -6,  -8, -11,
    -4,  0, -5, -1, -7, -12,  -8, -16,
    -6, -6,  0,  2, -9,  -9, -11,  -3,
    -9,  2,  3, -1, -5, -13,   4, -20,
};

const int mg_queen_table[64] = {
    -28,   0,  29,  12,  59,  44,  43,  45,
    -24, -39,  -5,   1, -16,  57,  28,  54,
    -13, -17,   7,   8,  29,  56,  47,  57,
    -27, -27, -16, -16,  -1,  17,  -2,   1,
     -9, -26,  -9, -10,  -2,  -4,   3,  -3,
    -14,   2, -11,  -2,  -5,   2,  14,   5,
    -35,  -8,  11,   2,   8,  15,  -3,   1,
     -1, -18,  -9,  10, -15, -25, -31, -50,
};

const int eg_queen_table[64] = {
     -9,  22,  22,  27,  27,  19,  10,  20,
    -17,  20,  32,  41,  58,  25,  30,   0,
    -20,   6,   9,  49,  47,  35,  19,   9,
      3,  22,  24,  45,  57,  40,  57,  36,
    -18,  28,  19,  47,  31,  34,  39,  23,
    -16, -27,  15,   6,   9,  17,  10,   5,
    -22, -23, -30, -16, -16, -23, -36, -32,
    -33, -28, -22, -43,  -5, -32, -20, -41,
};

const int mg_king_table[64] = {
    -65,  23,  16, -15, -56, -34,   2,  13,
     29,  -1, -20,  -7,  -8,  -4, -38, -29,
     -9,  24,   2, -16, -20,   6,  22, -22,
    -17, -20, -12, -27, -30, -25, -14, -36,
    -49,  -1, -27, -39, -46, -44, -33, -51,
    -14, -14, -22, -46, -44, -30, -15, -27,
      1,   7,  -8, -64, -43, -16,   9,   8,
    -15,  36,  12, -54,   8, -28,  24,  14,
};

const int eg_king_table[64] = {
    -74, -35, -18, -18, -11,  15,   4, -17,
    -12,  17,  14,  17,  17,  38,  23,  11,
     10,  17,  23,  15,  20,  45,  44,  13,
     -8,  22,  24,  27,  26,  33,  26,   3,
    -18,  -4,  21,  24,  27,  23,   9, -11,
    -19,  -3,  11,  21,  23,  16,   7,  -9,
    -27, -11,   4,  13,  14,   4,  -5, -17,
    -53, -34, -21, -11, -28, -14, -24, -43
};

const int* mg_pesto_table[6] =
{
    mg_pawn_table,
    mg_knight_table,
    mg_bishop_table,
    mg_rook_table,
    mg_queen_table,
    mg_king_table
};

const int* eg_pesto_table[6] =
{
    eg_pawn_table,
    eg_knight_table,
    eg_bishop_table,
    eg_rook_table,
    eg_queen_table,
    eg_king_table
};

const int piecevalue[12] = {1,3,3,5,9,0,1,3,3,5,9,0};
const int gamephaseInc[12] = {0,1,1,2,4,0,0,1,1,2,4,0};

int mg_table[12][64];
int eg_table[12][64];

int PCOLOR(int x) {
    return x >= 6;
}

int inZone(int sq1, int sq2) {
    int x1 = sq1/8, y1 = sq1%8;
    int x2 = sq2/8, y2 = sq2%8;

    return abs(x1 - x2) + abs(y1 - y2) <= 3;
}

int FLIP(int sq) {
    return Mirror64Board[sq];
}

void init_tables()
{
    int pc, p, sq;
    for (p = 0, pc = 0; p <= 5; pc ++, p++) {
        for (sq = 0; sq < 64; sq++) {

            mg_table[pc][sq] = mg_value[p] + mg_pesto_table[p][FLIP(sq)];
            eg_table[pc][sq] = eg_value[p] + eg_pesto_table[p][FLIP(sq)];
            mg_table[pc+6][sq] = mg_value[p] + mg_pesto_table[p][sq];
            eg_table[pc+6][sq] = eg_value[p] + eg_pesto_table[p][sq];
        }
    }
}

GameHelper gamehelper;

AI::AI(Color ME, int botDifficulty) 
    : ME(ME), OPP(ME == Color::BLACK ? Color::WHITE : Color::BLACK), botDifficulty(botDifficulty) 
    {
        init_tables();
    }

int AI::utility(Board board, Color turn) {
    if (gamehelper.isStaleMate(board) || cnt[board.hash()] >= 3) return 0;
    if (gamehelper.isCheckMate(board)) {
        if (turn == ME) return -1000000;
        else return +1000000;
    }

    int white = 0, black = 1;
    int mg[2];
    int eg[2];
    int material[2];
    // int material_mg[2];
    // int material_eg[2];
    int attack[2];
    int gamePhase = 0;

    material[white] = 0;
    material[black] = 0;
    mg[white] = 0;
    mg[black] = 0;
    eg[white] = 0;
    eg[black] = 0;
    // material_mg[white] = 0;
    // material_mg[black] = 0;
    // material_eg[white] = 0;
    // material_eg[black] = 0;
    attack[white] = 0;
    attack[black] = 0;

    for (int sq = 0; sq < 64; ++sq) {
        Square square = sq;
        int pc = board.at(sq);
        if (pc <= 11) { // 12 jest puste
            // material_eg[PCOLOR(pc)] += eg_value[pc%6];
            // material_mg[PCOLOR(pc)] += mg_value[pc%6];
            material[PCOLOR(pc)] += piecevalue[pc];
            mg[PCOLOR(pc)] += mg_table[pc][sq];
            eg[PCOLOR(pc)] += eg_table[pc][sq];
            gamePhase += gamephaseInc[pc];

            if (pc == 5) { // krol bialy
                for (int sq2 = 0; sq2 < 64; sq2 ++) {
                    if (inZone(sq, sq2) && board.isAttacked(sq2, Color::BLACK)) {
                        attack[black] ++;
                    }
                }
            }

            if (pc == 11) { // krol czarny
                 for (int sq2 = 0; sq2 < 64; sq2 ++) {
                    if (inZone(sq, sq2) && board.isAttacked(sq2, Color::WHITE)) {
                        attack[white] ++;
                    }
                }
            }
        }
    }

    /* tapered eval */
    int side2move = (ME == Color::WHITE ? 0 : 1);
    // int materialMgScore = material_mg[side2move] - material_mg[1-side2move];
    // int materialEgScore = material_eg[side2move] - material_eg[1-side2move];
    int mgScore = mg[side2move] - mg[1-side2move];
    int egScore = eg[side2move] - eg[1-side2move];
    int mgPhase = gamePhase;
    if (mgPhase > 24) mgPhase = 24; /* in case of early promotion */
    int egPhase = 24 - mgPhase;
    int res = (mgScore * mgPhase + egScore * egPhase) / 24;
    //10*(material[side2move] - material[1-side2move]) + 5*(attack[side2move] - attack[1-side2move]);

    // int res = (mgScore * mgPhase + egScore * egPhase) / 24 + 
    // (materialMgScore * mgPhase + materialEgScore * egPhase) / 24 +
    // 5*(attack[side2move] - attack[1-side2move]);
    

    return res;
}

int AI::getDepth() {
    return botDifficulty;
}

pair<int, string> AI::minimax(Board board, int alpha, int beta, Color to_play, int depth) {

    int hasz = board.hash();
    int what = getDepth();

    if (mapka.find(hasz) != mapka.end()) {
        assert(depth > 0);
        return {mapka[hasz], "-1 -1"};
    }

    if (gamehelper.isGameOver(board) || depth >= what) {
        return {utility(board, to_play), "-1 -1"};
    }

    pair<int, string> res = {-INF, "-1 -1"};
    if (to_play == ME) { // MAX
        res.first = -INF;
        Movelist moves = gamehelper.getMoves(board);
        Board board_copy = board;
        vector<pair<int, int>> vec;
        for (int i = 0; i < (int)moves.size(); i ++) {
            vec.push_back({0, i});
        }
        if (depth <= 3) {
            for (int i = 0; i < (int)moves.size(); i ++) {
                board_copy.makeMove(moves[i]);
                vec[i].first = utility(board_copy, OPP);
                board_copy.unmakeMove(moves[i]);
            } 
            sort(vec.begin(), vec.end(), greater<pair<int,int>>());
        }
        for (auto v : vec) {
            auto move = moves[v.second];
            board_copy.makeMove(move);
            pair<int, string> it = make_pair(0, "-1 -1");
            if (cnt[board_copy.hash()] < 3) {
                it = minimax(board_copy, alpha, beta, gamehelper.opposite(to_play), depth+1);
                mapka[board_copy.hash()] = it.first;
            }
            board_copy.unmakeMove(move);

            if (res.first < it.first) {
                res.first = it.first;
                res.second = uci::moveToUci(move);
            }

            if (it.first >= beta && depth > 0) {
                return {it.first, "-1 -1"};
            }

            alpha = max(alpha, it.first);
        } 
    } else { // MIN
        res.first = INF;
        Movelist moves = gamehelper.getMoves(board);
        Board board_copy = board;
        vector<pair<int, int>> vec;
        for (int i = 0; i < (int)moves.size(); i ++) {
            vec.push_back({0, i});
        }
        if (depth <= 3) {
            for (int i = 0; i < (int)moves.size(); i ++) {
                board_copy.makeMove(moves[i]);
                vec[i].first = utility(board_copy, ME);
                board_copy.unmakeMove(moves[i]);
            } 
            sort(vec.begin(), vec.end());
        }
        for (auto v : vec) {
            auto move = moves[v.second];
            board_copy.makeMove(move);
            pair<int, string> it = make_pair(0, "-1 -1");
            if (cnt[board_copy.hash()] < 3) {
                it = minimax(board_copy, alpha, beta, gamehelper.opposite(to_play), depth+1);
                mapka[board_copy.hash()] = it.first;
            }
            board_copy.unmakeMove(move);

            if (res.first > it.first) {
                res.first = it.first;
                res.second = uci::moveToUci(move);
            }

            if (it.first <= alpha && depth > 0) {
                return {it.first, "-1 -1"};
            }

            beta = min(beta, it.first);
        } 
    }

    return res;
}

string AI::decodePolyGlotMove(unsigned short polyMove) {
    int to_file = int(polyMove & 7);
    int to_row = int((polyMove >> 3) & 7);
    int from_file = int((polyMove >> 6) & 7);
    int from_row = int((polyMove >> 9) & 7);
    // uint8_t promotionCode = (polyMove >> 12) & 0x7;

    string uci_move = "";
    uci_move += char('a'+from_file);
    uci_move += char('1'+from_row);
    uci_move += char('a'+to_file);
    uci_move += char('1'+to_row);

    return uci_move;
}

void AI::loadOpeningBook(string filename) {
    ifstream bin_file(filename, ios::binary);
    if (!bin_file.is_open()) {
        cerr << "Nie można otworzyć pliku: " << filename << '\n';
        return;
    }
    
    while (bin_file.peek() != EOF) {
        U64 key;
        unsigned short polyMove;
        unsigned short weight;
        unsigned int learn;

        bin_file.read((char*) &key, sizeof(key));
        bin_file.read((char*) &polyMove, sizeof(polyMove));
        bin_file.read((char*) &weight, sizeof(weight));
        bin_file.read((char*) &learn, sizeof(learn));

        key = __builtin_bswap64(key);
        polyMove = __builtin_bswap16(polyMove);
        weight = __builtin_bswap16(weight);
        learn = __builtin_bswap32(learn);

        string uci_move = decodePolyGlotMove(polyMove);

        if (openingBook[key].size() < 5) openingBook[key].push_back({weight, uci_move});
        else if (openingBook[key][0].first < weight) {
            openingBook[key][0] = {weight, uci_move};
            sort(openingBook[key].begin(), openingBook[key].end());
        }
    }

    bin_file.close();
}

string AI::getMoveFromOpeningBook(Board board) {
    U64 key = board.hash();
    if (openingBook.find(key) != openingBook.end()) {
        return openingBook[key].back().second;
    }
    return "-1 -1";
}

string AI::getMove(Board board) {
    string opMove = getMoveFromOpeningBook(board);
    if (opMove != "-1 -1") return opMove;

    string minimaxMove = minimax(board, -INF, INF, ME, 0).second;
    assert(minimaxMove != "-1 -1");

    return minimaxMove;
}