#ifndef SAND_H
#define SAND_H
#include "world.h"

class Sand
{
public:
    Sand();
    void moveSand(int &x, int &y);
private:
    //jiggering of the solid elements is caused by flag n

    //Sand into void:
    void updateDownLeft(int&  x, int&  y, int & move_by, char flag);
    void updateLeft(int&  x, int&  y, int&  move_by, char flag);
    void updateDownRight(int  x, int  y, int  move_by, char flag);
    void updateRight(int&  x, int&  y, int&  move_by, char flag);
    void updateDown(int &x, int &y, int &move_by, char flag);

    //SAND into WATER:
    void updateWaterDown(int &x, int &y, int &move_by, char flag);
    void updateWaterDownLeft(int&  x, int&  y, int & move_by, char flag);
    void updateWaterDownRight(int  x, int  y, int  move_by, char flag);
private:
    World world;
    int vel;  //velocity
    int velSandInWater;
    //int moveBy;
    char lookUpPrt;
};

#endif // SAND_H
