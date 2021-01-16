#include <ObjectHandler.h>
#include <DrawHandler.h>

int frame = 1;
int screenwidth = 1280;
int screenheight = 720;

RenderWindow win(VideoMode(screenwidth, screenheight), "SFML Test");

int main()
{
    win.setFramerateLimit(60);
    TextureHandler::init();
    ObjectHandler::createPlayer();
    ObjectHandler::createBall();
    WallHandler::createMainWalls();

    while (win.isOpen())
    {
        #ifdef DEBUG
        std::cerr << "frame: " << frame << std::endl;
        std::cerr << "angle: " << (ObjectHandler::getBall(0).angle) << std::endl;
        std::cerr << "bx: " << ObjectHandler::getBall(0).getPos().x << std::endl;
        std::cerr << "by: " << ObjectHandler::getBall(0).getPos().y << std::endl;
        std::cerr << "bvx: " << ObjectHandler::getBall(0).getVel().x << std::endl;
        std::cerr << "bvy: " << ObjectHandler::getBall(0).getVel().x << std::endl;
        std::cerr << std::endl;
        #endif

        Event e;
        while (win.pollEvent(e)) {
            switch(e.type)
            {
                case Event::Closed:
                {
                    win.close();
                }
            }
        }

        ObjectHandler::updateAllObjects();
        DrawHandler::drawAll();
        win.draw(ObjectHandler::getBall(0).hitLines);
        win.draw(ObjectHandler::getPlayer(0).hitLines);
        win.display();

        if (frame<60) {
            frame++;
        }
        else {
            frame=0;
        }

        if (ObjectHandler::isBallOutOfBounds()) {
            exit(0);
        }
    }

    win.close();
    return 0;
}

