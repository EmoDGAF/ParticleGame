#include "sand.h"
#include <iostream>

Sand::Sand(World& world_)
{
    world = world_;
    //vel = velSandInAir ; // sand speed
    velSandInWater =2;
    velSandInOil =1;
    velSandInAir = 12;
}




//int Sand::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
//{
//    //type of the first particle on the path of sand: if its air, ignore, if its water replace
//    int i;
//    char lookUpPrt;
//    char firstEncounteredTypeOnPath;
//    for (i = 1; i < vel; ++i)
//    {
//        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
//        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);
//        if(lookUpPrt == air        && lookUpFlag!= 'f' ){ particleTypeToMove = air;   vel = 5 + std::rand()%15; }
//        else if(lookUpPrt == water && lookUpFlag!= 'f'){  particleTypeToMove = water; vel = 1 + velSandInWater; }
//        else if(lookUpPrt == oil   && lookUpFlag!= 'f'){  particleTypeToMove = oil;   vel = 1 + velSandInOil;   }

//        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == wood) //dont move sand through these
//        {
//            return i-1;
//        }
//    }
//    return i-1;
//}


int Sand::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{
    //type of the first particle on the path of sand: if its air, ignore, if its water replace
    int i;
    particleTypeToMove = '0'; //reset
    char lookUpPrt;
    char firstEncounteredTypeOnPath = '0';
    for (i = 1; i < vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);

        if(lookUpPrt == air && lookUpFlag!= 'f'){
            particleTypeToMove = air;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
            vel = 5 + std::rand()%15; //this is always called when path is clear
        }

        else if(lookUpPrt == water && lookUpFlag!= 'f'){
            particleTypeToMove = water;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
            vel = 1 + velSandInWater; //this is always called when path is clear
        }

        else if(lookUpPrt == oil   && lookUpFlag!= 'f'){
            particleTypeToMove = oil;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
            vel = 1 + velSandInOil; //this is always called when path is clear
        }

        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == wood) //dont move sand through these
        {
            return i-1;
        }
    }
    return i-1;
}



//separating moveSandinAir, moveSandinOil so on allows to apply different velocities for sand to move through these

bool Sand::moveSandinAir(int& x, int& y)
{
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, velSandInAir);
    if(moveBy> 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }

    /*down sides*/

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSandInAir);
    if(moveBy> 0)
    {
        updateDownLeft(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSandInAir);
    if(moveBy> 0)
    {
        updateDownRight(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }

    return 0;
}



bool Sand::moveSandInOil(int &x, int &y)
{
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, velSandInOil);
    if(moveBy> 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }

    /*down sides*/

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSandInOil);
    if(moveBy> 0)
    {
        updateDownLeft(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSandInOil);
    if(moveBy> 0)
    {
        updateDownRight(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }

    return 0;
}


bool Sand::moveSandInWater(int &x, int &y)
{
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, velSandInWater);
    if(moveBy> 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }

    /*down sides*/

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSandInWater);
    if(moveBy> 0)
    {
        updateDownLeft(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSandInWater);
    if(moveBy> 0)
    {
        updateDownRight(x, y, moveBy, particleTypeToMove, sand);
        return 1;
    }

    return 0;
}


//jiggering of the solid elements is caused by flag n
void Sand::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
    world.setFlag('f', x, y );
}


void Sand::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
    world.setFlag('f', x, y );
}



void Sand::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x, y+move_by);
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);

}

