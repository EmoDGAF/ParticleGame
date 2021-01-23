#include "world.h"
#include <iostream>

World::World()
{

}

void World::passMatrix(std::vector<Particle*> &matrix_)
{
    matrix = matrix_;
    std::cout << "matrix size: " << matrix.size() << std::endl;

}


void World::setParticle(char t, int x, int y)
{
    matrix[x+ y*Hight]->settype(t);
}

char World::getParticleType(int x, int y)
{
    //return matrix[x+ y*Hight]->getType();
    return matrix[x+ y*Hight]->getType();
}

Particle* World::getParticle(int x, int y)
{
    //return matrix[x+ y*Hight]->getType();
    return matrix[x+ y*Hight];
}

void World::setFlag(char f, int x, int y)
{
    //matrix[x+ y*Hight]->setFlag(f);
    flags[x+ y*Hight] = f;
}

char World::getFlag(int x, int y)
{
    //return matrix[x+ y*Hight]->getFlag();
    return flags[x+ y*Hight];
}

 
