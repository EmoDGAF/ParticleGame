#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>


class Particle
{
public:
    Particle();

    unsigned int fireLifetime;
    unsigned int smokeLifetime;
    char type;
    int x;
    int y;
    std::vector<int> prevPos_v;
public:
    bool decreaseFireLifetime();
    bool decreaseSmokeLifetime();
    void settype(char t);
    char getType();
    unsigned int getLifetimeCount();
};

#endif // PARTICLE_H
