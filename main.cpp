#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
#include "water.h"
#include "sand.h"
#include "world.h"
const int Width = 800 ;
const int Hight = 800 ;
int particle_button;
char matrix[Width*Hight];
char flags[Width*Hight];
int number =0;

Water water;
World world;
Sand sand;
int vel = 15;

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

    buttons_v.push_back(sandButton);
    buttons_v.push_back(rockButton);
    buttons_v.push_back(waterButton);
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
    enum particles_enum {SAND, ROCK, WATER};

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
            for (int i = 0; i < 15 ; ++i) {
                world.setParticle('s', clickPosi.x + addX, clickPosi.y +addY);
                //setFlag('n', clickPosi.x + addX, clickPosi.y +addY); //- creates invisible sand if mouse not moved
                addX++;
                 //addY++;
                number++;
                //if(clickPosi.x + addX> Width || clickPosi.y +addY > Hight)
                //  return;
            }
        }
        break;
        case ROCK:
        {
            for (int i = 0; i < 10 ; ++i) {
                world.setParticle('r', clickPosi.x + addX, clickPosi.y +addY);
                //setFlag('f', clickPosi.x + addX, clickPosi.y +addY);
                addX++;

                number++;
            }
        }
        break;
        case WATER:
        {
            for (int i = 0; i < 100 ; ++i) {
                world.setParticle('w', clickPosi.x + addX, clickPosi.y +addY);
                //setFlag('f', clickPosi.x + addX, clickPosi.y +addY);
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


void update()
{
    for (int y = 0; y < Hight ; ++y) {
        for (int x = 0; x < Width ; ++x) { // the 15 prevents moviing to the other end of the window

            if(world.getFlag(x,y) == 'f') continue;
            char currentC   = world.getParticle(x,y);
            if(currentC == 'n' || currentC == 'r') continue;


            //std::cout << "===========START============" << std::endl;

            if(currentC == 's')  //SAND
                sand.moveSand(x, y);

            if(currentC == 'w')  //WATER
                water.moveWater(x, y);

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

    std::vector<Button> buttons_v;
    makeOptionButtons(window, buttons_v);
    sf::Texture t;
    if(!t.loadFromFile("D:/Qt_workspace/SFML-Particles/sky.png"))
        std::cout << "loading image failed" << std::endl;
    sf::Sprite s(t);




    for (int y = 0; y < Hight ; ++y) {
        for (int x = 0; x < Width; ++x) {
            world.setParticle('n', x, y);
            world.setFlag('n', x, y);
        }
    }

    //make sand bottom
    for (int y = Hight-vel; y < Hight    ; ++y) {
        for (int x = 0; x < Width  ; ++x) {
            world.setParticle('s', x, y);
            world.setFlag('f', x, y);
        }
    }


    sf::VertexArray va;
    va.setPrimitiveType(sf::Points);
    sf::Vertex v;



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
                    if(std::rand()%2 == 1)
                        v.color = sf::Color(34, 97, 149);
                    else
                        v.color = sf::Color(47, 47, 255);
                    v.position.x = x;
                    v.position.y = y;
                    va.append(v);
                }
            }
        }


        update();
        window.draw(va);
        va.clear();

        //these need to be below update and draw so i cant write on buttons
        checkButtonsState(buttons_v, window);
        drawOptionButtons(window, buttons_v);

        window.display();


        for (int y = 0; y < Hight; ++y) {
            for (int x = 0 +vel; x < Width-vel; ++x) { //jiggering of the solid elements is caused by flag n and this +vel prevents it
                world.setFlag('n', x, y);
            }
        }
        //for sand bottom - setting the bottom unmovable prevents distotion and going all image below the window
        for (int y = Hight-vel; y < Hight    ; ++y) {
            for (int x = vel; x < Width-vel ; ++x) {
                world.setFlag('f', x, y);
            }
        }
    }
    return EXIT_SUCCESS;
}
