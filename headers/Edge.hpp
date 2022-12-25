#ifndef EDGE
#define EDGE

#include <SFML/Graphics.hpp>
using namespace sf;

class Edge{
    public: uint16_t x1,x2,y1,y2;
    Edge(
        uint16_t a,
        uint16_t b,
        uint16_t c,
        uint16_t d): x1(a),x2(c),y1(b),y2(d) {}
    void drawEdge(RenderTexture&);
};

void Edge::drawEdge(RenderTexture& win){
    Vertex line[] = {
        Vertex(Vector2f(x1,y1)),
        Vertex(Vector2f(x2,y2))
    };
    win.draw(line, 2, sf::Lines);
}

class visibleRay{
    public: float angle,x,y;
    visibleRay(float a,float b,float c):angle(a),x(b),y(c){}
    bool operator >(visibleRay& R) noexcept { return this->angle > R.angle; }
    bool operator <(visibleRay& R) noexcept { return this->angle <= R.angle; }
};

#endif //EDGE