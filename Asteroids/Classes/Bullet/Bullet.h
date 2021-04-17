#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
    public:
        int x, y, r, vX, vY, vMin, windowW, windowH;
        sf::CircleShape shape;
        sf::FloatRect bndBox;

        Bullet();
        void manipulate(int _x, int _y, int _r, int _vX, int _vY, int _vMin, int _windowW, int _windowH, int _theta);
        void draw();
        void move(float deltaT);
        bool outOfBounds();
        bool asCollision(sf::FloatRect bndBox1);
};

#endif