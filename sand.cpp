#include "sand.h"
#include <iostream>

Sand::Sand(World& world_)
{
    world = world_;
    vel = velSandInAir ; // sand speed
    velSandInWater =2;
    velSandInAir = 10;
}


char particleTypeToMove;
int Sand::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{
    int i;
    char lookUpPrt;
    for (i = 1; i < vel; ++i)
    {

        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        //char flag = world.getFlag(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air ){ particleTypeToMove = air;  vel = 5 + std::rand()%15; } //vel = 5 + std::rand()%15;
        if(lookUpPrt == water ){ particleTypeToMove = water; vel = 1 + velSandInWater; } //vel = 1 + std::rand()%8;
        if(lookUpPrt == oil ){ particleTypeToMove = oil; vel = 1 + velSandInWater; } //vel = 1 + std::rand()%8;

        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == fire)
        {
            return i-1;
        }

    }

    return i-1;
}



bool Sand::moveSandinAir(int& x, int& y)
{
    //vel = vel + std::rand()% 140 - vel ; //changing velocity prevents pumping particles up

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel);
    if(moveBy> 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, sand);
            return 1;
    }
    /*down sides*/



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, vel);
    if(moveBy> 0)
    {
        updateDownLeft(x, y, moveBy, particleTypeToMove, sand);
            return 1;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, vel);
    if(moveBy> 0)
    {
        updateDownRight(x, y, moveBy, particleTypeToMove, sand);
            return 1;
    }


    return 0;
}



bool Sand::moveSandInOil(int &x, int &y)
{
//    int moveBy=0;

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, velSandInWater);
//    if(moveBy!= 0)
//    {
//        updateDown(x, y, moveBy, particleTypeToMove, sand);
//        return 1;
//    }

//    /*down sides*/

//        moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSandInWater);
//        if(moveBy!= 0)
//        {
//            updateDownLeft(x, y, moveBy, particleTypeToMove, sand);
//            return 1;
//        }

//        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSandInWater);
//        if(moveBy!= 0)
//        {
//            updateDownRight(x, y, moveBy, particleTypeToMove, sand);
//            return 1;
//        }


        return 0;
}

//jiggering of the solid elements is caused by flag n
void Sand::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x-move_by , y+move_by )=='f')
        return;
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
    world.setFlag('f', x, y );

}


void Sand::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x+move_by, y+move_by)=='f') //can check cause sand goes through water
        return;
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
    world.setFlag('f', x, y );

}



void Sand::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{

    if(world.getFlag( x, y+moveBy)=='f')
        return;
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x, y+move_by);
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);

}

