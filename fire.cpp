#include "fire.h"
#include <iostream>
Fire::Fire(World &world_)
{
    world = world_;
    vel =15;
}



int Fire::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{

    vel = 4 + std::rand()%8;
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air ){ particleTypeToMove = air; }
        if(lookUpPrt == oil ){ particleTypeToMove = oil; }
        if(lookUpPrt == water ){ particleTypeToMove = water; }
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == water || lookUpPrt == fire ) //without lookUpPrt == fire (fire is the current particle), fire would disappear when falling down
        {
            return i-1;
        }
    }
    return i-1;
}



bool Fire::moveFire(int& x, int& y)
{

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, 10);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, fire); //particleTypeToMove = air
        interact(particleTypeToMove, x,y);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, 15);
    if(moveBy!= 0)
    {
        updateDownLeft(x, y, moveBy, particleTypeToMove, fire);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, 15);
    if(moveBy!= 0)
    {
        updateDownRight(x, y, moveBy, particleTypeToMove, fire);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, 20);
    if(moveBy!= 0)
    {
        updateRight(x, y, moveBy, particleTypeToMove, fire);
        return 1;
    }



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, 20);
    if(moveBy!= 0)
    {
        updateLeft(x, y, moveBy, particleTypeToMove, fire);
        return 1;
    }
    return 0;

}


bool Fire::interact(char& particleToInteract, int& x, int& y)
{
    if(particleToInteract == water)
    {
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, 10)  ;
        if(moveBy!= 0)
        {
            updateUp(x,y,moveBy, air, smoke);
//            updateDown(x, y, moveBy , air, smoke);
            return 1;
        }
    }

    return 0;
}


void Fire::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{

    if(world.getFlag( x-move_by , y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y+move_by );
}

void Fire::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x-move_by , y)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Fire::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag(x+move_by, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y+move_by);
}

void Fire::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x+move_by , y)=='f')  //cant check cause water cant spread properly
        return;
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}

void Fire::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

void Fire::updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x, y-move_by)=='f')
        return;
    world.setParticle(nextPrt, x, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y-move_by);
}
