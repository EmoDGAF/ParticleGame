#ifndef OIL_H
#define OIL_H
#include "world.h"


class Oil
{
public:
    Oil(World& world_);
    void moveOil(int& x, int& y);

private:
    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel);
    int  checkHowFarIsWaterInGivenDir(int x, int y, int dir_x, int dir_y, int vel);
    bool disperseOil(int &x, int &y);
    void setOilVelocitytoType(char& particleTypeToMove, int& vel);

    void updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
/*in water: */
    void updateUp(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateUpRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateUpLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);



    World world;
    int vel; //velocity
    int moveBy;
    char lookUpPrt;
    char lookUpFlag;
    char particleTypeToMove;

    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';
    char smoke = 'd';
    char wood = 'v';
};

#endif // OIL_H
