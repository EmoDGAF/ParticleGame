#ifndef SAND_H
#define SAND_H
#include "world.h"


class Sand
{
public:
    Sand(World &world_);
    void moveSand(int &x, int &y);
    bool moveSandInWater(int& x, int &y);
    bool moveSandInOil(int &x, int &y);
private:
    //jiggering of the solid elements is caused by flag n

    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel );

    void updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    void updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    void updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    void updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void moveWaterAsideWhenMovesUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
private:
    World world;
    int vel  ;  //velocity
    int velSandInWater ;
    int velSandInAir ;
    char lookUpPrt;
    int moveBy;

    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';
};

#endif // SAND_H
