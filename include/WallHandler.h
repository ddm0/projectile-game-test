#ifndef WALLHANDLER_H
#define WALLHANDLER_H
#include <Wall.h>
#include <vector>
#include <iostream>

extern "C" int screenheight,screenwidth;

namespace WallHandler {
    void createMainWall();
    void createTopWall();
    void createBotWall();
    void createLeftWall();
    void createRightWall();
    void createMainWalls();
    void createExtraWall(Vector2f p, Vector2f s);
    Wall& getMainWall(int i);
    Wall& getExtraWall(int i);
    int getExtraWallCount();
    Wall& getTopWall();
    Wall& getBotWall();
    Wall& getLeftWall();
    Wall& getRightWall();
};

#endif // WALLHANDLER_H
