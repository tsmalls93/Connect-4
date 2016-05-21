//
//  Window.hpp
//  connect4
//
//  Created by Tyler Small on 4/29/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include "Search.hpp"

class Window {
    Game game;
    Search search;
    static const char *optns[];
    int moves[SIZE],nmoves, movenr;
    
public:
    Window(const char *bookfile);
    ~Window();
    void refresh();
    bool back();
    bool forward();
    bool play(int n);
    void showgamemoves();
    bool reset();
    bool solve();
    bool evals();
    bool stats();
    bool chglvl(int l);
    void showevals();
};
#endif /* Window_hpp */
