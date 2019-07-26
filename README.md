## Particle Physics Collisions with SFML

    This program draws particles with random velocities into a SFML window.
    Particles collide with each other and window boundaries. There is a small
    friction coefficient and particles are assumed to have the same mass.

    Two classes inside `particles.cpp` source file, ParticlePool and Particle.
    ParticlePool contructor creates multiple Particle´s and stores them in a C++ vector,
    which is then accessed to update movement and detect collisions. Details on how
    collision velocities are calculated are described in source code comments.

    Written in C++.

    Only built on Linux so far, can´t guarantee it will work on other systems
    although no majoy changes will be needed.

    Version: 1.0

### Build and running

1. Clone the repository

2. Run `make` then `./particles`

Created by Patrick Fox, 25th July 2019

