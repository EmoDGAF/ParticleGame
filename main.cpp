#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
#include "water.h"
#include "sand.h"
#include "world.h"
//#include "oil.h"
//#include "fire.h"
#include "particle.h"
#include "vector"
const int Width = 800;
const int Hight = 800;
int particle_button;
//char matrix[Width*Hight];
char flags[Width*Hight]; //incorporating it inside class slows down the code
char flagsClean[Width*Hight];
int number =0;


std::vector<Particle*> matrix;


//Oil oil;
//Fire fire;
int vel = 15;

World world;

void initialiseFlagsAndCleanFlags()
{
    for (int y = 0; y < Hight; ++y) {
        for (int x = 0 +vel; x < Width-vel; ++x) { //jiggering of the solid elements is caused by flag n and this +vel prevents it
            flags[x+ y*Hight] = 'n';
        }
    }

    //for sand bottom - setting the bottom unmovable prevents distotion and going all image below the window
    for (int y = Hight-vel; y < Hight    ; ++y) {
        for (int x = vel; x < Width-vel ; ++x) {
            flagsClean[x+ y*Hight] = 'n';
        }
    }

    for (int y = Hight-vel; y < Hight    ; ++y) {
        for (int x = 0; x < Width  ; ++x) {
            //world.setParticle('s', x, y);
            flags[x+ y*Hight] = 'f';
            flagsClean[x+ y*Hight] = 'f';
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
    sandButton.setType('s');

    Button rockButton;
    rockButton.setPosition(120,0);
    rockButton.setType('r');

    Button waterButton;
    waterButton.setPosition(140,0);
    waterButton.setType('w');

    Button oilButton;
    oilButton.setPosition(160,0);
    oilButton.setType('o');

    Button fireButton;
    fireButton.setPosition(180,0);
    fireButton.setType('f');

    buttons_v.push_back(sandButton);
    buttons_v.push_back(rockButton);
    buttons_v.push_back(waterButton);
    buttons_v.push_back(oilButton);
    buttons_v.push_back(fireButton);
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
    enum particles_enum {SAND, ROCK, WATER, OIL, FIRE};

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
            for (int i = 0; i < 11    ; ++i) {
                world.setParticle('s', clickPosi.x + addX, clickPosi.y +addY);
                world.setFlag('n', clickPosi.x + addX, clickPosi.y +addY); //- creates invisible sand if mouse not moved

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
                    world.setParticle('r', clickPosi.x + i, clickPosi.y +y);
                }
            }
        }
        break;
//        case OIL:
//        {
//            for (int i = 0; i < 50 ; ++i) {
//                world.setParticle('o', clickPosi.x + addX, clickPosi.y +addY);
//                addY++;
//            }
//        }
        break;
//        case FIRE:
//        {
//            for (int i = 0; i < 10 ; ++i) {
//                world.setParticle('f', clickPosi.x + addX, clickPosi.y +addY);
//                addY++;
//            }
//        }
//        break;
        case WATER:
        {
            for (int i = 0; i < 100 ; ++i) {
                world.setParticle('w', clickPosi.x + addX, clickPosi.y +addY);
                world.setFlag('f', clickPosi.x + addX, clickPosi.y +addY);
                //addX++;
                addY++;
                number++;
            }
        }
        break;
        default:
            break;
        }
    }
}


void update(Sand& sand, Water& water)
{
    for (int y = 0; y < Hight ; ++y) {
        for (int x = 0; x < Width ; ++x) { // the 15 prevents moviing to the other end of the window

            if(world.getFlag(x,y) == 'f') continue;
            char currentC   = world.getParticle(x,y);
            if(currentC == 'n' || currentC == 'r') continue;


            //std::cout << "===========START============" << std::endl;

            if(currentC == 's'){  //SAND
                if(!sand.moveSand(x, y))        //only if sand in air was NOT moved, check if there is possibility to move sand in water
                   if(!sand.moveSandInWater(x, y))  //if sand wasnt moved, move sand in water (otherwise sand gets multiplied in water)
                     sand.moveSandInOil(x,y); //chec sand in oil possibility only if the previous conditions failed - that provides some optimalisation

            }   //moveSand and moveSandInWater cant both be activated, cause moveSand may move current particle and moveSandInWater may move it AGAIN

            if(currentC == 'w')  //WATER
                water.moveWater(x, y);

//            if(currentC == 'o')  //OIL
//                oil.moveOil(x, y);

//            if(currentC == 'f')  //FIRE
//                fire.moveFire(x, y);

        }//end for
    }

}



//        sf::Color upC;
//        sf::Color upleftC;
//        sf::Color uprightC;
//        if(particles_v[i]->getY()-1 >=1){
//            upC = image.getPixel(particles_v[i]->getX(), particles_v[i]->getY()-1);
//            //upleftC  = image.getPixel(particles_v[i]->getX()-1, particles_v[i]->getY()-1);
//            //uprightC = image.getPixel(particles_v[i]->getX()+1, particles_v[i]->getY()-1);
//        }
//       // if( upC ==sf::Color::Yellow && upleftC==sf::Color::Yellow && uprightC==sf::Color::Yellow)
//        if( upC ==sf::Color::Yellow)
//          continue;
//        //optimalisation


//[20:40:19] <~fir> sodaj randa zeby nie spadalo w dol tylko w jeden z 3 dolow



int main()
{
    sf::RenderWindow window(sf::VideoMode(Width, Hight), "SFML window");

    window.setFramerateLimit(100);
    int size = Width*Hight;
    initialiseFlagsAndCleanFlags();

    matrix.reserve(size);
    for (int i = 0; i < size; ++i) {
        Particle* p = new Particle;
        //p->setFlag('n');

        matrix.push_back(p);
    }
    std::cout << "matrix in main: " << matrix.size() << std::endl;
    world.passMatrix(matrix);

    Sand sand(world);
    Water water(world);

    std::vector<Button> buttons_v;
    makeOptionButtons(window, buttons_v);
    sf::Texture t;
    if(!t.loadFromFile("D:/Qt_workspace/SFML-Particles/sky.png"))
        std::cout << "loading image failed" << std::endl;
    sf::Sprite s(t);


    //make sand bottom
    for (int y = Hight-vel; y < Hight    ; ++y) {
        for (int x = 0; x < Width  ; ++x) {
            world.setParticle('s', x, y);
            world.setFlag('f', x, y);
        }
    }

    //make water bed
    for (int y = Hight-vel-30; y < Hight-vel    ; ++y) {
        for (int x = 0; x < Width  ; ++x) {
            world.setParticle('w', x, y);
            world.setFlag('f', x, y);
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
        }

        window.clear();
        window.draw(s); //background

        checkLeftClicks(window);


        //std::cout << "particle_button: " << particle_button << std::endl;
        //Draw:
        for (int y = 0; y < Hight ; ++y) { // Hight -vel would cause we would see bottom sand but it would still be there
            for (int x = 0+vel; x < Width-vel ; ++x) { // +vel and -vel prevents sand sitting on the edges, cause now we DONT DISPLAY edges lol
                if(world.getParticle(x,y) == 's' || world.getParticle(x,y) == 'y'){

                    if(std::rand()%2 == 1)
                        v.color = sf::Color(255, 127, 39);
                    else
                        v.color = sf::Color(255, 199, 4);
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
                else if(world.getParticle(x,y) == 'r')
                {
                    v.color = sf::Color::Magenta;
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
                else if(world.getParticle(x,y) == 'w')
                {
//                    if(std::rand()%2 == 1)
//                        v.color = sf::Color(34, 97, 149);
//                    else
                        v.color = sf::Color(47, 47, 255);
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
//                else if(world.getParticle(x,y) == 'o')
//                {
//                    v.color = sf::Color(136,0,21);
//                    v.position.x = x;
//                    v.position.y = y;
//                    va.append(v);
//                }
//                else if(world.getParticle(x,y) == 'f')
//                {
//                    int r = std::rand()%3;
//                    if(r == 1)
//                        v.color = sf::Color::Red;
//                    else if(r == 2)
//                        v.color = sf::Color(255, 127, 39);
//                    else if(r == 3)
//                        v.color = sf::Color(255, 255, 0);
//                    v.position.x = x;
//                    v.position.y = y;
//                    va.append(v);
//                }
            }
        }


        update(sand, water);
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
