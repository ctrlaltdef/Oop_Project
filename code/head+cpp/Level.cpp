#include "Level.h"
#include <cmath>  // Include cmath for mathematical functions like sqrt and pow

// Constructor: Initializes the level, camera, and game objects such as player, overlay, and market
Level::Level(sf::RenderWindow& window)
    : window(window), player(sf::Vector2f(500, 300), window), overlay(window, &player), sky(window), market(), marketActive(false) {
    setup();  // Set up the initial state of the level
    camera.setSize(static_cast<sf::Vector2f>(window.getSize()));  // Set camera size to match window size
    camera.setCenter(player.getPosition());  // Center the camera on the player
}

// Setup method: Initializes the background, player position, and other components of the level
void Level::setup() {
    // Load background texture and set up the background sprite
    backgroundTexture.loadFromFile("../graphics/world/ground1.png");
    background.setTexture(backgroundTexture);

    // Apply scaling factor to the background to adjust size
    float scaleFactor = 0.8f;
    background.setScale(scaleFactor, scaleFactor);

    // Calculate the width and height of the ground based on the texture size and scaling factor
    sf::Vector2u textureSize = backgroundTexture.getSize();
    groundWidth = textureSize.x * scaleFactor;
    groundHeight = textureSize.y * scaleFactor;

    // Set the background sprite's position to (0, 0)
    background.setPosition(0, 0);

    // Set the player's initial position to the center of the ground
    player.setPosition(sf::Vector2f(groundWidth / 2.0f, groundHeight / 2.0f));

    // Add the background to the drawables list
    drawables.push_back(&background);

    // Initialize soil layer and associate it with the player
    soilLayer = SoilLayer();
    player.setSoilLayer(&soilLayer);
}

// Template function to clamp a value between a minimum and maximum value
template <typename T>
T clamp(const T& value, const T& min, const T& max) {
    if (value < min) return min;  // Return the minimum value if the input is less than the minimum
    if (value > max) return max;  // Return the maximum value if the input is greater than the maximum
    return value;  // Return the original value if it's within the range
}

// Main game loop: Updates and draws game objects and checks for market interactions
void Level::run(float dt) {
    player.update(dt);  // Update the player's state (e.g., movement, animation)
    checkMarketProximity();  // Check if the player is near the market for interaction

    // Get the player's position and dimensions
    sf::Vector2f playerPos = player.getPosition();
    float playerWidth = player.getSprite().getGlobalBounds().width;
    float playerHeight = player.getSprite().getGlobalBounds().height;

    // Clamp the player's position to keep it within the boundaries of the ground
    playerPos.x = clamp(playerPos.x, 0.0f, groundWidth - playerWidth);
    playerPos.y = clamp(playerPos.y, 0.0f, groundHeight - playerHeight);
    player.setPosition(playerPos);

    // Update the camera's position based on the player's position
    sf::Vector2f viewCenter = player.getPosition();
    sf::Vector2f viewSize = camera.getSize();

    // Clamp the camera's center to prevent it from moving out of bounds
    viewCenter.x = clamp(viewCenter.x, viewSize.x / 2, groundWidth - viewSize.x / 2);
    viewCenter.y = clamp(viewCenter.y, viewSize.y / 2, groundHeight - viewSize.y / 2);

    camera.setCenter(viewCenter);  // Set the camera's center position
    window.setView(camera);  // Apply the camera view to the window

    window.clear(sf::Color::Black);  // Clear the window with a black color

    // Draw all drawable objects (background, sky, soil layer, player, etc.)
    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    // Draw the soil layer and player
    soilLayer.draw(window);
    player.draw(window);

    // If the market is active, render the market UI and handle interactions
    if (marketActive) {
        market.render(window, player.getInventory(), player.getMoney());
        handleMarketInteraction();
    }

    // Display the overlay and sky elements
    overlay.display(camera);
    sky.display(dt);

    window.display();  // Display the rendered content on the window
}

// Check if the player is near the market and can interact with it
void Level::checkMarketProximity() {
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f marketPos(700, 300);  // Hardcoded market position (could be dynamic)

    // Calculate the distance between the player and the market using Euclidean distance formula
    float distance = std::sqrt(std::pow(playerPos.x - marketPos.x, 2) +
                               std::pow(playerPos.y - marketPos.y, 2));

    // If the player is close enough and presses the 'M' key, activate the market
    if (distance < 100.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        marketActive = true;
    } 
    // If the market is active and the player presses the 'Escape' key, deactivate the market
    else if (marketActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        marketActive = false;
    }
}

// Handle market interactions such as buying and selling items using specific keys
void Level::handleMarketInteraction() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        market.buyItem("Corn Seed", 1, player);  // Buy Corn Seed when 'Q' is pressed
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        market.sellItem("Corn Crop", 1, player);  // Sell Corn Crop when 'W' is pressed
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        market.buyItem("Tomato Seed", 1, player);  // Buy Tomato Seed when 'E' is pressed
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        market.sellItem("Tomato Crop", 1, player);  // Sell Tomato Crop when 'R' is pressed
    }
}
