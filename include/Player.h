#ifndef PLAYER_H
#define PLAYER_H
#include <Object.h>

class Player: public Object{
    public:
        Player();
        void update();
        void input();
        void swing();
        void jump();
        void accelRight();
        void accelLeft();
        void deAccel();
        void updateV();
        void updateX();

    private:
        bool isSwinging = false;
        int swingTimer;

        float acc = 4;
        float deacc = 0.5;
        float jumpv = 30;
        float gravity = 2;
        float vmin = 1;
        float vmax = 10;
        bool lookingRight = true;
        bool canMove = true;
        sf::RectangleShape* swingBox;
};

#endif // PLAYER_H
