#include "Wall.h"

Wall::Wall()
{
    //ctor
}

int Wall::getTop() {
    return getGlobalBounds().top;
}

int Wall::getBot() {
    return getGlobalBounds().top + getGlobalBounds().height;
}

int Wall::getLeft() {
    return getGlobalBounds().left;
}

int Wall::getRight() {
    return getGlobalBounds().left + getGlobalBounds().width;
}
