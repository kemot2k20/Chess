#ifndef PLAYER_H
#define PLAYER_H

#include <bits/stdc++.h>
#include "chess-library-master/include/chess.hpp"

using namespace std;
using namespace chess;

struct Player {
    string name;
    bool isAI;
    Color color;
    Player(string name, bool isAI, Color color);
};

#endif