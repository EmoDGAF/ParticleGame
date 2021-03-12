#ifndef WATER_H
#define WATER_H
#include "world.h"


class Water
{
public:
    Water(World& world_);
    void moveWater(int& x, int& y);

private:
    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int &vel );
    void updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    void setSandVelocitytoType(char& particleTypeToMove, int& vel);
    bool disperseWater(int &x, int &y);

    int number4 =0;
    World world;
    int vel     ; //velocity
    int moveBy;
    char lookUpPrt;
    char particleTypeToMove;
    char lookUpFlag;
    int velSides;

    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';
    char wood = 'v';
    char smoke = 'd';
};

#endif // WATER_H
