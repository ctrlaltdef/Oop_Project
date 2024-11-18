#include "Overlay.h"
#include <cmath>
#include <iostream>
using namespace std;
#include "Settings.h" // Assuming this includes OVERLAY_POSITIONS
#include <SFML/Graphics.hpp>


// Constructor
Overlay::Overlay(Player* player) : player(player) {
    // Load tool textures
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

    // Load seed textures
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
void Overlay::display(sf::RenderWindow& window) {
    // Tool
    sf::Sprite& toolSprite = toolsSprites[player->getSelectedTool()];
    toolSprite.setPosition(OVERLAY_POSITIONS.at("tool"));
    window.draw(toolSprite);

    // Seed
    sf::Sprite& seedSprite = seedsSprites[player->getSelectedSeed()];
    seedSprite.setPosition(OVERLAY_POSITIONS.at("seed"));
    window.draw(seedSprite);
}