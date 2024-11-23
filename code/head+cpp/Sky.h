#ifndef SKY_H
#define SKY_H

#include <SFML/Graphics.hpp>

class Sky{

    private:
        sf::RenderWindow& displaySurface;
        sf::RectangleShape fullSurf;
        sf::Color start_color;
        sf::Color end_color;

    public:
        Sky(sf::RenderWindow& window);
        void display(float dt);
};

#endif