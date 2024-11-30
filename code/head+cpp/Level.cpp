// #include "Level.h"
// #include <iostream>
// #include <algorithm> 
// #include "Settings.h"
// #include "Sky.h"
// #include "MarketUI.h"

// Level::Level(sf::RenderWindow& window)
//     : window(window), player(sf::Vector2f(500, 300)), overlay(window, &player), sky(window),  market(), marketActive(false) {
//     setup();

//     // Initialize the camera view
//     camera.setSize(static_cast<sf::Vector2f>(window.getSize()));

//     // Center the camera on the player's position
//     camera.setCenter(player.getPosition());
// }

// void Level::setup() {
//     if (!backgroundTexture.loadFromFile("../graphics/world/ground1.png")) {
//         std::cerr << "Error: Can't load background texture!" << std::endl;
//     }
//     background.setTexture(backgroundTexture);

//     float scaleFactor = 0.8f;
//     background.setScale(scaleFactor, scaleFactor);

//     // Calculate ground dimensions
//     sf::Vector2u textureSize = backgroundTexture.getSize();
//     groundWidth = textureSize.x * scaleFactor;
//     groundHeight = textureSize.y * scaleFactor;

//     background.setPosition(0, 0); // Ensure the background starts at (0, 0)

//     // Calculate the center of the ground
//     sf::Vector2f groundCenter(groundWidth / 2.0f, groundHeight / 2.0f);

//     // Set the player at the center of the ground
//     player.setPosition(groundCenter);

//     // Add background and player sprite to the drawable objects
//     drawables.push_back(&background);
//     drawables.push_back(&player.getSprite());

//     soilLayer = SoilLayer(); // Initialize SoilLayer
//     player.setSoilLayer(&soilLayer); // Pass SoilLayer to the Player



// }

// void Level::reset(sf::RenderWindow& window) {
//     sf::RectangleShape fullSurf(sf::Vector2f(window.getSize().x, window.getSize().y));
//     fullSurf.setFillColor(sf::Color(255, 255, 255));
// }

// template <typename T>
// T clamp(const T& value, const T& min, const T& max) {
//     if (value < min) return min;
//     if (value > max) return max;
//     return value;
// }

// void Level::run(float dt) {
//     // Update player position and constrain it to the ground bounds
//     player.update(dt); // Update the player at the start

//     sf::Vector2f playerPos = player.getPosition();
//     float playerWidth = player.getSprite().getGlobalBounds().width;
//     float playerHeight = player.getSprite().getGlobalBounds().height;

//     playerPos.x = clamp(playerPos.x, 0.0f, groundWidth - playerWidth);
//     playerPos.y = clamp(playerPos.y, 0.0f, groundHeight - playerHeight);

//     player.setPosition(playerPos);

//     // Constrain camera center to the ground boundaries
//     sf::Vector2f viewCenter = player.getPosition();
//     sf::Vector2f viewSize = camera.getSize();

//     viewCenter.x = clamp(viewCenter.x, viewSize.x / 2, groundWidth - viewSize.x / 2);
//     viewCenter.y = clamp(viewCenter.y, viewSize.y / 2, groundHeight - viewSize.y / 2);

//     camera.setCenter(viewCenter);
//     window.setView(camera); // Apply the updated view

//     // Clear the window
//     window.clear(sf::Color::Black);

//     // Draw static elements (e.g., terrain or ground-level elements)
//     for (auto& drawable : drawables) {
//         window.draw(*drawable);
//     }

//     // Update and draw soil patches
//     soilLayer.draw(window);
//     // Draw the player (ensures player is above soil and other elements)
//     player.draw(window);

//     // Draw overlays (e.g., HUD, status effects)
//     overlay.display(camera);

//     // Draw sky (background element)
//     sky.display(dt);


//     // Present the rendered frame
//     window.display();
// }


#include "Level.h"
#include <iostream>
#include <algorithm> 
#include "Settings.h"
#include "Sky.h"
#include "MarketUI.h"
#include "Player.h"
#include <cmath>

// Constructor
Level::Level(sf::RenderWindow& window)
    : window(window), player(sf::Vector2f(500, 300)), overlay(window, &player), sky(window), market(), marketActive(false) {
    setup();

    // Initialize the camera view
    camera.setSize(static_cast<sf::Vector2f>(window.getSize()));
    camera.setCenter(player.getPosition());
}

// Setup function
void Level::setup() {
    if (!backgroundTexture.loadFromFile("../graphics/world/ground1.png")) {
        std::cerr << "Error: Can't load background texture!" << std::endl;
    }
    background.setTexture(backgroundTexture);

    float scaleFactor = 0.8f;
    background.setScale(scaleFactor, scaleFactor);

    // Calculate ground dimensions
    sf::Vector2u textureSize = backgroundTexture.getSize();
    groundWidth = textureSize.x * scaleFactor;
    groundHeight = textureSize.y * scaleFactor;

    background.setPosition(0, 0); // Ensure the background starts at (0, 0)

    // Calculate the center of the ground
    sf::Vector2f groundCenter(groundWidth / 2.0f, groundHeight / 2.0f);

    // Set the player at the center of the ground
    player.setPosition(groundCenter);

    // Add background and player sprite to the drawable objects
    drawables.push_back(&background);
    drawables.push_back(&player.getSprite());

    soilLayer = SoilLayer(); // Initialize SoilLayer
    player.setSoilLayer(&soilLayer); // Pass SoilLayer to the Player
}

// Reset function
void Level::reset(sf::RenderWindow& window) {
    sf::RectangleShape fullSurf(sf::Vector2f(window.getSize().x, window.getSize().y));
    fullSurf.setFillColor(sf::Color(255, 255, 255));
}

// Template clamp function
template <typename T>
T clamp(const T& value, const T& min, const T& max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Run function
void Level::run(float dt) {
    // Update player position and constrain it to the ground bounds
    player.update(dt); // Update the player at the start
    checkMarketProximity();

    sf::Vector2f playerPos = player.getPosition();
    float playerWidth = player.getSprite().getGlobalBounds().width;
    float playerHeight = player.getSprite().getGlobalBounds().height;

    playerPos.x = clamp(playerPos.x, 0.0f, groundWidth - playerWidth);
    playerPos.y = clamp(playerPos.y, 0.0f, groundHeight - playerHeight);

    player.setPosition(playerPos);

    // Constrain camera center to the ground boundaries
    sf::Vector2f viewCenter = player.getPosition();
    sf::Vector2f viewSize = camera.getSize();

    viewCenter.x = clamp(viewCenter.x, viewSize.x / 2, groundWidth - viewSize.x / 2);
    viewCenter.y = clamp(viewCenter.y, viewSize.y / 2, groundHeight - viewSize.y / 2);

    camera.setCenter(viewCenter);
    window.setView(camera); // Apply the updated view

    // Clear the window
    window.clear(sf::Color::Black);

    // Check proximity to the market
    checkMarketProximity();

    // Draw static elements (e.g., terrain or ground-level elements)
    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    // Update and draw soil patches
    soilLayer.draw(window);

    // Draw the player (ensures player is above soil and other elements)
    player.draw(window);

    // If the market is active, draw its UI
    if (marketActive) {
         market.render(window, player.getInventory()); // Pass inventory to the market UI
        handleMarketInteraction();
    }

    // Draw overlays (e.g., HUD, status effects)
    overlay.display(camera);

    // Draw sky (background element)
    sky.display(dt);

    // Present the rendered frame
    window.display();
}

void Level::checkMarketProximity() {
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f marketPos(700, 300); // Example market position

    float distance = std::sqrt(std::pow(playerPos.x - marketPos.x, 2) +
                               std::pow(playerPos.y - marketPos.y, 2));

    if (distance < 100.0f) { // If close to the market
        if (!marketActive) {
            std::cout << "Press E to open the market" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            marketActive = true;
        }
    } else {
        if (marketActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            marketActive = false;
        }
    }
}


void Level::handleMarketInteraction() {
    int& playerMoney = player.getMoney();  // Get player's money as a reference

    // Example: Buying or selling a specific item (e.g., "Corn")
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        if (market.buyItem("Corn", 1, playerMoney)) { // Buy 1 corn
            player.getInventory().addItem("Corn", 1); // Add 1 corn to inventory
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (market.sellItem("Corn", 1, playerMoney)) { // Sell 1 corn
            player.getInventory().removeItem("Corn", 1); // Remove 1 corn from inventory
        }
    }
}

