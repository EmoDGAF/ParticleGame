#ifndef FIRE_H
#define FIRE_H
#include "world.h"


class Fire
{
public:
    Fire(World& world_);
    bool moveFire(int& x, int& y);
    bool interact(char &particleToInteract, int& x, int& y);

private:
    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel );
    int checkHowFarIsWaterInGivenDir(int x, int y, int dir_x, int dir_y, int vel );

    void updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateUp(int &x, int &y, int &move_by, char &currentPrt, char &nextPrt);

    World world;
    int vel =   15     ; //velocity
    int moveBy;
    char lookUpPrt;
    char particleTypeToMove;

    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';
    char smoke = 'd';
};

#endif // FIRE_H
