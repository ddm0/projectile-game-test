#include "Player.h"
#include "ObjectHandler.h"
#include "BoxHandler.h"

Player::Player(): Object (TextureHandler::getPlayerTexture()){
    setSca(0.4);
    pos.x = 600;
    pos.y = 300;
}

void Player::update(){
    if(isSwinging){
        if(swingTimer>0){
            if(swingBox->getGlobalBounds().intersects(ObjectHandler::getBall(0).getGlobalBounds())){
                ObjectHandler::getBall(0).setSpeed(0);
                std::cout << "set speed to 0" << std::endl;
            }
            swingTimer--;
        }
        else{
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
    setPosition(pos.x,pos.y);
}

void Player::input(){
    if(Keyboard::isKeyPressed(Keyboard::Z) && !isSwinging){
        swing();
    }

    //x movement
    if(canMove){
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            accelRight();
            if(!lookingRight){
                setTextureRect(IntRect(0,0,getTexture()->getSize().x,getTexture()->getSize().y));
            }
            lookingRight = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)){
            accelLeft();
            if(lookingRight){
                setTextureRect(IntRect(getTexture()->getSize().x,0,-getTexture()->getSize().x,getTexture()->getSize().y));
            }
            lookingRight = false;
        }
        else{
            deAccel();
        }
    }
    else{
        vel.x = 0;
    }

    //jump
    if(Keyboard::isKeyPressed(Keyboard::C) && isAgainstFloor()){
        jump();
        ObjectHandler::createBall();
    }
}

void Player::swing(){
    isSwinging = true;
    canMove = false;
    swingTimer = 120;

    BoxHandler::createBox();
    swingBox = BoxHandler::getBox(BoxHandler::getBoxCount()-1);
    swingBox->setSize(Vector2f(getGlobalBounds().width,getGlobalBounds().height));
    swingBox->setFillColor(sf::Color::Blue);
    if(lookingRight){
        swingBox->setPosition(pos.x+getGlobalBounds().width,pos.y);
    }
    else swingBox->setPosition(pos.x-getGlobalBounds().width,pos.y);
}

void Player::jump(){
    vel.y = -jumpv;
}
void Player::accelRight(){
    vel.x = clamp(vel.x+acc, -vmax, vmax);
}
void Player::accelLeft(){
    vel.x = clamp(vel.x-acc, -vmax, vmax);
}
void Player::deAccel(){
    vel.x*=deacc;
}
void Player::updateV(){
    //stops tiny speed
    if(vel.x>0 && vel.x<1){
        vel.x=0;
    }
    if(vel.x<0 && vel.x>-1){
        vel.x=0;
    }

    //collision check
    if((isAgainstLeftWall() && vel.x<0) || (isAgainstRightWall() && vel.x>0)){
        vel.x=0;
    }

    //gravity check
    if(!isAgainstFloor()){
        //fix this if for high diagonal v
        if(getBot()+vel.y > WallHandler::getBotWall().getTop()){
            setBot(WallHandler::getBotWall().getTop()-1);
            vel.y=0;
        }
        else{
            vel.y+=gravity;
        }
    }
    else if(vel.y>0){
        vel.y=0;
    }
}

void Player::updateX(){

    pos.x+=vel.x;
    pos.y+=vel.y;
    //wallCollision();
}
