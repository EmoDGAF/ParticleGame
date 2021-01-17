#include "sand.h"
#include <iostream>

Sand::Sand(World& world_)
{
    world = world_;
    vel = 10 ; // sand speed
    velSandInWater =2;
}

int Sand::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{
    int i;
    char lookUpPrt;
    for (i = 1; i < vel; ++i)
    {
        lookUpPrt = world.getParticle(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air){  }
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == fire)
        {
            return i-1;
        }
    }
    return i-1;
}
 
bool Sand::moveSand(int& x, int& y)
{
    //std::cout << "moveSand" << std::endl;
 
    int moveBy=0;
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, air, sand);
        return 1;
    }


        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel);
        if(moveBy!= 0)
        {
            updateDown(x, y, moveBy, air, sand);
            return 1;
        }
        /*down sides*/



        moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, vel);
        if(moveBy!= 0)
        {
            updateDownLeft(x, y, moveBy, air, sand);
            return 1;
        }


        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, vel);
        if(moveBy!= 0)
        {
            updateDownRight(x, y, moveBy, air, sand);
            return 1;
        }


    return 0;
}

bool Sand::moveSandInWater(int &x, int &y)
{

    int moveBy;

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, velSandInWater);

    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, water, sand);
        return 1;
    }

    /*down sides*/

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSandInWater);
    if(moveBy!= 0)
    {
        updateDownLeft(x, y, moveBy, water, sand);
        return 1;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSandInWater);
    if(moveBy!= 0)
    {
        updateDownRight(x, y, moveBy, water, sand);
        return 1;
    }


    return 0;
}

bool Sand::moveSandInOil(int &x, int &y)
{

    int moveBy=0;

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, velSandInWater);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, oil, sand);
        return 1;
    }

    /*down sides*/
    if(std::rand()%2 == 1){
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSandInWater);
        if(moveBy!= 0)
        {
            updateDownLeft(x, y, moveBy, oil, sand);
            return 1;
        }
    }else
    {
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSandInWater);
        if(moveBy!= 0)
        {
            updateDownRight(x, y, moveBy, oil, sand);
            return 1;
        }
    }

    return 0;
}

//jiggering of the solid elements is caused by flag n
void Sand::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    //std::cout << "updateDownLeft" << std::endl;
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
}


void Sand::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    //std::cout << "updateDownRight" << std::endl;
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
}



void Sand::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    //std::cout << "updateDown" << std::endl;
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x, y+move_by);
    world.setFlag('f', x, y+move_by);
}


