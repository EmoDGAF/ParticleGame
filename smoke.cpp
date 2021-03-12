#include "smoke.h"
#include <iostream>

Smoke::Smoke(World& world_)
{
    world = world_;
    velSandInAir = 10;
    vel = velSandInAir ; // sand speed
    velSandInWater =2;
}


/*if fire moves through smoke, and smoke moves through fire, both are are neutral to each other*/
int Smoke::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{
    int i;
    particleTypeToMove = '0'; //reset is needed not to preserve the previous state

    for (i = 1; i <= vel; ++i)
    {
        if(x+i-1>= Width || x-i-1<=  0 || y+i-1 >=Hight || y-i-1 <= 0) //so water doesnt move through edges on the other side
            return 0;
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);


        if(lookUpPrt != sand && lookUpPrt != rock  && lookUpPrt != wood && lookUpPrt != oil  && lookUpFlag != 'f'){ /*go to next iteration of for loop*/ }
        else{
            lookUpPrt = world.getParticleType(x+dir_x*(i-1), y+dir_y*(i-1));
            particleTypeToMove = lookUpPrt;
            return i-1;
        }
    }

    particleTypeToMove = lookUpPrt;
    //setSandVelocitytoType(particleTypeToMove, vel);
    return i-1;
}


void Smoke::moveSmoke(int& x, int& y)
{
    //vel = vel + std::rand()% 140 - vel ; //changing velocity prevents pumping particles up
    //lifetime:
    if(world.getParticle(x,y)->decreaseSmokeLifetime())
        world.setParticle('n',x,y);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, vel) ;
    if(moveBy> 0)
    {
//no need to check if it encounters air, as all other types are removed as non interactive
            updateUp(x, y, moveBy, particleTypeToMove, smoke);
            return;

    }
    /*down sides*/


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, -1, vel);
    if(moveBy> 0)
    {

            updateUpLeft(x, y, moveBy, particleTypeToMove, smoke);
            return;

    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, vel) ;
    if(moveBy> 0)
    {

            updateLeft(x, y, moveBy, particleTypeToMove, smoke);
            return;

    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, vel) ;
    if(moveBy> 0)
    {

            updateRight(x, y, moveBy, particleTypeToMove, smoke);
            return;

    }
}



//jiggering of the solid elements is caused by flag n
void Smoke::updateUpLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y-move_by );
    world.setFlag('f', x-move_by , y-move_by );
    world.setFlag('f', x, y );

}


void Smoke::updateUpRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by, y-move_by);
    world.setFlag('f', x+move_by, y-move_by);
    world.setFlag('f', x, y );

}



void Smoke::updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x, y-move_by);
    world.setFlag('f', x, y );
    world.setFlag('f', x, y-move_by);

}

void Smoke::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}



void Smoke::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}
