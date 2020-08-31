#include "TextureHandler.h"

namespace TextureHandler{
    Texture ball;
    Texture player;
}

void TextureHandler::init(){
    ball.loadFromFile("images/ball.png");
    player.loadFromFile("images/player.png");
}

Texture& TextureHandler::getBallTexture(){
    return ball;
}

Texture& TextureHandler::getPlayerTexture(){
    return player;
}
