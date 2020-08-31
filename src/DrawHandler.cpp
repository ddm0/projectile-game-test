#include "DrawHandler.h"

namespace DrawHandler {
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
        win.draw(ObjectHandler::getBall(i));
    }
    for (int i = 0; i < ObjectHandler::getPlayerCount(); i++) {
        win.draw(ObjectHandler::getPlayer(i));
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
