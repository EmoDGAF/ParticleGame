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
    particleTypeToMove = '0';
    int i;
    char lookUpPrt;

    for (i = 1; i < vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);

        if(lookUpPrt == air && lookUpFlag!= 'f'){ particleTypeToMove = air;  vel = 5 + std::rand()%15; } //vel = 5 + std::rand()%15;
        //else if(lookUpPrt == fire ){ particleTypeToMove = fire; vel = 1 + velSandInWater; } //vel = 1 + std::rand()%8; | smoke can move through fire, cause otherwise, if smoke stops on fire, smoke pumps fire up
        else if( lookUpPrt == sand || lookUpPrt == rock  || lookUpPrt == smoke || lookUpPrt == wood || lookUpPrt == oil || lookUpPrt == water   )
        {
            return i-1;
        }
    }


//    if(x+i-1>= Width || x-i-1<= 40 || y+i-1 >=Hight || y-i-1 <=40)
//        return 0;

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
        if(particleTypeToMove ==air){
            updateUp(x, y, moveBy, air, smoke);
            return;
        }
    }
    /*down sides*/


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, -1, vel);
    if(moveBy> 0)
    {
        if(particleTypeToMove ==air){
            updateUpLeft(x, y, moveBy, air, smoke);
            return;
        }
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, vel) ;
    if(moveBy> 0)
    {
        if(particleTypeToMove ==air){
            updateLeft(x, y, moveBy, air, smoke);
            return;
        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, vel) ;
    if(moveBy> 0)
    {
        if(particleTypeToMove ==air){
            updateRight(x, y, moveBy, air, smoke);
            return;
        }
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
