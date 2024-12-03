#ifndef SKY_H
#define SKY_H

#include <SFML/Graphics.hpp>  // SFML graphics library for rendering

class Sky {
private:
    sf::RenderWindow& displaySurface;  // Reference to the SFML window for rendering
    sf::RectangleShape fullSurf;       // Rectangle shape to cover the entire window (background)
    sf::Color start_color;             // Starting color of the sky (used for the transition effect)
    sf::Color end_color;               // Ending color of the sky (used for the transition effect)

public:
    // Constructor that takes a window reference to initialize the display surface
    Sky(sf::RenderWindow& window);
    
    // Method to display the sky and handle the color transition over time
    void display(float dt);
};

#endif
