#include "particle.h"
#include <iostream>
Particle::Particle()
{
     type = 'n';
//   flag = 'n';
     x = 0;
     y = 0;
}

void Particle::settype(char t)
{
    type = t;
}

char Particle::getType()
{
    return type;
}

//bool Particle::addPosAndcheckPosIfGoesUp(int x, int y)
//{
//    std::cout << "current y: " << y << " previous y: "  <<  prevPos_v.size()<< std::endl;
//    prevPos_v.push_back(y);
//    if(prevPos_v.size()>=3)
//        prevPos_v.erase(prevPos_v.begin());

//    if(prevPos_v[1]  >y) //check if current y is bigger than previous y position
//        return true;
//    else return false;
//}
