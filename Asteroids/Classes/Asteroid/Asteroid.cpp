#include <iostream>
using namespace std;
#include "Asteroid.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

int zeroOrOne() {
    int n = 0;
    while (n == 0) {
        n = (rand() % 3) -1;
    }
    return n;
}

Asteroid::Asteroid() {
    vertices = 0;
    x = 0;
    y = 0;
    w = 0;
    vX = 0;
    vY = 0;
    windowW = 0;
    windowH = 0;
}

void Asteroid::manipulate(int _vertices, int _w, int _vMax, int _windowW, int _windowH) {
    vertices = _vertices;
    w = _w;
    vX = (rand() % _vMax) * zeroOrOne();
    vY = (rand() % _vMax) * zeroOrOne();
    windowW = _windowW;
    windowH = _windowH;
}

void Asteroid::draw(sf::FloatRect bndBoxSB) {
    shape.setPointCount(vertices);

    int arrVertices[][2] = {
        {x, y},
        {x+(rand() % w/2), y-(rand() % w/2)},
        {x+w, y},
        {x+w, y+w},
        {x+(rand() % w/2), y+w+(rand() % w/2)},
        {x, y+w}
    };
    
    for (int i = 0; i < sizeof(arrVertices)/sizeof(arrVertices[0]); i++) {
        shape.setPoint(i, sf::Vector2f(arrVertices[i][0], arrVertices[i][1]));
    }

    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::White);

    shape.setPosition(sf::Vector2f(w + (rand() % (windowW - w*2)), w + (rand() % (windowH - w*2))));
    shape.setOrigin(w/2, w/2);

    sf::FloatRect bndBox = shape.getGlobalBounds();
    while (bndBox.intersects(bndBoxSB)) {
        shape.setPosition(sf::Vector2f(w + (rand() % (windowW - w*2)), w + (rand() % (windowH - w*2))));
        shape.setOrigin(w/2, w/2);
        bndBox = shape.getGlobalBounds();
    }
}

void Asteroid::bounds() {
    if (shape.getPosition().x > windowW + w) {
        shape.setPosition(sf::Vector2f(0, shape.getPosition().y));
    } else if (shape.getPosition().x < 0 - w) {
        shape.setPosition(sf::Vector2f(windowW, shape.getPosition().y));
    }

    if (shape.getPosition().y > windowH + w) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, 0));
    } else if (shape.getPosition().y < 0 - w) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, windowH));
    }
}

void Asteroid::move(float deltaT) {
    bounds();
    shape.move(sf::Vector2f(vX * deltaT, vY * deltaT));
}