#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button: public sf::RectangleShape
{
private:
    bool isActive;
    char type;

public:
    Button();
    void setState(bool on_off);
    bool getState()const;
    bool checkIfContains(sf::Vector2i clickPos, sf::RenderWindow &window);
    void setType(char t);
    char getType()const;
};

#endif // BUTTON_H
