#ifndef BOXHANDLER_H
#define BOXHANDLER_H
#include <SFML/Graphics.hpp>
#include <iostream>

namespace BoxHandler {
    void createBox(); //aaaa
    void destroyBox(sf::RectangleShape* i);
    int getBoxCount();
    sf::RectangleShape* getBox(int i);
    //bool checkCol(Object* a, Object b);
};

#endif // BOXHANDLER_H
