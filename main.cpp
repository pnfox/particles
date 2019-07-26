/*
*   Particle collisions physics using SFML
*
*
*   Created by Patrick Fox, 25th July 2019
*   http://pnfox.com
*/

#include <iostream>
#include "particles.h"

using namespace std;

int main(int argc, char *argv[]) {

    const sf::VideoMode screenSize = sf::VideoMode(800, 600, 24);
    sf::RenderWindow window(screenSize, "SFML Particles");
    window.setFramerateLimit(60);
    window.setActive(false);
    window.requestFocus();

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);

    ParticlePool particles = ParticlePool();

    // Main Loop here
    while(window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;


        if(timeSinceLastUpdate < timePerFrame)
            continue;

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        window.clear();


        particles.Update(window);

        window.display();

        timeSinceLastUpdate = sf::Time::Zero;
    }

    return 0;
}
