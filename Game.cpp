#include "Game.h"

Game::Game() : running(false), timer(Timer()) {}

bool Game::isRunning() const {
    return running;
}

void Game::setRunning(bool isRunning) {
    running = isRunning;
}

const bool *Game::getRunning() {
    return &running;
}

Timer &Game::getTimer() {
    return timer;
}
