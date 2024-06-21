#ifndef UI_H
#define UI_H

#include <bits/stdc++.h>

struct UI {
    void displayBoard(std::string fen);
    std::string getUserMove(std::string name);
    void over(std::string);
    void illegalMove();
    void quitGame();
};

#endif