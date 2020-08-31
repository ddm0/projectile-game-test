#ifndef BOXHANDLER_H
#define BOXHANDLER_H
#include <SFML/Graphics.hpp>
#include <iostream>

namespace BoxHandler
{
    void createBox(); //aaaa

    int getBoxCount();
    void destroyBox(sf::RectangleShape* i);
    sf::RectangleShape* getBox(int i);
    //bool checkCol(Object* a, Object b);
};

#endif // BOXHANDLER_H
