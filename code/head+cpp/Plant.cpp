#include "Plant.h"
#include "SoilLayer.h"
#include <iostream>

// Constructor
Plant::Plant(const std::string& plantType, const sf::Vector2f& soilPosition, const sf::Texture& textureSheet, std::function<bool(const sf::Vector2f&)> checkWatered)
    : plantType(plantType), position(soilPosition), checkWatered(checkWatered) {
}

