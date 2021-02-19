#ifndef SMOKE_H
#define SMOKE_H
#include "world.h"


class Smoke
{
public:
    Smoke(World &world_);
    void moveSmoke(int &x, int &y);

private:
    //jiggering of the solid elements is caused by flag n

    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel );
    void updateUpLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateUpRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
private:
    World world;
    int vel;  //velocity
    int velSandInWater ;
    int velSandInAir ;
    char lookUpPrt;
    int moveBy;
    char particleTypeToMove;
    char lookUpFlag;

    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';
    char smoke = 'd';
    char smokeDark = 'e';
    char wood = 'v';
};
#endif // SMOKE_H
