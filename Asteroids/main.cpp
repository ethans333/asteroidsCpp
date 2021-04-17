#include <iostream>
using namespace std;
#include <vector>
#include <SFML/Graphics.hpp>
#include "Classes/Window/Window.cpp"
#include "Classes/Window/Window.h"
#include "Classes/Ship/Ship.cpp"
#include "Classes/Ship/Ship.h"
#include "Classes/Asteroid/Asteroid.cpp"
#include "Classes/Asteroid/Asteroid.h"

void endGame() {
    std::exit(42);
}

int main()
{
    Window win(500, 500);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(win.width, win.height), "Asteriods", sf::Style::Default, settings);

    window.setFramerateLimit(60);
    sf::Clock dtClock;
    float dt = 0;

    Ship ship(0, 0, 10, 125, 5, win.width, win.height);
    ship.draw();

    int numOfAsteroids = 12; 
    std::vector<Asteroid> asteroids;
    
    for (int i = 0; i < numOfAsteroids; i++) {
        Asteroid asteroid = Asteroid();
        asteroid.manipulate(6, 50, 25, win.width, win.height);
        asteroid.draw(ship.safetyBox.getGlobalBounds());
        asteroids.push_back(asteroid);
    }

    while (window.isOpen()) {
        sf::Event event;

    //Move
        ship.move(dt);

        for (int i = 0; i < asteroids.size(); i++) {
            asteroids[i].move(dt);
            sf::FloatRect asBndBox = asteroids[i].shape.getGlobalBounds();
            if (ship.collision(asBndBox)) {
                endGame();
            }

            for (int j = 0; j < ship.bullets.size(); j++) {
                if (ship.bullets[j].asCollision(asBndBox)) {
                    asteroids.erase(asteroids.begin() + i);
                    ship.bullets.erase(ship.bullets.begin() + j);
                    numOfAsteroids -= 1;
                    if (numOfAsteroids == 0) {
                        endGame();
                    }
                }
            }
        }

        for (int i = 0; i < ship.bullets.size(); i++) {
            ship.bullets[i].move(dt);
            if (ship.bullets[i].outOfBounds()) {
                ship.bullets.erase(ship.bullets.begin() + i);
            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        dt = dtClock.restart().asSeconds();
        window.clear();

    //Draw
        window.draw(ship.shape);
        window.draw(ship.safetyBox);

        for (int i = 0; i < asteroids.size(); i++) {
            window.draw(asteroids[i].shape);
        }

        for (int i = 0; i < ship.bullets.size(); i++) {
            window.draw(ship.bullets[i].shape);
        }

        window.display();
    }

    return 0;
}