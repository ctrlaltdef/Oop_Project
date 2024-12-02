#include "Plant.h"
#include "SoilLayer.h"
#include <iostream>

// Default constructor
Plant::Plant() : plantType(""), position(0.f, 0.f), checkWatered(nullptr) {}

// Parameterized constructor
Plant::Plant(const std::string& plantType, const sf::Vector2f& soilPosition, const sf::Texture& textureSheet, std::function<bool(const sf::Vector2f&)> checkWatered)
    : Generic(soilPosition, textureSheet), 
      plantType(plantType), 
      position(soilPosition), 
      checkWatered(checkWatered) {}

sf::Vector2f Plant::getPosition() const{
    return sprite.getPosition();
}

// Getter for plant type
const std::string& Plant::getPlantType() const {
    return plantType;
}
