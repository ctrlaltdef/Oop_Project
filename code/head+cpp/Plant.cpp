#include "Plant.h"
#include "SoilLayer.h"
#include <iostream>

// Default constructor - Initializes plantType to an empty string, position to (0, 0), and checkWatered to nullptr
Plant::Plant() : plantType(""), position(0.f, 0.f), checkWatered(nullptr) {}

// Parameterized constructor - Initializes the plant with its type, position, texture, and checkWatered function
Plant::Plant(const std::string& plantType, const sf::Vector2f& soilPosition, const sf::Texture& textureSheet, std::function<bool(const sf::Vector2f&)> checkWatered)
    : Generic(soilPosition, textureSheet),  // Calls the parent class constructor with soil position and texture
      plantType(plantType),  // Initializes plant type
      position(soilPosition), // Initializes plant position in the soil
      checkWatered(checkWatered) {}  // Initializes the checkWatered function

// Getter for position - Returns the position of the plant (from the sprite's position)
sf::Vector2f Plant::getPosition() const {
    return sprite.getPosition();  // Returns the current position of the plant sprite
}

// Getter for plant type - Returns the plant type (e.g., "Carrot", "Tomato")
const std::string& Plant::getPlantType() const {
    return plantType;  // Returns the plant type
}
