#ifndef PLANT_H
#define PLANT_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
// #include "SoilLayer.h"

class SoilLayer;
class Plant {
public:
    Plant();
    Plant(const std::string& plantType, const sf::Vector2f& soilPosition, const sf::Texture& textureSheet, std::function<bool(const sf::Vector2f&)> checkWatered);
    const std::string& getPlantType() const;
private:
    std::string plantType; 
    sf::Vector2f position;        
    std::function<bool(const sf::Vector2f&)> checkWatered; 
};

#endif
