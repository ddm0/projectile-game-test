#include "Player.h"
#include "ObjectHandler.h"
#include "BoxHandler.h"

#include <SFML/Window/Mouse.hpp>
#include "DrawHandler.h"

Player::Player(): Object (TextureHandler::getPlayerTexture()) {
    setSca(0.4);
    pos.x = 600;
    pos.y = 300;
}

void Player::update() {
    if (isSwinging) {
        if (swingTimer > 0) {
            swingTimer--;
        }
        else {
            isSwinging = false;
            canMove = true;

            BoxHandler::destroyBox(swingBox);
        }
    }
    hitLines[0].position = sf::Vector2f(getLeft(), getBot());
    hitLines[1].position = sf::Vector2f(getRight(), getBot());

    input();
    updateV();
    updateX();
    sprite.setPosition(pos.x, pos.y);
}

void Player::input() {
    if (Keyboard::isKeyPressed(Keyboard::Z) && !isSwinging) {
        swing();
    }

	if (isChargingTp) {
		if(!Keyboard::isKeyPressed(Keyboard::Space)) {
			teleport();
			tpDistance = 0;
		} else {
			tpDistance++;
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		isChargingTp = true;
		canMove = false;
	}

    //movement
    if (canMove) {
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            accelRight();
            lookingRight = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            accelLeft();
            lookingRight = false;
        }
        else {
            deAccelX();
        }
		
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			accelUp();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			accelDown();
		}
		else {
			deAccelY();
		}
    }
    else {
        vel.x = 0;
		vel.y = 0;
    }

}

void Player::teleport() {
	isChargingTp = false;

	sf::Vector2i playerp(pos.x + width / 2, pos.y + height / 2);
	sf::Vector2i mousep = sf::Mouse::getPosition(DrawHandler::getWindow()); 

	double angle = -atan(double(mousep.y - playerp.y) / (mousep.x - playerp.x));

	if (mousep.x > playerp.x) {
		pos.x += tpDistance * cos(angle);
		pos.y -= tpDistance * sin(angle);
	} else {
		pos.x -= tpDistance * cos(angle);
		pos.y += tpDistance * sin(angle);
	}
	
	isChargingTp = false;
	canMove = true;
}

void Player::swing() {
    isSwinging = true;
    canMove = false;
    swingTimer = 120;

    BoxHandler::createBox();
    swingBox = BoxHandler::getBox(BoxHandler::getBoxCount() - 1);
    swingBox->setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    swingBox->setFillColor(sf::Color::Blue);
    if (lookingRight) {
        swingBox->setPosition(pos.x + sprite.getGlobalBounds().width, pos.y);
    }
    else swingBox->setPosition(pos.x - sprite.getGlobalBounds().width, pos.y);
}

void Player::accelUp() {
    vel.y = clamp(vel.y - acc, -vmax, vmax);
}

void Player::accelDown() {
    vel.y = clamp(vel.y + acc, -vmax, vmax);
}

void Player::accelRight() {
    vel.x = clamp(vel.x + acc, -vmax, vmax);
}

void Player::accelLeft() {
    vel.x = clamp(vel.x - acc, -vmax, vmax);
}

void Player::deAccelX() {
    vel.x *= deacc;
}

void Player::deAccelY() {
    vel.y *= deacc;
}

void Player::updateV() {
    //collision check
    if ((isAgainstLeftWall() && vel.x < 0) || (isAgainstRightWall() && vel.x > 0)) {
        vel.x = -vel.x;
    }

	if ((isAgainstCeiling() && vel.y < 0) || (isAgainstFloor() && vel.y > 0)) {
		vel.y = -vel.y;
	}
}

void Player::updateX() {
    pos.x += vel.x;
    pos.y += vel.y;
}
