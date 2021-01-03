#include "world.h"

World::World()
{

}

void World::setParticle(char t, int x, int y)
{
    matrix[x+ y*Hight] = t;
}

char World::getParticle(int x, int y)
{
    return matrix[x+ y*Hight];
}

void World::setFlag(char f, int x, int y)
{
    flags[x+ y*Hight] = f;
}

char World::getFlag(int x, int y)
{
    return flags[x+ y*Hight];
}
