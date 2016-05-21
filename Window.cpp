//
//  Window.cpp
//  connect4
//
//  Created by Tyler Small on 4/29/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//

#include "Window.hpp"
Window::Window(const char *bookfile) : game(), search(this, game, bookfile), nmoves(0) {
}


void Window::refresh() {
}

bool Window::back() {
    if (!movenr)
        return false;
    --movenr;
    game.backmove();
    return true;
}

bool Window::forward() {
    if (movenr >= nmoves)
        return false;
    return play(moves[movenr]);
}

bool Window::play(int n) {
    if (game.haswon(game.color[1 - (movenr & 1)]))
        return false;
    if (!game.isplayable(n))
        return false;
    if (movenr == nmoves || moves[movenr] != n) {
        nmoves = movenr;
        moves[nmoves++] = n;
    }
    game.makemove(n);
    movenr++;
    return true;
}

void Window::showgamemoves() {
}

bool Window::reset() {
    game.reset();
    movenr = 0;
    return true;
}

bool Window::solve() {
    printf("Solving . . .    \n");
    score result = search.solve();
    printf("score %c  work %d", "?-<=>+"[result], search.work);
    printf("  %ju pos / %ju msec = %jd Kpos/sec\n", (uintmax_t)search.nodes, (uintmax_t)search.msecs, (intmax_t)(search.nodes/search.msecs));
    return true;
}

bool Window::evals() {
    return true;
}

bool Window::stats() {
    return true;
}
bool Window::chglvl(int) {
    return true;
}
void Window::showevals() {
}

