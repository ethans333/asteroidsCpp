#include <iostream>
using namespace std;
#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Bullet/Bullet.h"
#include <vector>

Ship::Ship(int _x, int _y, int _w, int _vMax, int _rV, int _windowW, int _windowH) {
    x = _x;
    y = _y;
    w = _w;
    vMax = _vMax;
    v = 0;
    a = vMax / 10;
    rV = _rV;
    windowW = _windowW;
    windowH = _windowH;
}

void Ship::draw() {
    shape.setPointCount(3);

    shape.setPoint(0, sf::Vector2f(x - w, y));
    shape.setPoint(1, sf::Vector2f(x + w, y));
    shape.setPoint(2, sf::Vector2f(x, y - w*2));

    shape.setFillColor(sf::Color::White);

    shape.setPosition(sf::Vector2f(windowW / 2, windowH / 2));
    shape.setOrigin(0, -w);

    safetyBox.setSize(sf::Vector2f(w*safetyBoxScale, w*safetyBoxScale));
    safetyBox.setPosition(sf::Vector2f(windowW / 2 - w*safetyBoxScale/2, windowH / 2 - w*safetyBoxScale/2));
    safetyBox.setFillColor(sf::Color::Transparent);
    safetyBox.setOutlineColor(sf::Color::Transparent);
}

float boundTo360(float theta) {
    if (theta == 360) {
        theta = 0;
    } else if (theta < 0) {
        theta += 360;
    }
    return theta;
}

float getRadians(float theta) {
    return (theta * M_PI) / 180; 
}

float getVX (float radians) {
    return cos(radians);
}

float getVY (float radians) {
    return sin(radians);
}

void Ship::setVelXY() {
    float radians = getRadians(theta);
    vX = getVX(radians) * v;
    vY = -getVY(radians) * v;
    
}

void Ship::bounds() {
    if (shape.getPosition().x > windowW) {
        shape.setPosition(sf::Vector2f(0, shape.getPosition().y));
    } else if (shape.getPosition().x < 0) {
        shape.setPosition(sf::Vector2f(windowW, shape.getPosition().y));
    }

    if (shape.getPosition().y > windowH) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, 0));
    } else if (shape.getPosition().y < 0) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, windowH));
    }
}

void Ship::move(float deltaT) {
    shape.move(sf::Vector2f(vX * deltaT, vY * deltaT));
    bndBox = shape.getGlobalBounds();

    shoot();
    bounds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && v < vMax) {
        v += a;
    } else if (v > 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        v -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        shape.rotate(-rV);
        theta += rV;
        theta = boundTo360(theta);
        setVelXY();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        shape.rotate(rV);
        theta -= rV;
        theta = boundTo360(theta);
        setVelXY();
    }
}

void Ship::shoot() {
    sf::Time elapsedTime = clock.getElapsedTime();
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) &&
     elapsedTime.asSeconds() > fireRatePS) {
        Bullet bullet = Bullet();
        bullet.manipulate(shape.getPosition().x, shape.getPosition().y, 2, vX, vY, 200, windowW, windowH, theta);
        bullet.draw();
        bullets.push_back(bullet);
        clock.restart();
    }
}

bool Ship::collision(sf::FloatRect bndBox1) {
    bool shipHit = bndBox.intersects(bndBox1);
    if (shipHit) {
        shape.setFillColor(sf::Color::Red);
    } else {
        shape.setFillColor(sf::Color::White);
    }
    return shipHit;
}
