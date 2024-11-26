#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Overlay.h"
#include "Sky.h"
#include "SoilLayer.h"
#include "Market.h"

class Level {
public:
    // Constructor
    Level(sf::RenderWindow& window);

    // Member functions
    void setup();
    void reset(sf::RenderWindow& window);
    void run(float dt);
    void setupMarket(); // Initialize market items and prices
    void openMarket();
    void handleEvent(const sf::Event &event);
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

    Market market;

     bool marketActive;

    void checkMarketProximity();
};

#endif // LEVEL_H



