#include "water.h"
#include <iostream>
Water::Water(World &world_)
{
    world = world_;
    vel =15;
}

//the problem with water coming as a high wave making oil disappear was: coming from above water first encounters air, then oil, - but in my function, oil moves on untill it encounter SOLID elements like rock, wood, so on, but it should move on untill reaches different KIND of particle, even non solid like oil

int Water::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{
    particleTypeToMove = '0'; // reset particleTypeToMove so it wont preserve its state and cause water appearance in next iteration
    vel = 10 + std::rand()%20;
    int i;
    char firstEncounteredTypeOnPath = '0';
    for (i = 1; i <= vel; ++i)
    {
        if(x+i-1>= Width || x-i-1<=  0 || y+i-1 >=Hight || y-i-1 <= 0) //so water doesnt move through edges on the other side
            return 0;
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);

        if(lookUpPrt == air        && lookUpFlag!= 'f'){
            particleTypeToMove = air;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }
        else if(lookUpPrt == oil && dir_y == -1 && lookUpFlag!= 'f' ){
            particleTypeToMove = water;
            return i -1; //*  impenetrable substance for water moving up
        }
        else if(lookUpPrt == oil   && lookUpFlag!= 'f'){
            particleTypeToMove = oil;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }
        else if(lookUpPrt == smoke && lookUpFlag!= 'f'){
            particleTypeToMove = smoke;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }
        else if(lookUpPrt == fire  && lookUpFlag!= 'f'){
            particleTypeToMove = fire;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == water || lookUpPrt == wood)
        {
            return i-1;
        }
    }
    return i-1;
}

void Water::moveWater(int& x, int& y)
{
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, 15); //UP
    if(moveBy!= 0)
    {
        //if(particleTypeToMove == air){
            //updateDown(x, y, moveBy, air, water);
            //return;
        //}
//        if(particleTypeToMove == oil){
//            updateUp(x, y, moveBy, oil, water);
//            return;
//        }
        //else if(particleTypeToMove == smoke){
            //updateDown(x, y, moveBy, smoke, water);
            //return;
        //}else
//          if(particleTypeToMove == fire){
//            updateUp(x, y, moveBy, smoke, smoke);
//            return;
//        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, 15); //DOWN
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateDown(x, y, moveBy, air, water);
            return;
        }
        else if(particleTypeToMove ==oil){
            updateDown(x, y, moveBy, oil, water);
            return;
        }
        else if(particleTypeToMove ==smoke){
            updateDown(x, y, moveBy, smoke, water);
            return;
        }
//        else if(particleTypeToMove ==fire){
//            updateDown(x, y, moveBy, smoke, smoke);
//            return;
//        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, 15); //Downleft
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateDownLeft(x, y, moveBy, air, water);
            return;
        }
//        else if(particleTypeToMove ==oil){
//            updateDownLeft(x, y, moveBy, oil, water);
//            return;
//        }
        else if(particleTypeToMove ==smoke){
            updateDownLeft(x, y, moveBy, smoke, water);
            return;
        }
//        else if(particleTypeToMove ==fire){
//            updateDownLeft(x, y, moveBy, smoke, smoke);
//            return;
//        }

    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, 15);
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateDownRight(x, y, moveBy, air, water);
            return;
        }
//        else if(particleTypeToMove ==oil){
//            updateDownRight(x, y, moveBy, oil, water);
//            return;
//        }
        else if(particleTypeToMove ==smoke){
            updateDownRight(x, y, moveBy, smoke, water);
            return;
        }
//        else if(particleTypeToMove ==fire){
//            updateDownRight(x, y, moveBy, smoke, smoke);
//            return;
//        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, 15);
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateRight(x, y, moveBy, air, water);
            return;
        }
//        else if(particleTypeToMove ==oil){
//            updateRight(x, y, moveBy, oil, water);
//            return;
//        }
        else if(particleTypeToMove ==smoke){
            updateRight(x, y, moveBy, smoke, water);
            return;
        }
//        else if(particleTypeToMove ==fire){
//            updateRight(x, y, moveBy, smoke, smoke);
//            return;
//        }
    }



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, 15);
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateLeft(x, y, moveBy, air, water);
            return;
        }
//        else if(particleTypeToMove ==oil){
//            updateLeft(x, y, moveBy, oil, water);
//            return;
//        }
        else if(particleTypeToMove ==smoke){
            updateLeft(x, y, moveBy, smoke, water);
            return;
        }
//        else if(particleTypeToMove ==fire){
//            updateLeft(x, y, moveBy, smoke, smoke);
//            return;
//        }
    }

}

void Water::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y+move_by );
}

void Water::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Water::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y+move_by);
}

void Water::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}

void Water::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

void Water::updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y-move_by);
}
