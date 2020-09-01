#include "Object.h"

Object::Object(sf::Texture& t) {
    sprite = sf::Sprite(t);
    width = t.getSize().x;
    height = t.getSize().y;

    for (int i = 0; i < 6; i++) {
        hitLines[i].color = sf::Color::Green;
    }
}

bool Object::isCornerIntersect(Wall& a) {
    if ((getLeft() == a.getRight() || getRight() == a.getLeft()) &&
        (getBot() == a.getTop() || getTop() == a.getBot())) {
            return true;
    }
    return false;
}

bool Object::isAgainstTop(Wall& a) {
    return segmentIntersectsRectangle(sprite.getGlobalBounds(),
                                      sf::Vector2f(a.getLeft() + 1, a.getTop()),
                                      sf::Vector2f(a.getRight() - 1, a.getTop())
                                      );
}
bool Object::isAgainstBot(Wall& a) {
    return segmentIntersectsRectangle(sprite.getGlobalBounds(),
                                      sf::Vector2f(a.getLeft() + 1, a.getBot()),
                                      sf::Vector2f(a.getRight() - 1, a.getBot())
                                      );
}
bool Object::isAgainstLeft(Wall& a) {
    return segmentIntersectsRectangle(sprite.getGlobalBounds(),
                                      sf::Vector2f(a.getLeft(), a.getTop() + 1),
                                      sf::Vector2f(a.getLeft(), a.getBot() - 1)
                                      );
}
bool Object::isAgainstRight(Wall& a) {
    return segmentIntersectsRectangle(sprite.getGlobalBounds(),
                                      sf::Vector2f(a.getRight() + 1, a.getTop() + 1),
                                      sf::Vector2f(a.getRight() + 1, a.getBot() - 1)
                                      );
}
bool Object::isAgainst(Wall& a) {
    if (isAgainstTop(a) || isAgainstBot(a) || isAgainstLeft(a) || isAgainstRight(a)) {
        return true;
    }
    return false;
}

bool Object::isAgainstFloor() {
    return isAgainstTop(WallHandler::getBotWall());
}

bool Object::isAgainstLeftWall() {
    return isAgainstRight(WallHandler::getLeftWall());
}

bool Object::isAgainstRightWall() {
    return isAgainstLeft(WallHandler::getRightWall());
}

bool Object::isAgainstCeiling() {
    return isAgainstBot(WallHandler::getTopWall());
}

bool Object::isAgainstAnyX() {
    if (isAgainstLeftWall() || isAgainstRightWall()) {
        return true;
    }

    for (int i = 0; i < WallHandler::getExtraWallCount(); i++) {
        if (isAgainstLeft(WallHandler::getExtraWall(i)) || isAgainstRight(WallHandler::getExtraWall(i))) {
            return true;
        }
    }
    return false;
}

bool Object::isAgainstAnyY() {
    if (isAgainstCeiling() || isAgainstFloor()) {
        return true;
    }

    for (int i = 0; i < WallHandler::getExtraWallCount(); i++) {
        if (isAgainstTop(WallHandler::getExtraWall(i)) || isAgainstBot(WallHandler::getExtraWall(i))) {
            return true;
        }
    }

    return false;
}

bool Object::isAgainstAny() {
    if (isAgainstAnyX() || isAgainstAnyY()) {
        return true;
    }
    return false;
}

bool Object::isCornerInterAny() {




}

//from https://en.sfml-dev.org/forums/index.php?topic=23624.0
bool Object::segmentIntersectsRectangle(const sf::FloatRect& rect,
    const sf::Vector2f& a_p1, const sf::Vector2f& a_p2)
{
    // Find min and max X for the segment
    int minX = std::min(a_p1.x, a_p2.x);
    int maxX = std::max(a_p1.x, a_p2.x);

    // Find the intersection of the segment's and rectangle's x-projections
    if (maxX > rect.left + rect.width) {
        maxX = rect.left + rect.width;
    }

    if (minX < rect.left) {
        minX = rect.left;
    }

    // If Y-projections do not intersect then there's no intersection
    if (minX > maxX) { return false; }

    // Find corresponding min and max Y for min and max X we found before
    int minY = a_p1.y;
    int maxY = a_p2.y;

    int dx = a_p2.x - a_p1.x;
    if (std::abs(dx) > 0.0000001f) {
        int k = (a_p2.y - a_p1.y) / dx;
        int b = a_p1.y - k * a_p1.x;
        minY = k * minX + b;
        maxY = k * maxX + b;
    }

    if (minY > maxY) {
        std::swap(minY, maxY);
    }

    // Find the intersection of the segment's and rectangle's y-projections
    if (maxY > rect.top + rect.height) {
        maxY = rect.top + rect.height;
    }

    if (minY < rect.top) {
        minY = rect.top;
    }

    // If Y-projections do not intersect then there's no intersection
    if (minY > maxY) { return false; }
    return true;
}

inline float Dot(const sf::Vector2<float>& a,const sf::Vector2<float>& b)                        { return (a.x*b.x) + (a.y*b.y); }
inline float PerpDot(const sf::Vector2<float>& a,const sf::Vector2<float>& b)                    { return (a.y*b.x) - (a.x*b.y); }

bool LineCollision( const sf::Vector2<float>& A1, const sf::Vector2<float>& A2,
                    const sf::Vector2<float>& B1, const sf::Vector2<float>& B2,
                    sf::Vector2<float>& output                         )
{
    sf::Vector2<float> a(A2-A1);
    sf::Vector2<float> b(B2-B1);

    float f = PerpDot(a,b);
    if (!f)      // lines are parallel
        return false;

    sf::Vector2<float> c(B2-A2);
    float aa = PerpDot(a,c);
    float bb = PerpDot(b,c);

    if (f < 0)
    {
        if (aa > 0)     return false;
        if (bb > 0)     return false;
        if (aa < f)     return false;
        if (bb < f)     return false;
    }
    else
    {
        if (aa < 0)     return false;
        if (bb < 0)     return false;
        if (aa > f)     return false;
        if (bb > f)     return false;
    }

    output = ((B2 - B1) * (1 - (aa / f))) + B1;
    return true;
}

bool Object::collisionDist(RectangleShape r, int &returnDist, Vector2i &tpCoord) {
    FloatRect bound = r.getGlobalBounds();
    sf::VertexArray sides = sf::VertexArray(sf::Lines, 4);
    sf::Vector2f hitPos[3];
    int sideC = 0;
    bool L[3];
    float dist[3] = {0, 0, 0};

    auto setHitLinePos = [&](int l1p1, int l1p2, int l2p1, int l2p2, int l3p1, int l3p2)
    {
        hitLines[0].position = sf::Vector2f(l1p1, l1p2);
        hitLines[2].position = sf::Vector2f(l2p1, l2p2);
        hitLines[4].position = sf::Vector2f(l3p1, l3p2);

        for (int i = 0; i < 5; i += 2) {
            hitLines[i+1].position = sf::Vector2f(hitLines[i].position + sf::Vector2f(vel));
        }
    };

    auto setSide = [&](char s) { //*2+1 wont work if more than 2 sides
        if (s == 'T') {
            sides[sideC*2].position = sf::Vector2f(bound.left, bound.top);
            sides[sideC*2+1].position = sf::Vector2f(bound.left + bound.width, bound.top);
        }
        else if (s == 'B') {
            sides[sideC*2].position = sf::Vector2f(bound.left, bound.top + bound.height);
            sides[sideC*2+1].position = sf::Vector2f(bound.left+bound.width, bound.top+bound.height);
        }
        else if (s == 'L') {
            sides[sideC*2].position = sf::Vector2f(bound.left, bound.top);
            sides[sideC*2+1].position = sf::Vector2f(bound.left, bound.top + bound.height);
        }
        else if (s == 'R') {
            sides[sideC*2].position = sf::Vector2f(bound.left + bound.width, bound.top);
            sides[sideC*2+1].position = sf::Vector2f(bound.left + bound.width, bound.top + bound.height);
        }
        sideC++;
    };

    auto checkCol = [&]() {
        for (int i = 0; i < 3; i++) {
            L[i] = LineCollision(hitLines[i*2].position, hitLines[i*2+1].position, sides[0].position, sides[1].position, hitPos[i]);

            if (!L[i] && sideC == 2) {
                L[i] = LineCollision(hitLines[i*2].position, hitLines[i*2+1].position, sides[2].position, sides[3].position, hitPos[i]);
            }
        }
    };

    int halfH = getTop() + (height) / 2;
    int halfW = getLeft() + (width) / 2;

    if (vel.x > 0 && vel.y == 0) {
        setHitLinePos(getRight(), getBot(),
                      getRight(), halfH,
                      getRight(), getTop());
        setSide('L');
    }
    else if (vel.x > 0 && vel.y < 0) {
        setHitLinePos(getRight(), getBot(),
                      getRight(), getTop(),
                      getLeft(), getTop());
        setSide('L');
        setSide('B');
    }
    else if (vel.x == 0 && vel.y < 0) {
        setHitLinePos(getRight(), getTop(),
                      halfW, getTop(),
                      getLeft(), getTop());
        setSide('B');
    }
    else if (vel.x < 0 && vel.y < 0) {
        setHitLinePos(getRight(), getTop(),
                      getLeft(), getTop(),
                      getLeft(), getBot());
        setSide('R');
        setSide('B');
    }
    else if (vel.x < 0 && vel.y == 0) {
        setHitLinePos(getLeft(), getTop(),
                      getLeft(), halfH,
                      getLeft(), getBot());
        setSide('R');
    }
    else if (vel.x < 0 && vel.y > 0) {
        setHitLinePos(getLeft(), getTop(),
                      getLeft(), getBot(),
                      getRight(), getBot());
        setSide('R');
        setSide('T');
    }
    else if (vel.x == 0 && vel.y > 0) {
        setHitLinePos(getLeft(), getBot(),
                      halfW, getBot(),
                      getRight(), getBot());
        setSide('T');
    }
    else if (vel.x > 0 && vel.y > 0) {
        setHitLinePos(getLeft(), getBot(),
                      getRight(), getBot(),
                      getRight(), getTop());
        setSide('L');
        setSide('T');
    }

    checkCol();

    if (L[0] || L[1] || L[2]) {
        //compare distances and set the pos to which ever is closest
        for (int i = 0; i < 3; i++) {
            if (L[i]) {
                dist[i] = sqrt(pow((hitPos[i].x-hitLines[i*2].position.x), 2) + pow((hitPos[i].y-hitLines[i*2].position.y), 2));
            }
        }

        float minDist = 0;
        for (int i = 0; i < 3; i++) {
            if (dist[i] != 0 && (minDist == 0 || dist[i] < minDist)) {
                minDist = dist[i];
            }
        }

        //sets right hitpos depending on which is closest
        for (int i = 0; i < 3; i++) {
            if (minDist == dist[i]) {
                tpCoord = Vector2i(hitPos[i]-(hitLines[i*2].position - (Vector2f)pos));
                break;
            }
        }
        returnDist = minDist;
        return true;
    }
    return false;
}

sf::Vector2i Object::getPos() {
    return pos;
}

sf::Vector2i Object::getVel() {
    return vel;
}

void Object::draw(sf::RenderTarget& t) {
    t.draw(sprite);
}

int Object::getTop() {
    return pos.y;
}

int Object::getBot() {
    return pos.y + height;
}

int Object::getLeft() {
    return pos.x;
}

int Object::getRight() {
    return pos.x + width;
}

void Object::setBot(int a) {
    pos.y = a - height;

}

void Object::setSca(float a) {
    sprite.setScale(a, a);
    scale = a;
    updateSize();
}

void Object::updateSize() {
    width = sprite.getGlobalBounds().width;
    height = sprite.getGlobalBounds().height;
}
