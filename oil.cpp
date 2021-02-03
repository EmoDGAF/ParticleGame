#include "oil.h"
#include <iostream>
Oil::Oil(World &world_)
{
    world = world_;
    vel = 10;
}

int Oil::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, char substancePrtMovesThrough , int vel)
{
    vel = 10 + std::rand()%8;
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        //char flag = world.getFlag(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air){}
        else if(lookUpPrt == sand || lookUpPrt == rock ||lookUpPrt == oil  ||lookUpPrt == water || lookUpPrt == smoke )
        {
            return i-1;
        }
    }
    return i-1;
}


int Oil::checkHowFarIsWaterInGivenDir(int x, int y, int dir_x, int dir_y, int vel)
{
    //vel = 10 + std::rand()%8;
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        //char flag = world.getFlag(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == water){}
        else if(lookUpPrt == sand || lookUpPrt == rock ||lookUpPrt == oil  ||lookUpPrt == air ||lookUpPrt == smoke)
        {
            return i-1;
        }
    }
    return i-1;
}


bool Oil::moveOilinAir(int& x, int& y)
{
//std::cout << "moveOilinAir" << std::endl;
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, air, vel);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, air, oil);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, air, vel);
    if(moveBy!= 0)
    {
        updateDownLeft(x, y, moveBy, air, oil);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, air, vel);
    if(moveBy!= 0)
    {
        updateDownRight(x, y, moveBy, air, oil);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, air, vel);
    if(moveBy!= 0)
    {
        updateRight(x, y, moveBy, air, oil);
        return 1;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, air, vel);
    if(moveBy!= 0)
    {
        updateLeft(x, y, moveBy, air, oil);
        return 1;
    }

    return 0;
}



bool Oil::moveOilinWater(int &x, int &y)
{
    //std::cout << "moveOilinWater" << std::endl;

    moveBy = checkHowFarIsWaterInGivenDir(x, y, 0, -1, 15);
    if(moveBy!= 0)
    {
        updateUp(x, y, moveBy, water, oil); //whats above oil
        return 1;
    }


//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, air, vel);
//    if(moveBy!= 0)
//    {
//        updateDownLeft(x, y, moveBy, water, oil);
//        return 1;
//    }

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, air, vel);
//    if(moveBy!= 0)
//    {
//        updateDownRight(x, y, moveBy, water, oil);
//        return 1;
//    }



//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, -1, water, vel);
//    if(moveBy!= 0)
//    {
//        updateUpLeft(x, y, moveBy, water, oil);
//        return 1;
//    }

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, -1, water, vel);
//    if(moveBy!= 0)
//    {
//        updateUpRight(x, y, moveBy, water, oil);
//        return 1;
//    }

    moveBy = checkHowFarIsWaterInGivenDir(x, y, 1, 0, 10);
    if(moveBy!= 0)
    {
        updateRight(x, y, moveBy, water, oil);
        return 1;
    }


    moveBy = checkHowFarIsWaterInGivenDir(x, y, -1, 0, 10);
    if(moveBy!= 0)
    {
        updateLeft(x, y, moveBy, water, oil);
        return 1;
    }

    return 0;
}



void Oil::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{

    if(world.getFlag( x-move_by , y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y+move_by );
}

void Oil::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x-move_by , y)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Oil::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag(x+move_by, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y+move_by);
}

void Oil::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x+move_by , y)=='f')  //cant check cause water cant spread properly
        return;
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}

void Oil::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

/*in Water*/
void Oil::updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x, y-move_by)=='f')
        return;
    world.setParticle(nextPrt, x, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y-move_by);
}

void Oil::updateUpRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag(x+move_by, y-move_by)=='f')
        return;
    world.setParticle(nextPrt, x+move_by, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y-move_by);
}

void Oil::updateUpLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{

    if(world.getFlag( x-move_by , y-move_by)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y-move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y-move_by );
}
