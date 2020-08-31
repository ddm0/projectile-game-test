#ifndef OBJECT_H
#define OBJECT_H
#include <math2.h>
#include <WallHandler.h>
#include <TextureHandler.h>

class Object : public sf::Sprite {
    public:
        Object(sf::Texture& a);
        Vector2i pos;
        Vector2i vel;
        bool isAgainstCorner(Wall& a);
        bool isAgainstTop(Wall& a);
        bool isAgainstBot(Wall& a);
        bool isAgainstLeft(Wall& a);
        bool isAgainstRight(Wall& a);
        bool isAgainst(Wall& a);
        bool isCornerIntersect(Wall& a);

        /*
        bool isAgainstTop(Object a);
        bool isAgainstBot(Object a);
        bool isAgainstLeft(Object a);
        bool isAgainstRight(Object a);
        bool isAgainst(Object a);
        */

        bool isAgainstFloor();
        bool isAgainstLeftWall();
        bool isAgainstRightWall();
        bool isAgainstCeiling();
        bool isAgainstAnyX();
        bool isAgainstAnyY();
        bool isAgainstMain();
        bool isAgainstAny();
        bool isCornerInterAny();

        bool collisionDist(sf::RectangleShape r, int &d, Vector2<int> &t);
        sf::VertexArray hitLines = sf::VertexArray(sf::Lines, 6);

        int getBot();
        int getRight();
        int getTop();
        int getLeft();

        void setBot(int a);
        void setSca(float a);

    protected:
        float scale = 1;

    private:
        void updateSize();
        int width;
        int height;


        /*
        bool isAgainstTop(sf::FloatRect a);
        bool isAgainstBot(sf::FloatRect a);
        bool isAgainstLeft(sf::FloatRect a);
        bool isAgainstRight(sf::FloatRect a);
        bool isAgainst(sf::FloatRect a);
        */

        bool segmentIntersectsRectangle(const sf::FloatRect& rect,
        const sf::Vector2f& a_p1, const sf::Vector2f& a_p2);
};

#endif // OBJECT_H
