#include "Game.h"

Game::Game() : running(false) {}

bool Game::isRunning() const {
    return running;
}

void Game::setRunning(bool isRunning) {
    running = isRunning;
}
