#include "game.h"

Game::~Game()
{
    delete window;
    delete level;
}

Game &Game::GetGame()
{
    static Game game;
    return game;
}