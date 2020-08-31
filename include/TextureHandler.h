#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H
#include <SFML/Graphics.hpp>

using namespace sf;

namespace TextureHandler
{
    void init();
    Texture& getBallTexture();
    Texture& getPlayerTexture();
};



#endif // TEXTUREHANDLER_H
