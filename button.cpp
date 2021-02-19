#include "button.h"

Button::Button()
{
    isActive = false;
    this->setSize(sf::Vector2f(20,20));
}

void Button::setState(bool on_off)
{
    isActive = on_off;
}

bool Button::getState() const
{
    return isActive;
}

bool Button::checkIfContains(sf::Vector2i clickPos, sf::RenderWindow& window)
{
    sf::IntRect r(this->getPosition().x, this->getPosition().y, 20,20);
    if(r.contains(clickPos)){
        //std::cout << type << std::endl;
        return true;
    }
    else{
        return false;
    }
}

void Button::setType(char t)
{
    type = t;
    if(type=='w')
        this->setFillColor(sf::Color::Blue);
    else if(type=='r')
        this->setFillColor(sf::Color::Magenta);
    else if(type=='s')
        this->setFillColor(sf::Color::Yellow);
    else if(type=='o')
        this->setFillColor(sf::Color(136,0,21));
    else if(type=='f')
        this->setFillColor(sf::Color::Red);
    else if(type=='d')
        this->setFillColor(sf::Color::Black);
    else if(type == 'v')
        this->setFillColor(sf::Color(124, 78, 52));
}

char Button::getType() const
{
    return type;
}
