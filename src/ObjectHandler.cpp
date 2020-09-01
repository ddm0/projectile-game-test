#include "ObjectHandler.h"

namespace {
    const int maxBall = 3;
    const int maxPlayer = 2;
    int ballCount = 0;
    int playerCount = 0;
    std::vector<Ball> ball;
    std::vector<Player> player;
}

void ObjectHandler::createBall() {
    if (ballCount < maxBall) {
        ballCount++;
        ball.resize(ballCount);
    }
    else std::cerr << "ERROR: Can't create ball. Too many balls exist." << std::endl;
}

void ObjectHandler::createPlayer() {
    if (playerCount < maxPlayer) {
        playerCount++;
        player.resize(playerCount);
    }
    else std::cerr << "ERROR: Can't create player. Too many players exist." << std::endl;
}


void ObjectHandler::updateAllBalls() {
   for (int i = 0; i < ballCount; i++) {
        getBall(i).update();
   }
}

void ObjectHandler::updateAllPlayers() {
   for (int i = 0; i < playerCount; i++) {
        getPlayer(i).update();
   }
}

void ObjectHandler::updateAllObjects() {
    updateAllPlayers();
    updateAllBalls();
}

int ObjectHandler::getBallCount() {
    return ballCount;
}

int ObjectHandler::getPlayerCount() {
    return playerCount;
}

bool ObjectHandler::isBallOutOfBounds() {
    sf::Vector2i pos = getBall(0).getPos();
    return (pos.y > 1280 ||
            pos.y < 0 ||
            pos.x > 1280 ||
            pos.x < 0);
}

Ball& ObjectHandler::getBall(int i) {
    return ball[i];
}

Player& ObjectHandler::getPlayer(int i) {
    return player[i];
}
