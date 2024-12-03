#include "Overlay.h"

Overlay::Overlay(sf::RenderWindow& window, Player* player)
    : window(window), player(player) {
    std::string overlayPath = "../graphics/overlay/";

    for (const auto& tool : player->getTools()) {
        sf::Texture toolTexture;
        if (toolTexture.loadFromFile(overlayPath + tool + ".png")) {
            toolsTextures[tool] = toolTexture;
            toolsSprites[tool].setTexture(toolsTextures[tool]);
        }
    }

    for (const auto& seed : player->getSeeds()) {
        sf::Texture seedTexture;
        if (seedTexture.loadFromFile(overlayPath + seed + ".png")) {
            seedsTextures[seed] = seedTexture;
            seedsSprites[seed].setTexture(seedsTextures[seed]);
        }
    }
}

void Overlay::display(const sf::View& camera) {
    sf::Vector2f cameraCenter = camera.getCenter();
    sf::Vector2f cameraSize = camera.getSize();

    sf::Vector2f toolPosition = cameraCenter - (cameraSize / 2.f) + OVERLAY_POSITIONS.at("tool");
    sf::Vector2f seedPosition = cameraCenter - (cameraSize / 2.f) + OVERLAY_POSITIONS.at("seed");

    auto& toolSprite = toolsSprites[player->getSelectedTool()];
    toolSprite.setPosition(toolPosition);
    window.draw(toolSprite);

    auto& seedSprite = seedsSprites[player->getSelectedSeed()];
    seedSprite.setPosition(seedPosition);
    window.draw(seedSprite);
}
