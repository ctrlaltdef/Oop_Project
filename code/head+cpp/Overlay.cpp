#include "Overlay.h"

// Constructor initializes textures and sprites for the tools and seeds
Overlay::Overlay(sf::RenderWindow& window, Player* player)
    : window(window), player(player) {
    std::string overlayPath = "../graphics/overlay/";  // Path to the overlay images

    // Load textures and create sprites for each tool the player has
    for (const auto& tool : player->getTools()) {
        sf::Texture toolTexture;
        if (toolTexture.loadFromFile(overlayPath + tool + ".png")) {
            toolsTextures[tool] = toolTexture;  // Store the texture
            toolsSprites[tool].setTexture(toolsTextures[tool]);  // Create the sprite
        }
    }

    // Load textures and create sprites for each seed the player has
    for (const auto& seed : player->getSeeds()) {
        sf::Texture seedTexture;
        if (seedTexture.loadFromFile(overlayPath + seed + ".png")) {
            seedsTextures[seed] = seedTexture;  // Store the texture
            seedsSprites[seed].setTexture(seedsTextures[seed]);  // Create the sprite
        }
    }
}

// Displays the selected tool and seed icons on the screen, adjusting positions based on the camera view
void Overlay::display(const sf::View& camera) {
    // Get the center and size of the camera view
    sf::Vector2f cameraCenter = camera.getCenter();
    sf::Vector2f cameraSize = camera.getSize();

    // Calculate the position of the tool and seed icons relative to the camera's position and size
    sf::Vector2f toolPosition = cameraCenter - (cameraSize / 2.f) + OVERLAY_POSITIONS.at("tool");
    sf::Vector2f seedPosition = cameraCenter - (cameraSize / 2.f) + OVERLAY_POSITIONS.at("seed");

    // Get the selected tool sprite and set its position
    auto& toolSprite = toolsSprites[player->getSelectedTool()];
    toolSprite.setPosition(toolPosition);
    window.draw(toolSprite);  // Draw the tool sprite on the window

    // Get the selected seed sprite and set its position
    auto& seedSprite = seedsSprites[player->getSelectedSeed()];
    seedSprite.setPosition(seedPosition);
    window.draw(seedSprite);  // Draw the seed sprite on the window
}
