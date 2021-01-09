#include "sand.h"
#include <iostream>
Sand::Sand()
{
    vel = 10; // sand speed
    velSandInWater = 2;
}

//move by vel, but if there is rock, skip moving forward
//tworza sie kwadraty o vel
bool Sand::moveSand(int& x, int& y)
{
    int moveBy=0;
    bool is_go = false;

    //down ================:
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x, y+z );
        if(lookUpPrt == 'n'){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break; //when it breaks moveBy is z-1 and as so goes to is_go

    } //end for

    if(is_go){ //else go down by velocity

        updateDown(x, y, moveBy , 'f');
        return 1;
    }


    //down left ===========:
    is_go= false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x-z, y+z );
        if(lookUpPrt == 'n'){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break;
    }
    if(is_go)
    {
        updateDownLeft(x, y, moveBy, 'f');
        return 1;
    }

    //down right ==========:
    is_go= false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x+z, y+z );
        if(lookUpPrt == 'n' ){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break;

    }
    if(is_go)
    {
        updateDownRight(x, y, moveBy, 'f');
        return 1;
    }
    return 0;
}

bool Sand::moveSandInWater(int &x, int &y)
{
    int velSandInWater = 2;
    int moveBy=0;
    bool is_go = false;

    for (int z = 1; z <= velSandInWater; ++z) {
        lookUpPrt = world.getParticle(x, y+z );
        if(lookUpPrt == 'w'){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break; //when it breaks moveBy is z-1 and as so goes to is_go

    } //end for

    if(is_go){ //else go down by velocity
        updateWaterDown(x, y, moveBy , 'f');
        return 1;
    }


    //down left ===========:
    is_go= false;
    for (int z = 1; z <= velSandInWater; ++z) {
        lookUpPrt = world.getParticle(x-z, y+z );
        if(lookUpPrt == 'w'){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break;
    }
    if(is_go)
    {
        updateWaterDownLeft(x, y, moveBy, 'f');
        return 1;
    }

    //down right ==========:
    is_go= false;
    for (int z = 1; z <= velSandInWater; ++z) {
        lookUpPrt = world.getParticle(x+z, y+z );
        if(lookUpPrt == 'w' ){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break;

    }
    if(is_go)
    {
        updateWaterDownRight(x, y, moveBy, 'f');
        return 1;
    }

    return 0; // no match
}

void Sand::moveSandInOil(int &x, int &y)
{
    int velSandInWater = 2;
    int moveBy=0;
    bool is_go = false;

    for (int z = 1; z <= velSandInWater; ++z) {
        lookUpPrt = world.getParticle(x, y+z );
        if(lookUpPrt == 'o'){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break; //when it breaks moveBy is z-1 and as so goes to is_go

    } //end for

    if(is_go){ //else go down by velocity
        updateOilDown(x, y, moveBy , 'f');
        return;
    }


    //down left ===========:
    is_go= false;
    for (int z = 1; z <= velSandInWater; ++z) {
        lookUpPrt = world.getParticle(x-z, y+z );
        if(lookUpPrt == 'o'){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break;
    }
    if(is_go)
    {
        updateOilDownLeft(x, y, moveBy, 'f');
        return;
    }

    //down right ==========:
    is_go= false;
    for (int z = 1; z <= velSandInWater; ++z) {
        lookUpPrt = world.getParticle(x+z, y+z );
        if(lookUpPrt == 'o' ){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'r') break;

    }
    if(is_go)
    {
        updateOilDownRight(x, y, moveBy, 'f');
        return;
    }
}

//jiggering of the solid elements is caused by flag n
void Sand::updateDownLeft(int&  x, int&  y, int&  move_by, char flag)
{
    //std::cout << "updateDownLeft" << std::endl;
    world.setParticle('n', x, y );
    world.setParticle('s', x-move_by , y+move_by );
    world.setFlag(flag, x-move_by , y+move_by );
}

void Sand::updateDownRight(int  x, int  y, int  move_by, char flag)
{
    //std::cout << "updateDownRight" << std::endl;
    world.setParticle('n', x, y );
    world.setParticle('s', x+move_by, y+move_by);
    world.setFlag(flag, x+move_by, y+move_by);
}



void Sand::updateDown(int&  x, int&  y, int&  move_by, char flag)
{
    //std::cout << "updateDown" << std::endl;
    world.setParticle('n', x, y );
    world.setParticle('s', x, y+move_by);
    world.setFlag(flag, x, y+move_by);
}

// Sand into WATER:
void Sand::updateWaterDown(int &x, int &y, int &move_by, char flag)
{
    //std::cout << "updateWaterDown" << std::endl;
    world.setParticle('w', x, y );
    world.setParticle('s', x, y+move_by);
    world.setFlag('f', x, y+move_by);
}

void Sand::updateWaterDownLeft(int &x, int &y, int &move_by, char flag)
{
    //std::cout << "updateWaterDownLeft" << std::endl;
    world.setParticle('w', x, y );
    world.setParticle('s', x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
}

void Sand::updateWaterDownRight(int x, int y, int move_by, char flag)
{
    //std::cout << "updateWaterDownRight" << std::endl;
    world.setParticle('w', x, y );
    world.setParticle('s', x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
}

// Sand into OIL:
void Sand::updateOilDown(int &x, int &y, int &move_by, char flag)
{
    //std::cout << "updateWaterDown" << std::endl;
    world.setParticle('o', x, y );
    world.setParticle('s', x, y+move_by);
    world.setFlag('f', x, y+move_by);
}

void Sand::updateOilDownLeft(int &x, int &y, int &move_by, char flag)
{
    //std::cout << "updateWaterDownLeft" << std::endl;
    world.setParticle('o', x, y );
    world.setParticle('s', x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
}

void Sand::updateOilDownRight(int x, int y, int move_by, char flag)
{
    //std::cout << "updateWaterDownRight" << std::endl;
    world.setParticle('o', x, y );
    world.setParticle('s', x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
}
