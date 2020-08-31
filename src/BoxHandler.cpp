#include "BoxHandler.h"

namespace BoxHandler {
    const int maxBox = 10;
    int boxCount = 0;
    std::vector<sf::RectangleShape> box;
}

void BoxHandler::createBox() {
    if (boxCount < maxBox) {
        boxCount++;
        box.resize(boxCount);
    }
    else std::cout << "too many boxes" << std::endl;
}

int BoxHandler::getBoxCount() {
    return boxCount;
}

sf::RectangleShape* BoxHandler::getBox(int i) {
    return &box[i];
}

void BoxHandler::destroyBox(sf::RectangleShape* address) {
    int i;
    for (i = 0; i < boxCount; i++) {
         if(address == &box[i]) {
            std::cout << "triggered i = " << i << std::endl;
            //std::cout << address << std::endl;
            //std::cout << &box[i] << std::endl;
            break;
        }
    }
    box.erase(box.begin() + i);
    boxCount--;
}

/*
bool BoxHandler::checkCol(Object* a, Object b){
    if(a->getGlobalBounds().intersects(b.getGlobalBounds())){
        return true;
    }
}
*/
