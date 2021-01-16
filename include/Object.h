#ifndef OBJECT_H
#define OBJECT_H
#include <math2.h>
#include <WallHandler.h>
#include <TextureHandler.h>

class Object {
    public:
        Object(sf::Texture& t);

        bool isAgainstCorner(Wall& a);
        bool isAgainstTop(Wall& a);
        bool isAgainstBot(Wall& a);
        bool isAgainstLeft(Wall& a);
        bool isAgainstRight(Wall& a);
        bool isAgainst(Wall& a);
        bool isCornerIntersect(Wall& a);

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

        sf::Vector2i getPos();
        sf::Vector2i getVel();
        void draw(sf::RenderTarget& t);

        int getBot();
        int getRight();
        int getTop();
        int getLeft();
        void setBot(int a);
        void setSca(float a);

    protected:
        sf::Sprite sprite;
        int width;
        int height;
        float scale = 1;
        sf::Vector2i pos;
        sf::Vector2i vel;


    private:
        void updateSize();
        bool segmentIntersectsRectangle(const sf::FloatRect& rect,
        const sf::Vector2f& a_p1, const sf::Vector2f& a_p2);
};

#endif // OBJECT_H
