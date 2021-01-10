#include "fire.h"

Fire::Fire()
{

}

void Fire::moveFire(int& x, int& y)
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
        updateDown(x, y, moveBy);
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
        updateDownLeft(x, y, moveBy);
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
        updateDownRight(x, y, moveBy);
        return; // = continue
    }

    /*Side Movement*/

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
        updateRight(x, y, moveBy);
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
        updateLeft(x, y, moveBy);
        return; // = continue
    }

/*INTERACTIONS*/



}


void Fire::updateDownLeft(int  x, int  y, int  move_by)
{
    world.setParticle('n', x, y );
    world.setParticle('f', x-move_by , y+move_by );
    world.setFlag('f', x-move_by , y+move_by );
}

void Fire::updateLeft(int  x, int  y, int  move_by)
{
    world.setParticle('n', x, y );
    world.setParticle('f', x-move_by , y);
    world.setFlag('f', x-move_by , y);
}

void Fire::updateDownRight(int  x, int  y, int  move_by)
{
    world.setParticle('n', x, y );
    world.setParticle('f', x+move_by, y+move_by);
    world.setFlag('f', x+move_by, y+move_by);
}

void Fire::updateRight(int  x, int  y, int  move_by)
{
    world.setParticle('n', x, y );
    world.setParticle('f', x+move_by , y);
    world.setFlag('f', x+move_by , y);
}

void Fire::updateDown(int  x, int  y, int  move_by)
{
    //std::cout << "y+move_by: " << y+move_by << std::endl;
    //    if(y+move_by >   Hight)
    //        move_by = 0;
    world.setParticle('n', x, y );
    world.setParticle('f', x, y+move_by);
    world.setFlag('f', x, y+move_by);
}
