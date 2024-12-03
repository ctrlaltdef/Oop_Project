#ifndef PLANT_H
#define PLANT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "Generic.h"  // Including the Generic class header, assumed to be a base class

class SoilLayer;  // Forward declaration of the SoilLayer class

// Plant class inherits from Generic class
class Plant : public Generic {
public:
    // Default constructor
    Plant();
    
    // Parameterized constructor
    Plant(const std::string& plantType, const sf::Vector2f& soilPosition, const sf::Texture& textureSheet, std::function<bool(const sf::Vector2f&)> checkWatered);

    // Getter for plant type
    const std::string& getPlantType() const;
    
    // Override method to get the position of the plant
    sf::Vector2f getPosition() const override;

private:
    std::string plantType;  // Type of the plant (e.g., "Tomato", "Carrot")
    sf::Vector2f position;  // Position of the plant in the soil
    std::function<bool(const sf::Vector2f&)> checkWatered;  // A function to check if the plant has been watered
};

#endif
