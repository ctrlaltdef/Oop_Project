#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>   // Include SFML graphics for window, texture, sprite, and view handling
#include <vector>               // Include to use vector container for drawables
#include "Player.h"             // Include Player class for player-related functionality
#include "Overlay.h"            // Include Overlay class for UI or HUD display
#include "Sky.h"                // Include Sky class for background management
#include "SoilLayer.h"          // Include SoilLayer class for managing soil rendering
#include "Market.h"             // Include Market class for market-related interactions

class Level {
public:
    // Constructor: Initializes the level with the window for rendering
    Level(sf::RenderWindow& window);

    // Setup the level, loading textures and initializing components
    void setup();

    // Run the level's update cycle, processing game logic and rendering
    void run(float dt);

    // Handle interactions with the market (e.g., opening, purchasing)
    void handleMarketInteraction();

    // Check if the player is near the market to trigger proximity actions
    void checkMarketProximity();

private:
    sf::RenderWindow& window;  // Reference to the main render window for drawing the level
    sf::View camera;           // Camera view to handle the viewport for rendering

    sf::Texture backgroundTexture;  // Texture for the background image of the level
    sf::Sprite background;          // Sprite to display the background

    float groundWidth = 0.0f;  // Width of the ground, used for level size calculation
    float groundHeight = 0.0f; // Height of the ground, used for level size calculation

    Player player;             // Player object for handling player-specific logic
    Overlay overlay;           // Overlay object for managing UI or HUD elements
    SoilLayer soilLayer;       // SoilLayer object for managing and rendering soil
    Sky sky;                   // Sky object for managing the sky background
    std::vector<sf::Drawable*> drawables; // List of drawable objects to render in the level
    Market market;             // Market object for managing interactions with the in-game market

    bool marketActive;         // Flag indicating whether the market is active or not
};

#endif
