#ifndef DRAWHANDLER_H
#define DRAWHANDLER_H
#include "WallHandler.h"
#include "ObjectHandler.h"
#include "BoxHandler.h"

extern "C" RenderWindow win;

namespace DrawHandler {
    void drawWalls();
    void drawObjects();
    void drawBoxes();
    void drawAll();
};

#endif // DRAWHANDLER_H
