#ifndef WATER_H
#define WATER_H
#include "world.h"


class Water
{
public:
    Water(World& world_);
    void moveWater(int& x, int& y);

private:
    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel );
    void updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    World world;
    int vel =   6     ; //velocity
    int moveBy;
    char lookUpPrt;

    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';
};

#endif // WATER_H
