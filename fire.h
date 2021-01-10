#ifndef FIRE_H
#define FIRE_H
#include "world.h"

class Fire
{
public:
    Fire();
    void moveFire(int& x, int& y);

private:
    void updateDownLeft(int  x, int  y, int  move_by);
    void updateLeft(int  x, int  y, int  move_by);
    void updateDownRight(int  x, int  y, int  move_by);
    void updateRight(int  x, int  y, int  move_by);
    void updateDown(int  x, int  y, int  move_by);

    World world;
    int vel =   6     ; //velocity
    int moveBy;
    char lookUpPrt;
};

#endif // FIRE_H
