#ifndef BALL_H
#define BALL_H
#include <Object.h>


class Ball: public Object{ // do corners and hitbox wall like you drid with player
    public:
        Ball();
        int angle = 360-45;//0=neutral
        int speed = 10;
        void update();
        void setSpeed(int s);
        void addSpeed(int s);
        //window.draw(line, 2, sf::Lines);
        //sf::RectangleShape scanBox;

    private:
        void angleupdate();
};

#endif // BALL_H
