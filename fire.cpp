#include "fire.h"
#include <iostream>
Fire::Fire(World &world_)
{
    world = world_;
    vel =15;
    velWoodOnFire =0.1;
    spreadFireVel = 1; //because if "else if(particleTypeToMove == oil) spreadFire(x,y);" - so cant move by more than 1 cause it would bo beyond oil in the direction, where oil is
    velUpFire= 30;
}

void Fire::spreadFire(int& x, int& y)
{
    int moveBy;

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, spreadFireVel,false);
    if(moveBy)
        updateDown(x,y,moveBy,smoke, fire);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, spreadFireVel,false);
    if(moveBy)
        updateLeft(x,y,moveBy,smoke, fire);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, spreadFireVel,false);
    if(moveBy)
        updateRight(x,y,moveBy,smoke, fire);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, spreadFireVel,false);
    if(moveBy)
        updateUp(x,y,moveBy,smoke, fire); //smoke should only appear above, cause other way blocks spread of fire getting on its way

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, -1, spreadFireVel,false);
    if(moveBy)
        updateUpRight(x,y,moveBy,smoke, fire);

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, -1, spreadFireVel,false);
    if(moveBy)
        updateUpLeft(x,y,moveBy,smoke, fire);
}


/*if fire moves through smoke, and smoke moves through fire, both are are neutral to each other: */
float Fire::checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel, bool is_rand = true)
{
    particleTypeToMove = '0';
    if(is_rand) vel = 4 + std::rand()%8; //dont use random when fireSpreads
    int i;
    char lookUpPrt;
    for (i = 1; i <= vel; ++i)
    {
        lookUpPrt = world.getParticleType(x+dir_x*i, y+dir_y*i);
        lookUpFlag = world.getFlag(x+dir_x*i, y+dir_y*i);
        if(lookUpPrt == air        && lookUpFlag!= 'f'){ particleTypeToMove = air; }
        else if(lookUpPrt == oil   && lookUpFlag!= 'f'){ particleTypeToMove = oil; }
        else if(lookUpPrt == water && lookUpFlag!= 'f'){ particleTypeToMove = water; }
        else if(lookUpPrt == wood  && lookUpFlag!= 'f'){ particleTypeToMove = wood; }
        else if(lookUpPrt == smoke && lookUpFlag!= 'f'){ particleTypeToMove =smoke; } //without it smoke puts off fire when moving up wood | fire should be able to move through smoke, cause when falling down, fire would act as if it hit on rock - so smoke must be penetrable
        /*non burnable: */
        else if(lookUpPrt == sand || lookUpPrt == rock || lookUpPrt == fire ) //without lookUpPrt == fire (fire is the current particle), fire would disappear when falling down
        {
            return i-1;
        }
    }

    return i-1;
}



void Fire::moveFire(int& x, int& y)
{
    //lifetime:
    if(world.getParticle(x,y)->decreaseFireLifetime())
        world.setParticle('n',x,y);


    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, 1, 10); //down
    if(moveBy!= 0)
    {
        if(particleTypeToMove == air){
            updateDown(x, y, moveBy, air, fire);
            return;
        }
        else if(particleTypeToMove == water){
            //fire interacts with water
            updateDown(x,y,moveBy,smoke, smoke); //current is fire
            return;
        }
        else if(particleTypeToMove == oil){ //fire interacts with oil
            updateUp(x,y,moveBy,smoke, fire); //adds smoke
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == wood){ //fire interacts with oil
            updateDown(x,y,moveBy,smoke, fire); //adds smoke and also without it, fire particles wouldnt reach the surface of some wooden particles, causing leaving those unburnt, fire would "jump" on wood never reaching wood
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == smoke){
//            updateUp(x,y,moveBy,smoke, fire);
//            return;
        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 1, 15);//down left
    if(moveBy!= 0)
    {
        if(particleTypeToMove == air){
            updateDownLeft(x, y, moveBy, air, fire);
            return;
        }
        else if(particleTypeToMove == water){
            //fire interacts with water
            updateDownLeft(x,y,moveBy,smoke, smoke);
            return;
        }
        else if(particleTypeToMove == oil){ //fire interacts with oil
             updateDownLeft(x,y,moveBy,smoke, fire); //add smoke
             spreadFire(x,y);
             return;
        }
        else if(particleTypeToMove == wood){ //fire interacts with oil
            updateDownLeft(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == smoke){ //fire interacts with oil
            //updateDownLeft(x,y,moveBy,smoke, fire);
            //spreadFire(x,y);
            //return;
        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 1, 15); //down right
    if(moveBy!= 0)
    {
        if(particleTypeToMove == air){
            updateDownRight(x, y, moveBy, air, fire);
            return;
        }
        else if(particleTypeToMove == water){
            //fire interacts with water
            updateDownRight(x,y,moveBy,smoke, smoke);
            return;
        }
        else if(particleTypeToMove == oil){ //fire interacts with oil
            updateDownRight(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == wood){ //fire interacts with oil
            updateDownRight(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == smoke){ //fire interacts with oil
            //spreadFire(x,y);
        }

    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 1, 0, 20);//right
    if(moveBy!= 0)
    {
        if(particleTypeToMove == air){
            updateRight(x, y, moveBy, air, fire);
            return;
        }
        else if(particleTypeToMove == oil){
            updateRight(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == wood){ //fire interacts with oil
            updateRight(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == smoke){ //fire interacts with oil
            //spreadFire(x,y);
            //updateRight(x,y,moveBy,smoke, fire);
            //return;
        }
    }

    moveBy = checkHowFarIsObstacleInGivenDir(x, y, -1, 0, 20); //left
    if(moveBy!= 0)
    {
        if(particleTypeToMove == air){
            updateLeft(x, y, moveBy, air, fire);
            return;
        }
        else if(particleTypeToMove == oil){
            updateLeft(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == wood){ //fire interacts with oil
            updateLeft(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
        else if(particleTypeToMove == smoke){ //fire interacts with oil
            //spreadFire(x,y);
            //updateLeft(x,y,moveBy,smoke, fire);
            //return;
        }


    }

    //up:
    moveBy = checkHowFarIsObstacleInGivenDir(x, y, 0, -1, 10); //move fire up so when oil drops on it it burns
    if(moveBy!= 0)
    {
       if(particleTypeToMove == wood){  //fire interacts with oil
            updateUp(x,y,moveBy,smoke, fire);
            spreadFire(x,y);
            return;
        }
       else if(particleTypeToMove == water){
            //fire interacts with water
            updateUp(x,y,moveBy,smoke, smoke);
            return;
        }
        else if(particleTypeToMove == oil){  //fire interacts with oil
            updateUp(x,y,moveBy,smoke, smoke);
            spreadFire(x,y);
            return;
        }
//        else if(particleTypeToMove == smoke){
//            updateUp(x,y,moveBy,fire, smoke);
//            return;
//        }

    }

}




void Fire::updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y+move_by );
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y+move_by );
}

void Fire::updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by , y);
}

void Fire::updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by, y+move_by);
}

void Fire::updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+move_by , y);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x+move_by , y);
}

void Fire::updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y+move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y+move_by);
}

void Fire::updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x, y-move_by);
}

void Fire::updateUpLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x-move_by, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x-move_by, y-move_by);
}

void Fire::updateUpRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt)
{
    world.setParticle(nextPrt, x+ move_by, y-move_by);
    world.setParticle(currentPrt, x, y );
    world.setFlag('f', x, y );
    world.setFlag('f', x +move_by, y-move_by);
}
