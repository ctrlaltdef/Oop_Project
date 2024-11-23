// #ifndef LEVEL_H
// #define LEVEL_H

// #include <SFML/Graphics.hpp>
// #include <vector>
// #include "Player.h"
// #include "Settings.h"
// #include "Overlay.h"
// #include "Generic.h"
// #include "Water.h"
// #include "WildFlower.h"
// #include "Tree.h"
// #include "Sky.h"

// class Level {
// private:
//     sf::RenderWindow& window;
//     std::vector<Generic*> elements; 
//     Player player;
//     Sky sky;
//     Overlay overlay;
//     sf::Sprite background; 
//     sf::Texture backgroundTexture; 
//     std::vector<sf::Drawable*> drawables;
//     sf::View camera;

// public:
//     Level(sf::RenderWindow& window);
//     void setup();
//     void reset(sf::RenderWindow& window);
//     void run(float dt);

// };

// #endif


#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Overlay.h"
#include "Sky.h"
#include "Generic.h"

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

    // Sky effect
    Sky sky;

    // Drawables and elements
    std::vector<sf::Drawable*> drawables;    // All drawable objects
    std::vector<Generic*> elements;         // Game elements with layering
};

#endif // LEVEL_H



