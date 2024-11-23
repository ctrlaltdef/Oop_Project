#include "Sky.h"
#include <iostream>


Sky::Sky(sf::RenderWindow* window)
    :displaySurface(window), fullSurf(sf::Vector2f(window->getSize().x, window->getSize().y)),
    start_color(sf::Color(255, 255, 255)), 
    end_color(sf::Color(38, 101, 189)) 
    {
        fullSurf.setFillColor(start_color);
}

void Sky::display(float dt){
    const float transitionRate = 0.000215f;

    if (start_color.r > end_color.r) {
        start_color.r -= (transitionRate * dt);
    }
    
    if (start_color.g > end_color.g) {
        start_color.g -= (transitionRate * dt);
    }
    
    if (start_color.b > end_color.b) {
        start_color.b -= (transitionRate * dt);
    }

    if ((start_color.r <= end_color.r) && (start_color.g <= end_color.g) && (start_color.b <= end_color.b)){
        start_color.r = 255;
        start_color.g = 255;
        start_color.b = 255;
    }

    fullSurf.setFillColor(start_color);
    displaySurface->draw(fullSurf, sf::BlendMultiply);
}