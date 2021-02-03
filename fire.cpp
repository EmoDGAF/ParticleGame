#include "fire.h"
#include <iostream>
Fire::Fire(World &world_)
{
    world = world_;
    vel =15;
    spreadFireVel = 1; //because if "else if(particleTypeToMove == oil) spreadFire(x,y);" - so cant move by more than 1 cause it would bo beyond oil in the direction, where oil is
}



int Fire::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel, bool is_rand = true)
{

    if(is_rand) vel = 4 + std::rand()%8; //dont use random when fireSpreads
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air ){ particleTypeToMove = air; }
        if(lookUpPrt == oil ){ particleTypeToMove = oil; }
        if(lookUpPrt == water ){ particleTypeToMove = water; }
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == fire || lookUpPrt == smoke) //without lookUpPrt == fire (fire is the current particle), fire would disappear when falling down
        {
            return i-1;
        }
    }
    return i-1;
}

void Fire::spreadFire(int& x, int& y)
{
    int moveBy;
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, spreadFireVel,false);
    if(moveBy)
        updateDown(x,y,spreadFireVel,fire, fire);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, spreadFireVel,false);
    if(moveBy)
        updateUp(x,y,spreadFireVel,fire, fire);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, spreadFireVel,false);
    if(moveBy)
        updateLeft(x,y,spreadFireVel,fire, fire);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, spreadFireVel,false);
    if(moveBy)
        updateRight(x,y,spreadFireVel,fire, fire);

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, spreadFireVel);
//    if(moveBy)
//        updateDownLeft(x,y,spreadFireVel,fire, fire);

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y,  1, 1, spreadFireVel);
//    if(moveBy)
//        updateDownRight(x,y,spreadFireVel,fire, fire);
}

bool Fire::moveFire(int& x, int& y)
{

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, 10);
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, fire); //particleTypeToMove = air
        if(particleTypeToMove == water) //fire interacts with water
            updateUp(x,y,moveBy, air, smoke);
        else if(particleTypeToMove == oil) //fire interacts with oil
            spreadFire(x,y);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, 15);
    if(moveBy!= 0)
    {
        updateDownLeft(x, y, moveBy, particleTypeToMove, fire);
        if(particleTypeToMove == oil) //fire interacts with oil
            spreadFire(x,y);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, 15);
    if(moveBy!= 0)
    {
        updateDownRight(x, y, moveBy, particleTypeToMove, fire);
        if(particleTypeToMove == oil) //fire interacts with oil
           spreadFire(x,y);
        return 1;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, 20);
    if(moveBy!= 0)
    {
        updateRight(x, y, moveBy, particleTypeToMove, fire);
        if(particleTypeToMove == oil) //fire interacts with oil
            spreadFire(x,y);
        return 1;
    }



    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, 20);
    if(moveBy!= 0)
    {
        updateLeft(x, y, moveBy, particleTypeToMove, fire);
        if(particleTypeToMove == oil) //fire interacts with oil
            spreadFire(x,y);
        return 1;
    }

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, 10);
//    if(moveBy!= 0)
//    {
//       updateUp(x,y,moveBy, air, smoke);
//       if(particleTypeToMove == oil) //fire interacts with oil
//            spreadFire(x,y);
//        return 1;
//    }

    //TODO:
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, 10); //move fire up so when oil drops on it it burns
    if(moveBy!= 0)
    {
//        if(particleTypeToMove == air)
//           updateUp(x,y,moveBy, air, smoke);
       if(particleTypeToMove!= air)
             updateUp(x,y,moveBy, particleTypeToMove, smoke);
       if(particleTypeToMove == oil){ //fire interacts with oil


            spreadFire(x,y);
       }
        return 1;
    }


    return 0;

}





void Fire::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{

    if(world.getFlag( x-move_by , y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y+move_by );
}

void Fire::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x-move_by , y)=='f')
        return;
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Fire::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag(x+move_by, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y+move_by);
}

void Fire::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x+move_by , y)=='f')  //cant check cause water cant spread properly
        return;
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}

void Fire::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x, y+move_by)=='f')
        return;
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

void Fire::updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    if(world.getFlag( x, y-move_by)=='f')
        return;
    world.setParticle(nextPrt, x, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y-move_by);
}
