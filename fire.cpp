#include "fire.h"
#include <iostream>
Fire::Fire()
{

}

//int Fire::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
//{
//    int i;
//    char lookUpPrt;

//    for (i = 1; i <= vel; ++i)
//    {
//        lookUpPrt = world.getParticle(x+dir_x*i, y+dir_y*i);
//        if(lookUpPrt == air){   }
//        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == fire)
//        {

//            return  i-1 ;
//        }
//    }
//    return  i ;
//}

//int Fire::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
//{
//    int moveBy =0;
//    for (int z = 1; z <= vel; ++z) {
//        lookUpPrt = world.getParticle(x+dir_x*z, y+dir_y*z);
//        if(lookUpPrt == air){
//            moveBy =z; // moveBy becomes the last z fulfilling the if condition
//        }
//        else if(lookUpPrt == rock || lookUpPrt == sand || lookUpPrt == fire) return moveBy;
//    }
//    return moveBy;    //so it calls updateDown(x, y, moveBy, air, fire);
//}

int Fire::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticle(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air){}
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == fire)
        {
            return i-1;
        }
    }
    return i-1;
}


void Fire::moveFire(int& x, int& y)
{

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, air, fire);
        return;
    }

/*down sides*/
    if(std::rand()%2 == 1){
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, vel);
        if(moveBy!= 0)
        {
            updateDownLeft(x, y, moveBy, air, fire);
            return;
        }
    }else
    {

        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, vel);
        if(moveBy!= 0)
        {
            updateDownRight(x, y, moveBy, air, fire);
            return;
        }
    }

/*sides*/

    if(std::rand()%2 == 1){
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, vel);
        if(moveBy!= 0)
        {
            updateLeft(x, y, moveBy, air, fire);
            return;
        }
    }else
    {
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, vel);
        if(moveBy!= 0)
        {
            updateRight(x, y, moveBy, air, fire);
            return;
        }
    }

}


void Fire::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
}

void Fire::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y);
    world.setFlag('f', x-move_by , y);
}

void Fire::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
}

void Fire::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by , y);
    world.setFlag('f', x+move_by , y);
}

void Fire::updateDown(int&  x, int&  y, int  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x, y+move_by);
    world.setFlag('f', x, y+move_by);
}

// INTERACTIONS:


