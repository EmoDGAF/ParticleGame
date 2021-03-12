#include "sand.h"
#include <iostream>

Sand::Sand(World& world_)
{
    world = world_;
    //vel = velSandInAir ; // sand speed
    velSandInWater =2;
    velSandInOil =1;
    velSandInAir = 12;
    particleTypeToMove = air;
    vel = 20;
    moveSandAsideIndex = 0;
    std::cout << "Sand::Sand(World& world_)" << "\n";
}

void Sand::setSandVelocitytoType(char& particleTypeToMove, int& vel)
{
    //for these to modify the values of vel, the function must pass vel by reference to checkHowFarIsObstacleInGivenDir:
    if(particleTypeToMove==air)vel = 5 + std::rand()%35;
    else if(particleTypeToMove==water)vel = 2;
    else if(particleTypeToMove==oil)vel = 1  ;
}

int Sand::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int& vel )
{
    int i;
    particleTypeToMove = '0'; //reset is needed not to preserve the previous state

    for (i = 1; i <= vel; ++i)
    {
        if(x+i-1>= Width || x-i-1<=  0 || y+i-1 >=Hight || y-i-1 <= 0) //so water doesnt move through edges on the other side
            return 0;
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);


        if(lookUpPrt != sand && lookUpPrt != rock && lookUpPrt != wood && lookUpPrt   && lookUpFlag != 'f'){ /*go to next iteration of for loop*/ }
        else{
            lookUpPrt = world.getParticleType(x+dir_x*(i-1), y+dir_y*(i-1));
            particleTypeToMove = lookUpPrt;
            return i-1;
        }
    }

    particleTypeToMove = lookUpPrt;
    setSandVelocitytoType(particleTypeToMove, vel);
    return i-1;
}

//to avoid sand pilling up in an unnatural way, there should be a rule, if sand is in the air, dont allow its particles touch each other
void Sand::moveSand(int& x, int& y)
{
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel);
    if(moveBy> 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, sand);
        return;
    }

    /*down sides*/

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, vel);
    if(moveBy> 0)
    {
        updateDownLeft(x, y, moveBy, particleTypeToMove, sand);
        return;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, vel);
    if(moveBy> 0)
    {
        updateDownRight(x, y, moveBy, particleTypeToMove, sand);
        return;
    }

 //==========

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -2, 1, vel);
//    if(moveBy> 0)
//    {
//        updateDownLeft(x, y, moveBy, particleTypeToMove, sand);
//        return;
//    }

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 2, 1, vel);
//    if(moveBy> 0)
//    {
//        updateDownRight(x, y, moveBy, particleTypeToMove, sand);
//        return;
//    }

}





//jiggering of the solid elements is caused by flag n
void Sand::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
    //world.setFlag('f', x, y );
}


void Sand::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
    //world.setFlag('f', x, y );
}



void Sand::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x, y+move_by);
    //world.setFlag('f', x, y );   //prevents pumping up
    world.setFlag('f', x, y+move_by);

}

//void Sand::updateLeft(int&  x, int&  y, int move_by, char& currentPrt, char& nextPrt)
//{
//    world.setParticle(currentPrt, x, y );
//    world.setParticle(nextPrt, x-move_by , y );
//    world.setFlag('f', x-move_by , y );
//    world.setFlag('f', x, y );
//}


//void Sand::updateRight(int&  x, int&  y, int move_by, char& currentPrt, char& nextPrt)
//{
//    world.setParticle(currentPrt, x, y );
//    world.setParticle(nextPrt, x+move_by, y );
//    world.setFlag('f', x+move_by, y );
//    world.setFlag('f', x, y );
//}
