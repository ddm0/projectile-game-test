#include "DrawHandler.h"

namespace {
    bool displayBoxes = true;
}

void DrawHandler::drawWalls() {
    for (int i = 0; i < 4; i++) {
        win.draw(WallHandler::getMainWall(i));
        if (i < WallHandler::getExtraWallCount()) {
            win.draw(WallHandler::getExtraWall(i));
        }
    }
}

void DrawHandler::drawObjects() {
    for (int i = 0; i < ObjectHandler::getBallCount(); i++) {
        ObjectHandler::getBall(i).draw(win);
    }
    for (int i = 0; i < ObjectHandler::getPlayerCount(); i++) {
        ObjectHandler::getPlayer(i).draw(win);
    }
}

void DrawHandler::drawBoxes() {
    for (int i = 0; i < BoxHandler::getBoxCount(); i++) {
        win.draw(*BoxHandler::getBox(i));
    }
}

void DrawHandler::drawAll() {
    win.clear();
    drawWalls();
    if (displayBoxes) {
        drawBoxes();
    }
    drawObjects();
}
