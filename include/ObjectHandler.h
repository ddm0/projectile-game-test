#ifndef OBJECTHANDLER_H
#define OBJECTHANDLER_H
#include <Player.h>
#include <Ball.h>
#include <vector>

namespace ObjectHandler {
    void createBall();
    void createPlayer();
    void updateBalls();
    void updatePlayers();
    void updateObjects();
    int getBallCount();
    int getPlayerCount();
    Ball& getBall(int i);
    Player& getPlayer(int i);
};

#endif // OBJECTHANDLER_H
