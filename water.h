#ifndef WATER_H
#define WATER_H
#include "world.h"


class Water
{
public:
    Water();
    void moveWater(int& x, int& y);

private:
    void updateDownLeft(int  x, int  y, int  move_by, auto flag);
    void updateLeft(int  x, int  y, int  move_by, auto flag);
    void updateDownRight(int  x, int  y, int  move_by, auto flag);
    void updateRight(int  x, int  y, int  move_by, auto flag);
    void updateDown(int  x, int  y, int  move_by, auto flag);

    World world;
    int vel =   15     ; //velocity
    int moveBy;
    char lookUpPrt;
};

#endif // WATER_H
