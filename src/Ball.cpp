#include "Ball.h"

Ball::Ball(): Object (TextureHandler::getBallTexture()) {
    pos.x=800;
    pos.y=439;
    move(pos.x,pos.y);
}

void Ball::angleupdate(){

    //fix corner edge case (see picture). if corner hits corner but is going wrong direction
    //if it is against x and y for two rectangles (concave) OR corner intersects extra (convex) flip angle
    if(isAgainstAnyX() & isAgainstAnyY()){
        angle+=180;
        std::cout<< "first 180+" <<std::endl;
        return;
    }
    else{
        for(int i = 0;i<WallHandler::getExtraWallCount();i++){
            if(isCornerIntersect(WallHandler::getExtraWall(i))){
                angle+=180;
                std::cout << "second 180+" <<std::endl;
                return;
            }
        }
    }


    if(isAgainstAnyX()){
        std::cout << "anyx" << std::endl;
        angle=180-angle;
    }
    else if(isAgainstAnyY()){
        std::cout << "anyy" << std::endl;
        angle=360-angle;
    }
}

void Ball::update(){
    angleupdate();

    bool angleC = true;
    while(angleC){
        if(angle >= 360){
            angle-=360;
        }
        else if(angle<0){
            angle+=360;
        }
        else{
            angleC=false;
        }
    }



    vel.x=cosd(angle)*speed;
    vel.y=-sind(angle)*speed;

    int dist;
    int mindist = 0;
    Vector2i linePos;
    Vector2i minLinePos;

    for(int i=0; i<4; i++){
        bool hit = collisionDist(WallHandler::getMainWall(i),dist,linePos);
        std::cout << "dist: " << dist << std::endl;
        if(hit & (mindist == 0 || dist < mindist)){
            mindist = dist;
            minLinePos = linePos;
        }


        if(i<WallHandler::getExtraWallCount()){
            bool hit2 = collisionDist(WallHandler::getExtraWall(i),dist,linePos);
            if(hit2 & (mindist == 0 || dist < mindist)){
                mindist = dist;
                minLinePos = linePos;
            }
        }
    }




    //std::cout<< "right line posx = " <<rightLinePos.x << std::endl;
    //std::cout<< "right line posy = " <<rightLinePos.y << std::endl;

    if(mindist != 0){
        std::cout << "mindist" << mindist << std::endl;
        std::cout <<"minLinePos.x" << minLinePos.x << std::endl;
        pos=minLinePos;
    }
    else{
        pos+=vel;
    }
    setPosition((float)pos.x,(float)pos.y);
}

void Ball::setSpeed(int s){
    speed = s;
}

void Ball::addSpeed(int s){
    speed += s;
}
