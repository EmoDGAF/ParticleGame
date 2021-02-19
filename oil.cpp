#include "oil.h"
#include <iostream>
Oil::Oil(World &world_)
{
    world = world_;
    vel = 8;
}


int Oil::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel)
{
    particleTypeToMove = '0'; //reset
    vel = 8 + std::rand()%8;
    int i;
    char firstEncounteredTypeOnPath = '0';
    for (i = 1; i <= vel; ++i)
    {
        if(x+i-1>= Width || x-i-1<=  0 || y+i-1 >=Hight || y-i-1 <= 0) //so water doesnt move through edges on the other side
            return 0;

        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);

        if(lookUpPrt == air && lookUpFlag!= 'f' ){
            particleTypeToMove =air;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }

        //BUT water causes a problem, because water shouldnt be penetrable by oil from (oil)updateDown, but should be penetrable from updateUp (so it can get on the surface of water) - thats why "&& dir_y == 1" cause  1 indcates checking Down (whats below oil)
        else if(lookUpPrt == water && dir_y == 1 && lookUpFlag!= 'f' ){
            //particleTypeToMove =oil;
            return i-1;
        } //*  impenetrable substance for water moving up | so it means "im an oil particle, so i cant move down when water is below me"
        else if(lookUpPrt == water && lookUpFlag!= 'f' ){
            particleTypeToMove =water;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }
        else if(lookUpPrt == smoke && lookUpFlag!= 'f' ){
            particleTypeToMove =smoke;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }
        else if(lookUpPrt == fire  && lookUpFlag!= 'f' ){
            particleTypeToMove =fire;
            if(firstEncounteredTypeOnPath = '0')
                firstEncounteredTypeOnPath = lookUpPrt;
            else if(lookUpPrt != firstEncounteredTypeOnPath)
                return i;
        }
        /*impenetrable substances:*/
        else if(lookUpPrt == sand || lookUpPrt == rock ||lookUpPrt == oil  || lookUpPrt == wood) //*
        {
            return i-1; //return position BEFORE rock/sand/oil/wood | here i return i within the loop
        }
    }

    //here "i" is bigger by 1 as it's past for loop which inseases  ++i - thats why "return i-1" - so i can get the actual location of the desired interactive particle like air/water/smoke
    return i-1; //return actual position OF air/water/smoke [so they can be replaced (moved/updated)] - so its interactive particles || so its like return i within the for loop (and not after it)
}


/*It would be possible to set for each particle rules of interaction with all the other particles, but it SLOWS DOWN the program, so its better not to repeat once already defined rule FOR ONE of the particles in interaction [meaning setting the rules in one (of the 2 interacting classes) is enough ]:*/
void Oil::moveOil(int& x, int& y)
{
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, vel); //UP
    if(moveBy!= 0)
    {
        //if(particleTypeToMove ==air){
        //updateUp(x, y, moveBy, smoke, oil); //if air is above water, do nothing
        //return     //return here would prevent the other conditions below to be checked
        //} else

        if(particleTypeToMove ==water){
            updateUp(x, y, moveBy, water, oil);
            return;
        }

        //else if(particleTypeToMove ==smoke){
        //updateUp(x, y, moveBy, air, oil);
        //return
        // }
        //        else if(particleTypeToMove ==fire){
        //            updateUp(x, y, moveBy, fire, fire);
        //            return;
        //        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, vel); //DOWN
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateDown(x, y, moveBy, air, oil);
            return;
        }
        //else if(particleTypeToMove ==water){
        //updateDown(x, y, moveBy, water, oil);
        //return;
        // }
        else if(particleTypeToMove ==smoke){
            updateDown(x, y, moveBy, smoke, oil);
            return;
        }
        //        else if(particleTypeToMove ==fire){
        //            updateDown(x, y, moveBy, fire, fire);
        //            return;
        //        }

    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, vel); //DownLeft
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateDownLeft(x, y, moveBy, air, oil);
            return;
        }
        //else if(particleTypeToMove ==water){
        //updateDownLeft(x, y, moveBy, water, oil);
        //return;
        //}
        //        else if(particleTypeToMove ==smoke){
        //            updateDownLeft(x, y, moveBy, smoke, oil);
        //            return;
        //        }
        //        else if(particleTypeToMove ==fire){
        //            updateDownLeft(x, y, moveBy, fire, fire);
        //            return;
        //        }

    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, vel);
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateDownRight(x, y, moveBy, air, oil);
            return;
        }
        //else if(particleTypeToMove ==water){
        //updateDownLeft(x, y, moveBy, water, oil);
        //return;
        //}
        //        else if(particleTypeToMove ==smoke){
        //            updateDownRight(x, y, moveBy, smoke, oil);
        //            return;
        //        }
        //        else if(particleTypeToMove ==fire){
        //            updateDownRight(x, y, moveBy, fire, fire);
        //            return;
        //        }

    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, vel); //left
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateLeft(x, y, moveBy, air, oil);
            return;
        }
        else if(particleTypeToMove ==water){
            //oil should be able to move right and left, cause otherwise it wouldnt dispair underwater well:
            updateLeft(x, y, moveBy, water, oil);
            return;
        }
        //        else if(particleTypeToMove ==smoke){
        //            updateLeft(x, y, moveBy, smoke, oil);
        //            return;
        //        }
        //        else if(particleTypeToMove ==fire){
        //            updateLeft(x, y, moveBy, fire, fire);
        //            return;
        //        }
    }


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, vel); //Right
    if(moveBy!= 0)
    {
        if(particleTypeToMove ==air){
            updateRight(x, y, moveBy, air, oil);
            return;
        }
        else if(particleTypeToMove ==water){
            //oil should be able to move right and left, cause otherwise it wouldnt dispair underwater well:
            updateRight(x, y, moveBy, water, oil);
            return;
        }
        //        else if(particleTypeToMove ==smoke){
        //            updateRight(x, y, moveBy, smoke, oil);
        //            return;
        //        }
        //        else if(particleTypeToMove ==fire){
        //            updateRight(x, y, moveBy, fire, fire);
        //            return;
        //        }

    }

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, -1, vel); //Up Left
//    if(moveBy!= 0)
//    {
//        if(particleTypeToMove ==water){
//            //oil should be able to move right and left, cause otherwise it wouldnt dispair underwater well:
//            updateUpLeft(x, y, moveBy, water, oil);
//            return;
//        }
//    }

//    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, -1, vel); //Up Right
//    if(moveBy!= 0)
//    {
//        if(particleTypeToMove ==water){
//            //oil should be able to move right and left, cause otherwise it wouldnt dispair underwater well:
//            updateUpRight(x, y, moveBy, water, oil);
//            return;
//        }
//    }

}



void Oil::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y ); //without it for ex. smoke appears in weird placed when fire hits water
    world.setFlag('f', x-move_by , y+move_by );
}

void Oil::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Oil::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y+move_by);
}

void Oil::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}

void Oil::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

/*in Water*/
void Oil::updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y-move_by);
}

void Oil::updateUpRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y-move_by);
}

void Oil::updateUpLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y-move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y-move_by );
}
