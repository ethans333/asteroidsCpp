#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid {
    public:
        int vertices, x, y, w, vX, vY, windowW, windowH;
        sf::ConvexShape shape;
        Asteroid();

        void draw(sf::FloatRect bndBoxSB);
        void move(float deltaT);
        void manipulate(int vertices, int _w, int _vMax, int _windowW, int _windowH);
        void bounds();
};

#endif