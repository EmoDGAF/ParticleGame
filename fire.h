#ifndef FIRE_H
#define FIRE_H
#include "world.h"

class Fire
{
public:
    Fire();
    void moveFire(int& x, int& y);

private:
    void updateDown(int&  x, int&  y, int move_by, char& currentPrt, char& nextPrt);
    void updateDownLeft(int&  x, int&  y, int&  move_by, char &currentPrt, char &nextPrt);
    void updateLeft(int&  x, int&  y, int&  move_by, char &currentPrt, char &nextPrt);
    void updateDownRight(int&  x, int&  y, int&  move_by, char &currentPrt, char &nextPrt);
    void updateRight(int&  x, int&  y, int&  move_by, char &currentPrt, char &nextPrt);

    int checkHowFarIsObstacleInGivenDir(int x, int y, int dir_x, int dir_y, int vel );

private:

    World world;
    static const int velfire =   6     ; //velocity
    int vel = 6;
    int moveBy =0;
    char lookUpPrt;
    bool is_go = false;


    char fire = 'f';
    char oil = 'o';
    char water = 'w';
    char rock = 'r';
    char sand = 's';
    char air = 'n';

};

#endif // FIRE_H
