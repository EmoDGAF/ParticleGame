#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
#include "water.h"
#include "sand.h"
#include "world.h"
#include "oil.h"
#include "fire.h"
#include "particle.h"
#include "vector"
#include <random>
#include <algorithm>
#include "smoke.h"
#include "wood.h"

#define FPS 100
const int Width = 800;
const int Hight = 800;
int particle_button;
//char matrix[Width*Hight];
char flags[Width*Hight]; //incorporating it inside class slows down the code
char flagsClean[Width*Hight];
int number =0;
int buttonYsize = 20;

std::vector<Particle*> matrix;


int vel = 20;

World world;
char fire = 'f';
char oil = 'o';
char water = 'w';
char rock = 'r';
char sand = 's';
char air = 'n';
char smoke = 'd';
char wood = 'v';

char f = 'f';
char n = 'n';

void initialiseFlagsAndCleanFlags()
{
    for (int y = 0; y < Hight; ++y) {
        for (int x = 0 +vel; x < Width-vel; ++x) { //jiggering of the solid elements is caused by flag n and this +vel prevents it
            flags[x+ y*Hight] = n;
        }
    }

    //for sand bottom - setting the bottom unmovable prevents distotion and going all image below the window
    for (int y = Hight-vel; y < Hight    ; ++y) {
        for (int x = vel; x < Width-vel ; ++x) {
            flagsClean[x+ y*Hight] = n;
        }
    }

    for (int y = Hight-vel; y < Hight    ; ++y) {
        for (int x = 0; x < Width  ; ++x) {
            //world.setParticle('s', x, y);
            flags[x+ y*Hight] = f;
            flagsClean[x+ y*Hight] = f;
        }
    }
}

void cleanFlags()
{
    std::copy(std::begin(flagsClean), std::end(flagsClean), std::begin(flags));
    //flags = flagsClean;
}

void drawOptionButtons(sf::RenderWindow& window, std::vector<Button>& buttons_v)
{
    for (auto i : buttons_v) {
        window.draw(i);
    }
}

void makeOptionButtons(sf::RenderWindow& window, std::vector<Button>& buttons_v)
{
    Button sandButton;
    sandButton.setPosition(100,0);
    sandButton.setType(sand);

    Button rockButton;
    rockButton.setPosition(120,0);
    rockButton.setType(rock);

    Button waterButton;
    waterButton.setPosition(140,0);
    waterButton.setType(water);

    Button oilButton;
    oilButton.setPosition(160,0);
    oilButton.setType(oil);

    Button fireButton;
    fireButton.setPosition(180,0);
    fireButton.setType(fire);

    Button smokeButton;
    smokeButton.setPosition(200, 0);
    smokeButton.setType(smoke);

    Button woodButton;
    woodButton.setPosition(220, 0);
    woodButton.setType(wood);

    buttons_v.push_back(sandButton);
    buttons_v.push_back(rockButton);
    buttons_v.push_back(waterButton);
    buttons_v.push_back(oilButton);
    buttons_v.push_back(fireButton);
    buttons_v.push_back(smokeButton);
    buttons_v.push_back(woodButton);
}

void checkButtonsState(std::vector<Button>& buttons_v, sf::RenderWindow& window)
{
    sf::Vector2i clickPos = sf::Mouse::getPosition(window);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ //without it buttons functions would ba activated without clicking
        for (int i = 0; i < buttons_v.size(); ++i) {
            if(buttons_v[i].checkIfContains(clickPos, window)){
                buttons_v[i].setState(true);
                particle_button = i;

            }
            //else particle_button =0; //lol

        }
    }
}


//here we re just adding particles, the particles have different positions, the vector doesnt order them by their position
void checkLeftClicks(sf::RenderWindow& window)
{
    enum particles_enum {SAND, ROCK, WATER, OIL, FIRE, SMOKE, WOOD};

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        //std::cout << "pixels: " << number << std::endl;
        //std::cout << "particles: " << particles_v.size() << std::endl;
        sf::Vector2i clickPosi = sf::Mouse::getPosition(window);
        sf::Vector2f clickPos= static_cast<sf::Vector2f>(clickPosi);
        int addX=0;
        int addY=0;

        switch (particle_button) {
        case SAND:
        {
            for (int i = 0; i < 10 ; ++i) {
                world.setParticle(sand, clickPosi.x + addX, clickPosi.y +addY);
                //world.setFlag(n, clickPosi.x + addX, clickPosi.y +addY); //- creates invisible sand if mouse not moved

                 addX++;
                //addY++;
                //number++;
                //if(clickPosi.x + addX> Width || clickPosi.y +addY > Hight)
                //  return;
            }
        }
        break;
        case ROCK:
        {
            for (int i = 0; i < 10 ; ++i) {
                for (int y = 0; y < 10; ++y) {
                    world.setParticle(rock, clickPosi.x + i, clickPosi.y +y);
                }
            }
        }
        break;
        case OIL:
        {
            for (int i = 0; i < 110  ; ++i) {
                world.setParticle(oil, clickPosi.x + addX, clickPosi.y +addY);
                addX++;
            }
        }
        break;
        case FIRE:
        {
            for (int i = 0; i < 20 ; ++i) {
                world.setParticle(fire, clickPosi.x + addX, clickPosi.y +addY);
                addX++;
            }
        }
        break;
        case WATER:
        {
            for (int i = 0; i < 100 ; ++i) {
                world.setParticle(water, clickPosi.x + addX, clickPosi.y +addY);
               // world.setFlag(f, clickPosi.x + addX, clickPosi.y +addY);
                 addX++;
                //addY++;
                //number++;
            }
        }
        break;
        case SMOKE:
        {
            for (int i = 0; i < 10 ; ++i) {
                world.setParticle(smoke, clickPosi.x + addX, clickPosi.y +addY);
                addX++;
            }
        }
        break;
        case WOOD:
        {
            for (int i = 0; i < 20 ; ++i) {
                for (int y = 0; y < 20; ++y) {
                    world.setParticle(wood, clickPosi.x + i, clickPosi.y +y);
                }
            }
        }
        break;
        default:
            break;
        }
    }
}



void updateUpLeft(Sand& sandClass, Water& waterClass, Oil& oilClass, Fire& fireClass, Smoke& smokeClass, Wood& woodClass) //its for normal particles, gases should be rervesed
{
    for (int y = Hight-1; y >= 0+buttonYsize ; --y) { //0+buttonYsize so we avoid interacting with type buttons
        for (int x = Width-1; x >= 0 ; --x) { // the 15 prevents moviing to the other end of the window

            if(world.getFlag(x,y) == f) continue;
            char currentC   = world.getParticleType(x,y);
            if(currentC == air || currentC == rock) continue;

            if(currentC == sand)
                sandClass.moveSand(x, y);


            if(currentC == water) //WATER
                waterClass.moveWater(x, y);

            if(currentC == oil) //Oil
                oilClass.moveOil(x,y);

            if(currentC == fire) //Fire
                fireClass.moveFire(x, y);

            if(currentC == smoke ) //Smoke
                smokeClass.moveSmoke(x,y);

            if(currentC == wood)
                woodClass.moveWood(x,y);
        }//end for
    }
}

void updateUpRight(Sand& sandClass, Water& waterClass, Oil& oilClass, Fire& fireClass, Smoke& smokeClass, Wood& woodClass) //its for normal particles, gases should be rervesed
{


    for (int y = Hight-1; y <= 0+buttonYsize ; --y) {
        for (int x = 0; x < Width ; ++x) { // the 15 prevents moviing to the other end of the window

            if(world.getFlag(x,y) == f) continue;
            char currentC   = world.getParticleType(x,y);
            if(currentC == air || currentC == rock) continue;

            if(currentC == sand)
                sandClass.moveSand(x, y);


            if(currentC == water) //WATER
                waterClass.moveWater(x, y);

            if(currentC == oil) //Oil
                oilClass.moveOil(x,y);

            if(currentC == fire) //Fire
                fireClass.moveFire(x, y);


            if(currentC == smoke) //Smoke
                smokeClass.moveSmoke(x,y);

            if(currentC == wood)
                woodClass.moveWood(x,y);
        }//end for
    }
}



void updateLeft(Sand& sandClass, Water& waterClass, Oil& oilClass, Fire& fireClass, Smoke& smokeClass, Wood& woodClass) //its for normal particles, gases should be rervesed
{
    for (int y = 0+buttonYsize; y < Hight-1 ; ++y) { //0+vel so to avoid interacting with type buttons
        for (int x = Width-1; x >= 0 ; --x) { // the 15 prevents moviing to the other end of the window

            if(world.getFlag(x,y) == f) continue;
            char currentC   = world.getParticleType(x,y);
            if(currentC == air || currentC == rock) continue;

            if(currentC == sand)
                sandClass.moveSand(x, y);

            if(currentC == water) //WATER
                waterClass.moveWater(x, y);

            if(currentC == oil) //Oil
                oilClass.moveOil(x,y);

            if(currentC == fire) //Fire
                fireClass.moveFire(x, y);


            if(currentC == smoke) //Smoke
                smokeClass.moveSmoke(x,y);

            if(currentC == wood)
                woodClass.moveWood(x,y);
        }//end for
    }
}

void updateRight(Sand& sandClass, Water& waterClass, Oil& oilClass, Fire& fireClass, Smoke& smokeClass, Wood& woodClass) //its for normal particles, gases should be rervesed
{


    for (int y = 0+buttonYsize; y < Hight-1 ; ++y) {
        for (int x = 0; x < Width ; ++x) { // the 15 prevents moviing to the other end of the window

            if(world.getFlag(x,y) == f) continue;
            char currentC   = world.getParticleType(x,y);
            if(currentC == air || currentC == rock) continue;

            if(currentC == sand)
                sandClass.moveSand(x, y);

            if(currentC == water) //WATER
                waterClass.moveWater(x, y);

            if(currentC == oil) //Oil
                oilClass.moveOil(x,y);

            if(currentC == fire) //Fire
                fireClass.moveFire(x, y);


            if(currentC == smoke) //Smoke
                smokeClass.moveSmoke(x,y);

            if(currentC == wood)
                woodClass.moveWood(x,y);
        }//end for
    }
}

static int switcher = 0;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Width, Hight), "SFML window");

    window.setFramerateLimit(FPS);
    int size = Width*Hight;
    initialiseFlagsAndCleanFlags();

    matrix.reserve(size);
    for (int i = 0; i < size; ++i) {
        Particle* p = new Particle;
        //p->setFlag(n);

        matrix.push_back(p);
    }
    std::cout << "matrix in main: " << matrix.size() << std::endl;
    world.passMatrix(matrix);

    Sand sandClass(world);
    Water waterClass(world);
    Oil oilClass(world);
    Fire fireClass(world);
    Smoke smokeClass(world);
    Wood woodClass(world);

    std::vector<Button> buttons_v;
    makeOptionButtons(window, buttons_v);
    sf::Texture t;
    if(!t.loadFromFile("D:/Qt_workspace/SFML-Particles/sky.png"))
        std::cout << "loading image failed" << std::endl;
    sf::Sprite s(t);


    //make sand bottom
    for (int y = Hight-vel; y < Hight    ; ++y) {
        for (int x = 0; x < Width  ; ++x) {
            world.setParticle(sand, x, y);
            world.setFlag(f, x, y);
        }
    }

    //make water bed
    for (int y = Hight-vel-30; y < Hight-vel    ; ++y) {
        for (int x = 0; x < Width  ; ++x) {
            world.setParticle(water, x, y);
            world.setFlag(f, x, y);
        }
    }

    sf::VertexArray va;
    va.setPrimitiveType(sf::Points);
    sf::Vertex v;

    std::cout << "matrix address in main: " << &matrix << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }

        window.clear();
        //window.draw(s); //background

        checkLeftClicks(window);


        //std::cout << "particle_button: " << particle_button << std::endl;
        //Draw:
        for (int y = 0; y < Hight ; ++y) { // Hight -vel would cause we would see bottom sand but it would still be there
            for (int x = 0+vel; x < Width-vel ; ++x) { // +vel and -vel prevents sand sitting on the edges, cause now we DONT DISPLAY edges lol
                if(world.getParticleType(x,y) == sand ){

                    if(std::rand()%2 == 1)
                        v.color = sf::Color(255, 127, 39);
                    else
                        v.color = sf::Color(255, 199, 4);
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
                else if(world.getParticleType(x,y) == rock)
                {
                    v.color = sf::Color::Magenta;
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
                else if(world.getParticleType(x,y) == water)
                {
//                    if(std::rand()%2 == 1)
//                        v.color = sf::Color(34, 97, 149);
//                    else
                        v.color = sf::Color(47, 47, 255);
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
                else if(world.getParticleType(x,y) == oil)
                {
                    v.color = sf::Color(136,0,21);
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                 }
                else if(world.getParticleType(x,y) == fire)
                {
                    int r = std::rand()%4;
                    if(r == 0)
                        v.color = sf::Color(244, 28, 36);
                    else if(r == 1)
                        v.color = sf::Color(255, 0, 5);
                    else if(r == 2)
                        v.color = sf::Color(255, 122, 5);
                    else if(r == 3)
                        v.color = sf::Color(255, 3, 50);

                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
                 else if(world.getParticleType(x,y) == smoke) //smoke
                 {
                    int r = std::rand()%2;
                    if(r == 1)
                        v.color = sf::Color(195,195,195);
                    else
                        v.color = sf::Color(101,118,118);

                     v.position.x = x;
                     v.position.y = y;
                     va.append(v);
                 }
                else if(world.getParticleType(x,y) == wood)
                {
                    v.color = sf::Color(124, 78, 52);
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }

            }
        }


          // updateLeft(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);




//        if(switcher==0){
//            updateLeft(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);
//            switcher=1;
//        }
//        else if(switcher==1)
//        {
//            updateUpLeft(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);
//            switcher =2;
//        }
//        else if(switcher==2)
//        {
//            updateRight(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);
//            switcher =3;
//        }
//        else if(switcher==3)
//        {
//            updateUpRight(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);
//            switcher =0;
//        }


                if(switcher==0){
                    updateLeft(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);
                    switcher=1;
                }
                else if(switcher==1)
                {
                    updateUpLeft(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);
                    switcher =2;
                }
                else if(switcher==2)
                {
                    updateUpRight(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);

                    switcher =3;
                }
                else if(switcher==3)
                {
                     updateRight(sandClass, waterClass, oilClass, fireClass, smokeClass, woodClass);
                    switcher =0;
                }

        window.draw(va);
        va.clear();


        //these need to be below update and draw so i cant write on buttons
        checkButtonsState(buttons_v, window);
        drawOptionButtons(window, buttons_v);

        window.display();

        cleanFlags();

    }
    return EXIT_SUCCESS;
}
