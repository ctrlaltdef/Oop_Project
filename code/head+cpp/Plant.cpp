#include "Plant.h"
#include <iostream>

// Constructor
Plant::Plant(const std::string& plantType, const sf::Vector2f& soilPosition, const sf::Texture& textureSheet, std::function<bool(const sf::Vector2f&)> checkWatered)
    : plantType(plantType), position(soilPosition), checkWatered(checkWatered) {

    // Corrected texture loading in C++
    std::string texturePath = "../graphics/fruit/" + plantType + ".png";
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return; // Handle texture loading failure
    }

    // Setup frames for growth stages
    for (int i = 0; i < 4; ++i) {
        sf::Sprite frame(texture);
        frame.setTextureRect(sf::IntRect(i * 64, 0, 64, 64)); // Assuming each frame is 64x64
        frames.push_back(frame);
    }

    // Initial setup
    sprite = frames[0];
    sprite.setPosition(soilPosition);
    yOffset = (plantType == "corn") ? -16 : -8;
    sprite.move(0, yOffset);

    // Growth settings
    growSpeed = (plantType == "corn") ? 0.05f : 0.1f; // Example speeds
    maxAge = frames.size() - 1;
}

// Grow the plant
void Plant::grow() {
    if (checkWatered(position)) {
        age += growSpeed;

        if (age >= maxAge) {
            age = maxAge;
            harvestable = true;
        }

        sprite = frames[static_cast<int>(age)];
        sprite.setPosition(position);
        sprite.move(0, yOffset);
    }
}

// Check if plant is harvestable
bool Plant::isHarvestable() const {
    return harvestable;
}

// Draw the plant
void Plant::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
