#include <bits/stdc++.h>
#include "ui.h"
#include <ncurses.h>

using namespace std;

const unordered_map<char, string> pieceSymbols = {
    {'P', "\u2659"}, {'R', "\u2656"}, {'N', "\u2658"}, {'B', "\u2657"}, {'Q', "\u2655"}, {'K', "\u2654"},
    {'p', "\u265F"}, {'r', "\u265C"}, {'n', "\u265E"}, {'b', "\u265D"}, {'q', "\u265B"}, {'k', "\u265A"}
};

void UI::displayBoard(string fen) {
    setlocale(LC_ALL, ""); // Ustawienia lokalne dla obsługi znaków Unicode
    initscr();            // Rozpoczyna tryb ncurses
    start_color();        // Włącza obsługę kolorów

    init_pair(1, COLOR_BLACK, COLOR_WHITE);  // Kolor tła planszy

    int height = 12;
    int width = 40;

    WINDOW *win = newwin(height, width, 0, 5);
    wbkgd(win, COLOR_PAIR(1)); // Ustawia kolor tła planszy
    box(win, 0, 0);       // Dodaje ramkę do okna

    int rowNumber = 8;
    for (int i = 1; i <= 8; ++i) {
        mvwprintw(win, i, 1, " %d", rowNumber--);
    }

    char colLetter = 'a';
    for (int i = 1; i <= 8; ++i) {
        mvwprintw(win, 9, i * 3 + 2, " %c", colLetter++);
    }

    int row = 1;
    int col = 6;

    for (char c : fen) {
        if (c == ' ') break;
        if (c == '/') {
            row++;
            col = 6;
            continue;
        } else if (isdigit(c)) {
            col += (c - '0') * 3;
            continue;
        }

        // Rysowanie symbolu figury na planszy
        string symbol = pieceSymbols.at(c);
        mvwprintw(win, row, col, "%s", symbol.c_str());

        col += 3;
    }

    wrefresh(win);
}

string UI::getUserMove(string name) {
    const char *name_cstr = name.c_str();
    WINDOW *input_win = newwin(3, 40, 12, 5);
    box(input_win, 0, 0);
    
    mvwprintw(input_win, 1, 1, "Your move %s: ", name_cstr);

    int x_position = 1 + 11 + strlen(name_cstr);
    wrefresh(input_win);

    char move[6];
    echo();
    mvwgetnstr(input_win, 1, x_position, move, 5);
    noecho();

    delwin(input_win);
    return string(move);
}

void UI::illegalMove() {
    clear(); // Czyści ekran
    int height, width;
    getmaxyx(stdscr, height, width); // Pobiera rozmiar ekranu

    mvprintw(height / 2 - 1, (width - strlen("Illegal move!")) / 2, "Illegal move!");
    mvprintw(height / 2, (width - strlen("Try again.")) / 2, "Try again.");
    mvprintw(height / 2 + 1, (width - strlen("Press any key to continue.")) / 2, "Press any key to continue.");

    refresh();
    getch(); // Czeka na wciśnięcie klawisza
}

void UI::over(string message) {
    int height, width;
    getmaxyx(stdscr, height, width);

    mvprintw(height - 2, (width - message.length()) / 2, "%s", message.c_str());
    mvprintw(height - 1, (width - strlen("Press any key to exit.")) / 2, "Press any key to exit.");
    refresh();

    getch();
    quitGame();
}

void UI::quitGame() {
    endwin();
}