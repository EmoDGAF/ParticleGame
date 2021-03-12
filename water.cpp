#include "water.h"
#include <iostream>
Water::Water(World &world_)
{
    world = world_;
    vel =25;
    velSides = 35;
    number4 =0;
}

/*basicly, to achieve fast water movement easilly, i need to make the water move in certain direction left/right, cause when each frame the direction changes, water movements null each other */

void Water::setSandVelocitytoType(char& particleTypeToMove, int& vel)
{
    //for these to modify the values of vel, the function must pass vel by reference to checkHowFarIsObstacleInGivenDir:
    if(particleTypeToMove==air)vel = 15 + std::rand()%35;
    if(particleTypeToMove==water || particleTypeToMove==smoke)vel = 35  + std::rand()%25;
    else if(particleTypeToMove==oil)vel = 1  ;
    else vel = 10 + std::rand()%15;
}

bool Water::disperseWater(int &x, int &y)
{
    int r = std::rand()%4;
    if(r==3){
        int velDisp =25;
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, velDisp);
        if(moveBy> 0)
        {
            updateLeft(x, y, moveBy, particleTypeToMove, water);
            return true;
        }
    }else if(r ==2){
        int velDisp =25;
        moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, velDisp);
        if(moveBy> 0)
        {
            updateRight(x, y, moveBy, particleTypeToMove, water);
            return true;
        }
    }

    return false;
}

int Water::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int& vel )
{
    int i;
    particleTypeToMove = '0'; //reset is needed not to preserve the previous state

    for (i = 1; i <= vel; ++i)
    {
        if(x+i-1>= Width || x-i-1<=  0 || y+i-1 >=Hight || y-i-1 <= 0) //so water doesnt move through edges on the other side
            return 0;
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);


        if(lookUpPrt != sand && lookUpPrt != rock && lookUpPrt != wood && lookUpPrt != smoke && lookUpPrt!= water && lookUpFlag != 'f'){ /*go to next iteration of for loop*/ }
        else{
            lookUpPrt = world.getParticleType(x+dir_x*(i-1), y+dir_y*(i-1));
            particleTypeToMove = lookUpPrt;
            //if(i-1>0) std::cout << i-1 << "\n";
            return i-1;
        }
    }

    particleTypeToMove = lookUpPrt;
    setSandVelocitytoType(particleTypeToMove, vel);
    // if(i-1>0) std::cout << i-1 << "\n";
    return i-1;
}



void Water::moveWater(int& x, int& y)
{
    number4++;
    if(disperseWater(x, y)) return;
    //=========
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel); //DOWN
    if(moveBy!= 0)
    {
        updateDown(x, y, moveBy, particleTypeToMove, water);
        return;
    }

    //randomizing left /right prevents dragging big amount of water to right or left - but this way water levels SLOWER
   if((number4&1)==0 ){
       moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, velSides); //Downleft
       if(moveBy!= 0)
       {

           updateDownLeft(x, y, moveBy, particleTypeToMove, water);
           return;
       }
   }else{

       moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, velSides);
       if(moveBy!= 0)
       {

           updateDownRight(x, y, moveBy, particleTypeToMove, water);
           return;

       }
     }





    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, velSides);
    if(moveBy!= 0)
    {
        updateLeft(x, y, moveBy, particleTypeToMove, water);
        return;
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, velSides);
    if(moveBy!= 0)
    {
        updateRight(x, y, moveBy, particleTypeToMove, water);
        return;
    }


}

//setting flags affects distribution of water and its speed, and also "pumping up" water effect, with certain set it disappears; also direction of waves kinda depends on the set

void Water::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    //world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

void Water::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    //world.setFlag('f', x-move_by , y+move_by );
}

void Water::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    //world.setFlag('f', x+move_by, y+move_by);
}

void Water::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    //world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Water::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    //world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}



