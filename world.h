#ifndef WORLD_H
#define WORLD_H
#include "particle.h"
#include "vector"
extern const int Hight;
extern const int Width;

extern char flags[];

class World
{
public:


    World();
    void passMatrix(std::vector<Particle*> &matrix_);
    void setParticle(char t, int x, int y);

    char getParticle(int x, int y);

    void setFlag(char f, int x, int y);

    char getFlag(int x, int y);

    void setZ(char f, int x, int y);

    char getZ(int x, int y);

private:
    std::vector<Particle*> matrix;

};

#endif // WORLD_H
