#include <random>
#include <cmath>
#include <iostream>
#include "particles.h"

// Constructor definition
Particle::Particle()
{
    this->setRandomMovement();
}

void Particle::Update()
{
    float screenWidth = 800.f;
    float screenHeight = 600.f;

    if(std::round(x + vx) >= screenWidth || std::round(x + vx) <= 0)
        vx = -vx;
    if(std::round(y + vy) >= screenHeight || std::round(y + vy) <= 0)
        vy = -vy;

    // Add friction
    this->vx = this->vx * 0.998;
    this->vy = this->vy * 0.998;

    this->x = this->x + vx;
    this->y = this->y + vy;

}

sf::CircleShape Particle::Draw()
{

    sf::CircleShape circle;
    circle.setRadius(this->radius);
    circle.setFillColor(this->color);
    circle.setPosition(this->x, this->y);

    return circle;
}

void Particle::setRandomMovement()
{
    std::srand(std::clock());
    // Set random movement between 1 and 10
    float randX = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(10-1)));
    float randY = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(10-1)));

    this->x = (randX*40);
    this->y = (randY*40);

    // If randX or randY < 10 then make negative
    randX = randX - 5;
    randY = randY - 5;

    this->vx = randX;
    this->vy = randY;
}

void Particle::setColor(long c)
{
    this->color = sf::Color(c);
}

ParticlePool::ParticlePool()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> distribution;

    for(int i=0; i < this->numOfParticles; i++){
        Particle p = Particle();
        p.setColor(distribution(gen));
        this->particles.insert(this->particles.end(), p);
    }
}

void ParticlePool::Update(sf::RenderWindow& window)
{
    float distance = 0; // Distance between particles, used to create unit normal vector
    float normal[2] = {0, 0}; // Vector joining both particles p to p2
    float normalVelocities[2] = {0, 0}; // Velocities along normal vector
    float tangentVelocities[2] = {0, 0}; // Velocities perpendicular to normal vector

    for(Particle& p : this->particles){
        p.Update();

        // Find collision
        // Assume particles all have same mass (m1=m2=m3=...)
        for(Particle& p2 : this->particles){
            if(p.x == p2.x && p.y == p2.y)
                continue;

            normal[0] = p2.x - p.x;
            normal[1] = p2.y - p.y;
            distance = std::sqrt(pow(normal[0], 2)+pow(normal[1], 2));

            // BUG: since we only update particles every 1/60 seconds
            // It is possible that particles overlap
            // If this happens and their velocities aren´t enough to escape
            // the overlap then these particles constantly exchange velocities

            if(distance <= (p.radius + p2.radius)){

                // Project velocities into components along normal
                // when m1=m2 exit velocity of m2 is the entry velocity of m1
                // and viceversa

                // normalVelocities[0] is particle p´s velocity in direction of normal vector
                // calculated by dot product of unit normal vector and (p.vx, p.vy)

                // Unit tangent vector is (-normal[1]/distance, normal[0]/distance)

                normalVelocities[0] = (normal[0]/distance)*(p.vx) + (normal[1]/distance)*(p.vy);
                normalVelocities[1] = (normal[0]/distance)*(p2.vx) + (normal[1]/distance)*(p2.vy);
                tangentVelocities[0] = (-normal[1]/distance)*(p.vx) + (normal[0]/distance)*(p.vy);
                tangentVelocities[1] = (-normal[1]/distance)*(p2.vx) + (normal[0]/distance)*(p2.vy);

                // Calculate exit velocities
                // Since m1=m2=m3=... then exit velocity of p in normal direction is equal to
                // to the velocity of p2´s entry velocity in the normal direction and viceversa
                // Tangent velocities are not changed after collision
                p.vx = normalVelocities[1]*normal[0]/distance + tangentVelocities[0]*(-normal[1]/distance);
                p.vy = normalVelocities[1]*normal[1]/distance + tangentVelocities[1]*normal[0]/distance;
                p2.vx = normalVelocities[0]*normal[0]/distance + tangentVelocities[0]*(-normal[1]/distance);
                p2.vy = normalVelocities[0]*normal[1]/distance + tangentVelocities[1]*normal[0]/distance;
            }
        }

        window.draw(p.Draw());
    }
}
