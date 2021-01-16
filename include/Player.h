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

		int tpCharge = 0;
		int tpChargeRate = 5;
		int tpMaxDistance = 200;

        float acc = 4;
        float deacc = 0.5;
        float jumpv = 30;
        float gravity = 0;
        float vmin = 1;
        float vmax = 10;
        bool lookingRight = true;
        bool canMove = true;
        sf::RectangleShape* swingBox;
		
		void teleport();
		bool isTpCharging();
		void chargeTp();
};

#endif // PLAYER_H
