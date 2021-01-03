#ifndef WORLD_H
#define WORLD_H

extern const int Hight;
extern const int Width;

extern char matrix[];
extern char flags[];
class World
{
public:
    World();


    void setParticle(char t, int x, int y);

    char getParticle(int x, int y);

    void setFlag(char f, int x, int y);

    char getFlag(int x, int y);
public:


};

#endif // WORLD_H
