#ifndef OBJECTHANDLER_H
#define OBJECTHANDLER_H
#include <Player.h>
#include <Ball.h>
#include <vector>

namespace ObjectHandler {
    void createBall();
    void createPlayer();
    void updateAllBalls();
    void updateAllPlayers();
    void updateAllObjects();
    int getBallCount();
    int getPlayerCount();
    bool isBallOutOfBounds();
    Ball& getBall(int i);
    Player& getPlayer(int i);
};

#endif // OBJECTHANDLER_H
