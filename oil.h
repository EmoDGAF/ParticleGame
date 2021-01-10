#ifndef OIL_H
#define OIL_H
#include "world.h"

class Oil
{
public:
    Oil();
    void moveOil(int& x, int& y);

private:
    void updateDownLeft(int  x, int  y, int  move_by, auto flag);
    void updateLeft(int  x, int  y, int  move_by, auto flag);
    void updateDownRight(int  x, int  y, int  move_by, auto flag);
    void updateRight(int  x, int  y, int  move_by, auto flag);
    void updateDown(int  x, int  y, int  move_by, auto flag);
    void updateUp(int  x, int  y, int  move_by, auto flag);
    void updateUpLeft(int  x, int  y, int  move_by, auto flag);
    void updateUpRight(int  x, int  y, int  move_by, auto flag);
//try:
    void updateUnderWaterLeft(int  x, int  y, int  move_by, auto flag);
    void updateUnderWaterRight(int  x, int  y, int  move_by, auto flag);

    World world;
    int vel =   10     ; //velocity
    int moveBy;
    char lookUpPrt;
};

#endif // OIL_H
