#ifndef FIRE_H
#define FIRE_H
#include "world.h"


class Fire
{
public:
    Fire(World& world_);
    void moveFire(int& x, int& y);
    //bool moveFireThroughWood(int& x, int& y);
    void spreadFire(int& x, int& y);

private:
    float checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel , bool is_rand);
    int checkHowFarIsWaterInGivenDir(int x, int y, int dir_x, int dir_y, int vel );
    int checkHowFarIsSmokeObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel);

    void updateDownLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDownRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateDown(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);
    void updateUp(int &x, int &y, int &move_by, char &currentPrt, char &nextPrt);

    //================
    void updateUpLeft(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    void updateUpRight(int&  x, int&  y, int&  move_by, char& currentPrt, char& nextPrt);

    World world;
    int vel =   15     ; //velocity
    float velWoodOnFire;
    int spreadFireVel;
    int moveBy;
    char lookUpPrt;
    char lookUpFlag;
    char particleTypeToMove;
    int velUpFire;

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

#endif // FIRE_H
