#include "water.h"

Water::Water()
{

}

void Water::moveWater(int& x, int& y)
{
    bool is_go = false;
    //down ================:
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x, y+z );
        if(lookUpPrt == 'n'){
            is_go = true;
            moveBy =z; // moveBy becomes the last z fulfilling the if condition
        }
        else if(lookUpPrt == 'r' || lookUpPrt == 's') break;
    }
    if(is_go){
        updateDown(x, y, moveBy, 'f');
        return; // means: continue, skip the for loop and dont go to "down left" and "down right"
    }



    //down left ===========:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x-z, y+z );
        if(lookUpPrt == 'n'){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 'r' || lookUpPrt == 's') break;
    }
    if(is_go){
        updateDownLeft(x, y, moveBy, 'f');
        return; // means: continue, skip the for loop and dont go to "down right"
    }

    //down right ==========:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x+z, y+z );
        if(lookUpPrt == 'n'){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 'r' || lookUpPrt == 's') break;
    }
    if(is_go){
        updateDownRight(x, y, moveBy, 'f');
        return; // = continue
    }

    //right ================:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x+z, y);
        if(lookUpPrt == 'n'){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 's' || lookUpPrt == 'r') break;
    }
    if(is_go){
        updateRight(x, y, moveBy, 'f');
        return; // = continue
    }

    //left ================:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x-z, y);
        if(lookUpPrt == 'n'){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 's' || lookUpPrt == 'r') break;
    }
    if(is_go){
        updateLeft(x, y, moveBy, 'f');
        return; // = continue
    }
}


void Water::updateDownLeft(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('w', x-move_by , y+move_by );
    world.setFlag(flag, x-move_by , y+move_by );
}

void Water::updateLeft(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('w', x-move_by , y);
    world.setFlag(flag, x-move_by , y);
}

void Water::updateDownRight(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('w', x+move_by, y+move_by);
    world.setFlag(flag, x+move_by, y+move_by);
}

void Water::updateRight(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('w', x+move_by , y);
    world.setFlag(flag, x+move_by , y);
}

void Water::updateDown(int  x, int  y, int  move_by, auto flag)
{
    //std::cout << "y+move_by: " << y+move_by << std::endl;
//    if(y+move_by >   Hight)
//        move_by = 0;
    world.setParticle('n', x, y );
    world.setParticle('w', x, y+move_by);
    world.setFlag(flag, x, y+move_by);
}
