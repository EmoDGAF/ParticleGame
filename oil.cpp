#include "oil.h"
#include <iostream>

Oil::Oil()
{

}

void Oil::moveOil(int& x, int& y)
{
    bool is_go = false;
    /*Down movement*/

    //down
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
        if(lookUpPrt == 'n' ){
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
        return; //
    }

 /*Side movement*/

    //right ================:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x+z, y);
        if(lookUpPrt == 'n' ){
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
        if(lookUpPrt == 'n' ){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 's' || lookUpPrt == 'r') break;
    }
    if(is_go){
        updateLeft(x, y, moveBy, 'f');
        return; // = continue
    }


 /*Upper movement*/

    //Up right ==========:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x+z, y-z );
        if(lookUpPrt == 'w'){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 'r' || lookUpPrt == 's') break;
    }
    if(is_go){
        updateUpRight(x, y, moveBy, 'f');
        return; //
    }

    //Up Left =============:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x-z, y-z );
        if(lookUpPrt == 'w'){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 'r' || lookUpPrt == 's') break;
    }
    if(is_go){
        updateUpLeft(x, y, moveBy, 'f');
        return; // means: continue, skip the for loop and dont go to "down right"
    }

    //Up ================:
    is_go = false;
    for (int z = 1; z <= vel; ++z) {
        lookUpPrt = world.getParticle(x, y-z);
        if(lookUpPrt == 'w'){
            is_go = true;
            moveBy =z;
        }else if(lookUpPrt == 's' || lookUpPrt == 'r') break;
    }
    if(is_go){
        updateUp(x, y, moveBy, 'f');
        return; // = continue
    }


/*underwater side movement*/

    if(std::rand()%2 ==1)
    {
        //right ================:
        is_go = false;
        for (int z = 1; z <= vel; ++z) {
            lookUpPrt = world.getParticle(x+z, y);
            if(lookUpPrt == 'w' ){
                is_go = true;
                moveBy =z;
            }else if(lookUpPrt == 's' || lookUpPrt == 'r') break;
        }
        if(is_go){
            updateUnderWaterRight(x, y, moveBy, 'f');
            return; // = continue
        }
    }
    else{
        //left ===============:
        is_go = false;
        for (int z = 1; z <= vel; ++z) {
            lookUpPrt = world.getParticle(x-z, y);
            if(lookUpPrt == 'w' ){
                is_go = true;
                moveBy =z;
            }else if(lookUpPrt == 's' || lookUpPrt == 'r') break;
        }
        if(is_go){
            updateUnderWaterLeft(x, y, moveBy, 'f');
            return; // = continue
        }

    }







}


void Oil::updateDownLeft(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('o', x-move_by , y+move_by );
    world.setFlag(flag, x-move_by , y+move_by );
}

void Oil::updateLeft(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('o', x-move_by , y);
    world.setFlag(flag, x-move_by , y);
}

void Oil::updateDownRight(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('o', x+move_by, y+move_by);
    world.setFlag(flag, x+move_by, y+move_by);
}

void Oil::updateRight(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('n', x, y );
    world.setParticle('o', x+move_by , y);
    world.setFlag(flag, x+move_by , y);
}

void Oil::updateDown(int  x, int  y, int  move_by, auto flag)
{
    //std::cout << "updateDown" << std::endl;
    world.setParticle('n', x, y );
    world.setParticle('o', x, y+move_by);
    world.setFlag(flag, x, y+move_by);
}

void Oil::updateUp(int  x, int  y, int  move_by, auto flag)
{
    //std::cout << "updateUp" << std::endl;
    world.setParticle('w', x, y );
    world.setParticle('o', x, y-move_by);
    world.setFlag(flag, x, y-move_by);
}

void Oil::updateUpLeft(int  x, int  y, int  move_by, auto flag)
{
    //std::cout << "updateUpLeft" << std::endl;
    world.setParticle('w', x, y );
    world.setParticle('o', x-move_by, y-move_by);
    world.setFlag(flag, x-move_by, y-move_by);
}

void Oil::updateUpRight(int  x, int  y, int  move_by, auto flag)
{
    //std::cout << "updateUpRight" << std::endl;
    world.setParticle('w', x, y );
    world.setParticle('o', x+move_by, y-move_by);
    world.setFlag(flag, x+move_by, y-move_by);
}

//try:
void Oil::updateUnderWaterLeft(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('w', x, y );
    world.setParticle('o', x-move_by , y);
    world.setFlag(flag, x-move_by , y);
}

void Oil::updateUnderWaterRight(int  x, int  y, int  move_by, auto flag)
{
    world.setParticle('w', x, y );
    world.setParticle('o', x+move_by , y);
    world.setFlag(flag, x+move_by , y);
}

