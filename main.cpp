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
    WallHandler::createExtraWall(Vector2f(300,645),Vector2f(200,25));
    WallHandler::createExtraWall(Vector2f(780,645),Vector2f(200,25));
    WallHandler::createExtraWall(Vector2f(540,200),Vector2f(200,25));

    while (win.isOpen())
    {
        #ifndef DEBUG
        std::cerr << "frame: " << frame << std::endl;
        std::cerr << "angle: " << (ObjectHandler::getBall(0).angle) << std::endl;
        std::cerr << "bx: " << ObjectHandler::getBall(0).pos.x << std::endl;
        std::cerr << "by: " << ObjectHandler::getBall(0).pos.y << std::endl;
        std::cerr << "bvx: " << ObjectHandler::getBall(0).vel.x << std::endl;
        std::cerr << "bvy: " << ObjectHandler::getBall(0).vel.y << std::endl;
        std::cerr << "angle: " << ObjectHandler::getBall(0).angle << std::endl;
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

