#include "WallHandler.h"

namespace WallHandler{
    int mainWallCount = 0;
    int extraWallCount = 0;
    const int maxMainWall = 4;
    const int maxExtraWall = 4;
    std::vector<Wall> mainwall; //0=top 1=bot 2=left 3=right
    std::vector<Wall> extrawall;
}

void WallHandler::createMainWall(){
    if(mainWallCount < maxMainWall){
        mainWallCount++;
        mainwall.resize(mainWallCount);
        std::cout << "main wall made" << std::endl;
    }
}

void WallHandler::createExtraWall(Vector2f pos, Vector2f size){
    if(extraWallCount < maxExtraWall){
        extraWallCount++;
        extrawall.resize(extraWallCount);
        std::cout << "extra wall made" << std::endl;
        extrawall[extraWallCount-1].setSize(size);
        extrawall[extraWallCount-1].setPosition(pos);
    }
}

void WallHandler::createTopWall(){
    mainwall[0].setSize(Vector2f(screenwidth, 50));
}

void WallHandler::createBotWall(){
    mainwall[1].setSize(Vector2f(screenwidth, 50));
    mainwall[1].setPosition(0,screenheight-50);
}

void WallHandler::createLeftWall(){
    mainwall[2].setSize(Vector2f(50, screenheight));
}

void WallHandler::createRightWall(){
    mainwall[3].setSize(Vector2f(50, screenheight));
    mainwall[3].setPosition(screenwidth-50,0);
}

void WallHandler::createMainWalls(){
    for(int i=0;i<4;i++){
        createMainWall();
    }
    createTopWall();
    createBotWall();
    createLeftWall();
    createRightWall();
}

Wall& WallHandler::getMainWall(int i){
    return mainwall[i];
}

Wall& WallHandler::getExtraWall(int i){
    return extrawall[i];
}

int WallHandler::getExtraWallCount(){
    return extraWallCount;
}

Wall& WallHandler::getTopWall(){
    return mainwall[0];
}

Wall& WallHandler::getBotWall(){
    return mainwall[1];
}

Wall& WallHandler::getLeftWall(){
    return mainwall[2];
}

Wall& WallHandler::getRightWall(){
    return mainwall[3];
}


