#include "water.h"
#include <iostream>
Water::Water(World &world_)
{
    world = world_;
}

int Water::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel )
{
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticle(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air){}
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == water)
        {
            return i-1;
        }
    }
    return i-1;
}

void Water::moveWater(int& x, int& y)
{

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, air, water);
        return;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, vel);
    if(moveBy!= 0)
    {
        updateDownLeft(x, y, moveBy, air, water);
        return;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, vel);
    if(moveBy!= 0)
    {
        updateDownRight(x, y, moveBy, air, water);
        return;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, vel);
    if(moveBy!= 0)
    {
        updateRight(x, y, moveBy, air, water);
        return;
    }



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, vel);
    if(moveBy!= 0)
    {
        updateLeft(x, y, moveBy, air, water);
        return;
    }



}
//sprawdzaj w tej wodzie czy ma na boki ukos pusto i jak ma to ja tam wstaw
/*[20:01:42] <~fir> ja mam w kodzi funkcyjki typu rusz czastke na ukos w dol jesli sie da
    [20:01:46] <~fir> i ja poprostu odpalam
    [20:02:12] <~fir> jesli sie da to ruszay taka wode naukos od razu jesli wsadze to wywolanie po swapni ecu wody w gore*/

void Water::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
}

void Water::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x-move_by , y);
    world.setFlag('f', x-move_by , y);
}

void Water::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
}

void Water::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x+move_by , y);
    world.setFlag('f', x+move_by , y);
}

void Water::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(currentPrt, x, y );
    world.setParticle(nextPrt, x, y+move_by);
    world.setFlag('f', x, y+move_by);
}
