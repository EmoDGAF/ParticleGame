#include "sand.h"
#include <iostream>
Sand::Sand()
{
    vel = 10; // sand speed
    velSandInWater = 2;
}

//move by vel, but if there is rock, skip moving forward
//tworza sie kwadraty o vel
void Sand::moveSand(int& x, int& y)
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
        else if(lookUpPrt == 'r') break;
        else if(lookUpPrt == 'w') updateWaterDown(x, y, velSandInWater, 'f');


    } //end for

    if(is_go){ //else go down by velocity

        updateDown(x, y, moveBy , 'f');
        return;
    }


    //down left ===========:
    is_go= false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x-z, y+z );
        if(lookUpPrt == 'n'){
            moveBy =z;
            is_go = true;
        }
        else if(lookUpPrt == 'w') updateWaterDownLeft(x, y, velSandInWater, 'f');
        else if(lookUpPrt == 'r') break;

    }
    if(is_go)
    {
        updateDownLeft(x, y, moveBy, 'f');
        return;
    }

    //down right ==========:
    is_go= false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x+z, y+z );
        if(lookUpPrt == 'n' ){
            moveBy =z;
            is_go = true;
        }

        else if(lookUpPrt == 'w') updateWaterDownRight(x, y, velSandInWater, 'f');
        else if(lookUpPrt == 'r') break;
    }
    if(is_go)
    {
        updateDownRight(x, y, moveBy, 'f');
        return;
    }


}

//jiggering of the solid elements is caused by flag n
void Sand::updateDownLeft(int&  x, int&  y, int&  move_by, char flag)
{
    world.setParticle('n', x, y );
    world.setParticle('s', x-move_by , y+move_by );
    world.setFlag(flag, x-move_by , y+move_by );
}

void Sand::updateDownRight(int  x, int  y, int  move_by, char flag)
{
    world.setParticle('n', x, y );
    world.setParticle('s', x+move_by, y+move_by);
    world.setFlag(flag, x+move_by, y+move_by);
}



void Sand::updateDown(int&  x, int&  y, int&  move_by, char flag)
{
    //std::cout << "y+move_by: " << y+move_by << std::endl;
    // if(y+move_by >   Hight)
    //move_by = 0;


    world.setParticle('n', x, y );
    world.setParticle('s', x, y+move_by);
    world.setFlag(flag, x, y+move_by);
    return;
}

// Sand into WATER:
void Sand::updateWaterDown(int &x, int &y, int &move_by, char flag)
{
    //std::cout << "updateWaterDown" << std::endl;
    world.setParticle('w', x, y );
    world.setParticle('s', x, y+move_by);
    world.setFlag('f', x, y+move_by);
    return;
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
