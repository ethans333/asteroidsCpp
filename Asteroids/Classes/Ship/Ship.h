#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>
#include "../Bullet/Bullet.cpp"
#include "../Bullet/Bullet.h"

class Ship {
    public:
        int x, y, w, vMax, v, rV, windowW, windowH, safetyBoxScale = 15;
        float theta = 90.0, vX = 0, vY = 0, a, fireRatePS = .5;
        sf::ConvexShape shape;
        sf::FloatRect bndBox;
        sf::Clock clock;
        std::vector<Bullet> bullets;
        sf::RectangleShape safetyBox;

        Ship(int _x, int _y, int _w, int _vMax, int rV, int _windowW, int _windowH);
        void draw();
        void move(float dt);
        void setVelXY();
        void bounds();
        bool collision(sf::FloatRect bndBox1);
        void shoot();
};

#endif