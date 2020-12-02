#ifndef GAME_H
#define GAME_H

#include "window.h"
#include "levels/level.h"

struct Game
{
    Window *window;
    Level *level;

    ~Game();

    static Game& GetGame();
};

#endif