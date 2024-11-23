// #include "Level.h"
// #include <iostream>
// #include "Settings.h"
// #include "Generic.h"
// #include "Water.h"
// #include "WildFlower.h"
// #include "Tree.h"
// #include "Sky.h"

// Level::Level(sf::RenderWindow& window)
//     : window(window), player(sf::Vector2f(540, 300)), overlay(&player), sky(&window) {
//     setup();
//     camera.setSize(static_cast<sf::Vector2f>(window.getSize()));
//     camera.setCenter(player.getPosition());
// }

// void Level::setup() {
//     if (!backgroundTexture.loadFromFile("../graphics/world/ground1.png")) {
//         std::cerr << "Error: Cant load background texture!" << std::endl;
//     }
//     background.setTexture(backgroundTexture);
//     float scaleFactor = 1.0f; 
//     background.setScale(scaleFactor, scaleFactor);

//     sf::Vector2u backgroundSize = backgroundTexture.getSize();
//     sf::Vector2f scaledSize(backgroundSize.x * scaleFactor, backgroundSize.y * scaleFactor);
//     sf::Vector2u screenSize = window.getSize();
//     float centerX = (screenSize.x / 2.0f) - (scaledSize.x / 2.0f);
//     float centerY = (screenSize.y / 2.0f) - (scaledSize.y / 2.0f);
//     background.setPosition(centerX, centerY);

//     drawables.push_back(&background); 
//     drawables.push_back(&player.getSprite()); 
    
// }

// void Level::reset(sf::RenderWindow& window){
//     sf::RectangleShape fullSurf(sf::Vector2f(window.getSize().x, window.getSize().y));
//     fullSurf.setFillColor(sf::Color(255, 255, 255));
// }

// void Level::run(float dt) {
//     camera.setCenter(player.getPosition());
//     window.setView(camera); 
//     window.clear(sf::Color::Black);

//     for (auto& drawable : drawables) {
//         window.draw(*drawable);
//     }


//     for (auto element : elements) {
//         element->update(dt);
//         window.draw(*element); 
//     }

//     std::sort(elements.begin(), elements.end(), [](Generic* a, Generic* b) {
//         return a->z < b->z; 
//     });

//     sky.display(dt);
//     player.update(dt);
//     overlay.display(window);
//     window.display();
// }




#include "Level.h"
#include <iostream>
#include <algorithm> // For std::clamp
#include "Settings.h"
#include "Generic.h"
#include "Water.h"
#include "WildFlower.h"
#include "Tree.h"
#include "Sky.h"

Level::Level(sf::RenderWindow& window)
    : window(window), player(sf::Vector2f(540, 300)), overlay(&player), sky(&window) {
    setup();

    // Initialize the camera view
    camera.setSize(static_cast<sf::Vector2f>(window.getSize()));
    camera.setCenter(player.getPosition());
}

void Level::setup() {
    if (!backgroundTexture.loadFromFile("../graphics/world/ground1.png")) {
        std::cerr << "Error: Can't load background texture!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    float scaleFactor = 1.0f;
    background.setScale(scaleFactor, scaleFactor);

    // Calculate ground dimensions
    sf::Vector2u textureSize = backgroundTexture.getSize();
    groundWidth = textureSize.x * scaleFactor;
    groundHeight = textureSize.y * scaleFactor;

    background.setPosition(0, 0); // Ensure the background starts at (0, 0)

    drawables.push_back(&background);
    drawables.push_back(&player.getSprite());
}

void Level::reset(sf::RenderWindow& window) {
    sf::RectangleShape fullSurf(sf::Vector2f(window.getSize().x, window.getSize().y));
    fullSurf.setFillColor(sf::Color(255, 255, 255));
}
template <typename T>
T clamp(const T& value, const T& min, const T& max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void Level::run(float dt) {
    // Update player position and constrain it to the ground bounds
    player.update(dt);
    sf::Vector2f playerPos = player.getPosition();

    // Constrain player position to stay within ground bounds
    playerPos.x = clamp(playerPos.x, 0.0f, groundWidth);
    playerPos.y = clamp(playerPos.y, 0.0f, groundHeight);
    player.setPosition(playerPos);

    // Update camera to follow the player
    sf::Vector2f viewCenter = player.getPosition();
    sf::Vector2f viewSize = camera.getSize();

    // Constrain camera center to the ground boundaries
    viewCenter.x = clamp(viewCenter.x, viewSize.x / 2, groundWidth - viewSize.x / 2);
    viewCenter.y = clamp(viewCenter.y, viewSize.y / 2, groundHeight - viewSize.y / 2);
    camera.setCenter(viewCenter);

    window.setView(camera); // Apply the updated view

    // Clear the window
    window.clear(sf::Color::Black);

    // Draw all drawable objects
    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    // Sort elements by their "z" value and draw them
    std::sort(elements.begin(), elements.end(), [](Generic* a, Generic* b) {
        return a->z < b->z;
    });

    for (auto element : elements) {
        element->update(dt);
        window.draw(*element);
    }

    // Display overlay and sky
    sky.display(dt);
    overlay.display(window);

    // Present the rendered frame
    window.display();
}










