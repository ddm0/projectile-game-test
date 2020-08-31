#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>

class Wall : public sf::RectangleShape {
    public:
        Wall();

        int getBot();
        int getRight();
        int getTop();
        int getLeft();

    protected:

    private:
        float pos;
};

#endif // WALL_H
