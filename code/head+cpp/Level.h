#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Overlay.h"
#include "Sky.h"
#include "Generic.h"
#include "SoilLayer.h"

class Level {
public:
    // Constructor
    Level(sf::RenderWindow& window);

    // Member functions
    void setup();
    void reset(sf::RenderWindow& window);
    void run(float dt);
private:
    sf::RenderWindow& window;            // Reference to the main game window
    sf::View camera;                     // Camera view for the level

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite background;

    // Ground boundaries
    float groundWidth = 0.0f;
    float groundHeight = 0.0f;

    // Player and UI elements
    Player player;
    Overlay overlay;
    SoilLayer soilLayer;


    // Sky effect
    Sky sky;

    // Drawables and elements
    std::vector<sf::Drawable*> drawables;    // All drawable objects
    std::vector<Generic*> elements;         // Game elements with layering
};

#endif // LEVEL_H



