#ifndef SAND_H
#define SAND_H
#include "world.h"


class Sand
{
public:
    Sand(World &world_);
    bool moveSandinAir(int &x, int &y);
    bool moveSandInWater(int &x, int &y);
    bool moveSandInOil(int &x, int &y);
private:
    //jiggering of the solid elements is caused by flag n

    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel );

    void updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    void updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    void updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);


    void moveWaterAsideWhenMovesUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
private:
    World world;

    int velSandInWater ;
    int velSandInAir ;
    int velSandInOil ;
    char lookUpPrt;
    char lookUpFlag;
    int moveBy;
    char particleTypeToMove;

    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';
    char wood = 'v';
};

#endif // SAND_H
