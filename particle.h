#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>


class Particle
{
public:
    Particle();

    void settype(char t);
    char getType();
 
    char type;
    //char flag;
    int x;
    int y;
//    bool addPosAndcheckPosIfGoesUp(int x, int y);
    std::vector<int> prevPos_v;
//    char getFlag();
//    char setFlag(char f);

};

#endif // PARTICLE_H
