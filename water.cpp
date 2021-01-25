#include "water.h"
#include <iostream>
Water::Water(World &world_)
{
    world = world_;
    vel =15;
}

int Water::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{

 //vel = 10 + std::rand()%20;
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        char flag = world.getFlag(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air){}
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == water)
        {
            return i-1;
        }
    }
    return i-1;
}

void Water::moveWater(int& x, int& y)
{

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, 10);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, air, water);
        return;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, 15);
    if(moveBy!= 0)
    {
        updateDownLeft(x, y, moveBy, air, water);
        return;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, 15);
    if(moveBy!= 0)
    {
        updateDownRight(x, y, moveBy, air, water);
        return;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, 20);
    if(moveBy!= 0)
    {
        updateRight(x, y, moveBy, air, water);
        return;
    }



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, 20);
    if(moveBy!= 0)
    {
        updateLeft(x, y, moveBy, air, water);
        return;
    }



}

void Water::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{

    if(world.getFlag( x-move_by , y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y+move_by );
}

void Water::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x-move_by , y)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Water::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag(x+move_by, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y+move_by);
}

void Water::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x+move_by , y)=='f')  //cant check cause water cant spread properly
        return;
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}

void Water::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}
