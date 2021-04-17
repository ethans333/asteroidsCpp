#include <iostream>
using namespace std;
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

Bullet::Bullet() {
    x = 0;
    y = 0;
    r = 0;
    vX = 0;
    vY = 0;
    windowH = 0;
    windowH = 0;
}

int incrV (int v, bool isX, int vMin, int theta) {
    if (v < vMin && isX) {
        v = cos(theta*M_PI/180) * vMin;
    } else if (v < vMin && !isX) {
        v = -sin(theta*M_PI/180) * vMin;
    }

    return v;
}

void Bullet::manipulate(int _x, int _y, int _r, int _vX, int _vY, int _vMin, int _windowW, int _windowH, int _theta) {
    x = _x;
    y = _y;
    r = _r;
    vX = incrV(_vX, true, _vMin, _theta);
    vY = incrV(_vY, false, _vMin, _theta);
    vMin = _vMin;
    windowW = _windowW;
    windowH = _windowH;
}

void Bullet::draw() {
    shape.setRadius(r);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2f(x, y));
    shape.setOrigin(0, 0);
}

void Bullet::move(float deltaT) {
    shape.move(sf::Vector2f(vX * deltaT, vY * deltaT));
    bndBox = shape.getGlobalBounds();
}

bool Bullet::outOfBounds() {
    if (
        shape.getPosition().x > windowW + r*2 ||
        shape.getPosition().x < -r*2 ||
        shape.getPosition().y + r*2  > windowH ||
        shape.getPosition().y < -r*2) 
    {
        return true;
    } else {
        return false;
    }
}

bool Bullet::asCollision(sf::FloatRect bndBox1) {
    bool bulletHit = bndBox.intersects(bndBox1);
    /*
    if (bulletHit) {
        cout << "BOOM!" << endl;
    } else {
        //
    }
    */
    return bulletHit;
}