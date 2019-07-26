#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

class Particle
{
    public:
        // Particles x and y coordinates with SFML window
        float x = 100;
        float y = 100;
        // Particles horizontal and vertical velocities
        float vx;
        float vy;
        // Particle radius
        float radius = 8;

        // Constructor declaration
        Particle();

        void Update();
        sf::CircleShape Draw();
        void setRandomMovement();
        void setColor(long c);

    private:
        sf::Color color;
        sf::CircleShape shape;
};

class ParticlePool
{
    public:
        int numOfParticles = 20;
        std::vector<Particle> particles;

        // Contructor declaration
        ParticlePool();

        void Update(sf::RenderWindow& window);
};
#endif
