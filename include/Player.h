#ifndef PLAYER_H
#define PLAYER_H
#include <Object.h>

class Player: public Object{
    public:
        Player();
        void update();
        void input();
        void swing();
        void accelRight();
        void accelLeft();
		void accelUp();
		void accelDown();
        void deAccelX();
        void deAccelY();
        void updateV();
        void updateX();

    private:
        bool isSwinging = false;
        int swingTimer;

		bool isChargingTp = false;
		int tpDistance = 0;

        float acc = 4;
        float deacc = 0.5;
        float jumpv = 30;
        float gravity = 0;
        float vmin = 1;
        float vmax = 10;
        bool lookingRight = true;
        bool canMove = true;
        sf::RectangleShape* swingBox;
};

#endif // PLAYER_H
