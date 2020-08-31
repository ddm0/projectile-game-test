#include "Ball.h"

Ball::Ball(): Object (TextureHandler::getBallTexture()) {
    pos.x = 800;
    pos.y = 439;
    move(pos.x, pos.y);
}

void Ball::angleupdate() {
    bool x = isAgainstAnyX();
    bool y = isAgainstAnyY();

    //fix corner edge case (see picture). if corner hits corner but is going wrong direction
    //if it is against x and y for two rectangles (concave) OR corner intersects extra (convex) flip angle
    if (x && y) {
        angle += 180;
        return;
    } else {
        for (int i = 0; i < WallHandler::getExtraWallCount(); i++) {
            if (isCornerIntersect(WallHandler::getExtraWall(i))) {
                angle += 180;
                return;
            }
        }
    }

    if (x) {
        angle = 180 - angle;
    } else if (y) {
        angle = 360 - angle;
    }
}

void Ball::update() {
    angleupdate();

    bool angleC = true;
    while (angleC) {
        if (angle >= 360) {
            angle -= 360;
        } else if (angle < 0) {
            angle += 360;
        } else {
            angleC = false;
        }
    }

    vel.x = cosd(angle) * speed;
    vel.y = -sind(angle) * speed;

    int dist;
    int minDist = 0;
    Vector2i linePos;
    Vector2i minLinePos;

    for (int i = 0; i < 4; i++) {
        bool hit = collisionDist(WallHandler::getMainWall(i), dist, linePos);
        if (hit && (minDist == 0 || dist < minDist)) {
            minDist = dist;
            minLinePos = linePos;
        }

        if (i < WallHandler::getExtraWallCount()) {
            bool hit2 = collisionDist(WallHandler::getExtraWall(i), dist, linePos);
            if (hit2 && (minDist == 0 || dist < minDist)) {
                minDist = dist;
                minLinePos = linePos;
            }
        }
    }

    if (minDist != 0) {
        pos = minLinePos;
    } else {
        pos += vel;
    }
    setPosition((float)pos.x, (float)pos.y);
}

void Ball::setSpeed(int s) {
    speed = s;
}

void Ball::addSpeed(int s) {
    speed += s;
}
