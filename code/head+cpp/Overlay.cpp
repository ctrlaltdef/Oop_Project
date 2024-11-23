#include "Overlay.h"
#include <iostream>
#include "Settings.h"

// Constructor
Overlay::Overlay(sf::RenderWindow& window, Player* player)
    : window(window), player(player) {
    // Load tool textures and sprites
    std::string overlayPath = "../graphics/overlay/";
    for (const auto& tool : player->getTools()) {
        sf::Texture toolTexture;
        if (!toolTexture.loadFromFile(overlayPath + tool + ".png")) {
            std::cerr << "Error loading tool texture: " << tool << std::endl;
        }
        toolsTextures[tool] = toolTexture;

        sf::Sprite toolSprite;
        toolSprite.setTexture(toolsTextures[tool]);
        toolsSprites[tool] = toolSprite;
    }

    // Load seed textures and sprites
    for (const auto& seed : player->getSeeds()) {
        sf::Texture seedTexture;
        if (!seedTexture.loadFromFile(overlayPath + seed + ".png")) {
            std::cerr << "Error loading seed texture: " << seed << std::endl;
        }
        seedsTextures[seed] = seedTexture;

        sf::Sprite seedSprite;
        seedSprite.setTexture(seedsTextures[seed]);
        seedsSprites[seed] = seedSprite;
    }
}

// Display method
void Overlay::display(const sf::View& camera) {
    // Adjust overlay position relative to the camera view
    sf::Vector2f cameraCenter = camera.getCenter();
    sf::Vector2f cameraSize = camera.getSize();

    // Calculate screen positions for overlay items
    sf::Vector2f toolScreenPosition = cameraCenter - (cameraSize / 2.f) + OVERLAY_POSITIONS.at("tool");
    sf::Vector2f seedScreenPosition = cameraCenter - (cameraSize / 2.f) + OVERLAY_POSITIONS.at("seed");

    // Display selected tool
    sf::Sprite& toolSprite = toolsSprites[player->getSelectedTool()];
    toolSprite.setPosition(toolScreenPosition);
    window.draw(toolSprite);

    // Display selected seed
    sf::Sprite& seedSprite = seedsSprites[player->getSelectedSeed()];
    seedSprite.setPosition(seedScreenPosition);
    window.draw(seedSprite);
}
