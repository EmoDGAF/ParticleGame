#include "oil.h"
#include <iostream>
Oil::Oil(World &world_)
{
    world = world_;
    vel = 8;
}


void Oil::setOilVelocitytoType(char& particleTypeToMove, int& vel)
{
    //for these to modify the values of vel, the function must pass vel by reference to checkHowFarIsObstacleInGivenDir:
    if(particleTypeToMove==air)vel = 10 + std::rand()%35;
    //if(particleTypeToMove==water)vel = 154 + std::rand()%25;
    else if(particleTypeToMove==oil)vel = 1  ;
}

bool Oil::disperseOil(int &x, int &y)
{
    int r = std::rand()%15;
    if(r==3){
        int velDisp =25;
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, velDisp);
        if(moveBy> 0)
        {
            updateLeft(x, y, moveBy, particleTypeToMove, oil);
            return true;
        }
    }else if(r ==2){
        int velDisp =25;
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, velDisp);
        if(moveBy> 0)
        {
            updateRight(x, y, moveBy, particleTypeToMove, oil);
            return true;
        }
    }

    return false;
}

int Oil::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel)
{

    int i;
    particleTypeToMove = '0'; //reset is needed not to preserve the previous state

    for (i = 1; i <= vel; ++i)
    {
        if(x+i-1>= Width || x-i-1<=  0 || y+i-1 >=Hight || y-i-1 <= 0) //so water doesnt move through edges on the other side
            return 0;
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);


        if(lookUpPrt != sand && lookUpPrt != rock && lookUpPrt != wood && lookUpPrt != oil && lookUpPrt!= water && lookUpFlag != 'f'){ /*go to next iteration of for loop*/ }
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

int velSides = 25;

void Oil::moveOil(int& x, int& y)
{

    if(disperseOil(x, y)) return;
    //=========
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel); //DOWN
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, oil);
        return;
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, velSides);
    if(moveBy!= 0)
    {

        updateLeft(x, y, moveBy, particleTypeToMove, oil);
        return;

    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, velSides);
    if(moveBy!= 0)
    {

        updateRight(x, y, moveBy, particleTypeToMove, oil);
        return;
    }



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSides); //Downleft
    if(moveBy!= 0)
    {

        updateDownLeft(x, y, moveBy, particleTypeToMove, oil);
        return;
    }



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSides);
    if(moveBy!= 0)
    {

        updateDownRight(x, y, moveBy, particleTypeToMove, oil);
        return;

    }
}

//setting flags affects distribution of water and its speed, and also "pumping up" water effect, with certain set it disappears; also direction of waves kinda depends on the set

void Oil::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    //world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

void Oil::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    //world.setFlag('f', x-move_by , y+move_by );
}

void Oil::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    //world.setFlag('f', x+move_by, y+move_by);
}

void Oil::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    //world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Oil::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    //world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}
