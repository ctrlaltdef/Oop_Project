#ifndef PLANT_H
#define PLANT_H
#include "SoilLayer.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>



class Plant {
public:
    Plant();
    Plant(const std::string& plantType, const sf::Vector2f& soilPosition, const sf::Texture& textureSheet, std::function<bool(const sf::Vector2f&)> checkWatered);
    void max(int count);                  // Handle plant growth
    void draw(sf::RenderWindow& window); // Render plant on screen

    bool isHarvestable() const;   // Check if the plant is ready for harvest


private:
    // Plant setup
    sf::Texture texture;
    sf::Texture image;  
    std::string plantType;
    std::vector<sf::Sprite> frames; // Frames representing growth stages
    sf::Sprite sprite;              // Current sprite for rendering
    sf::Vector2f position;          // Position of the plant
    std::function<bool(const sf::Vector2f&)> checkWatered; // Callback for water check


    // Growth mechanics
    float age = 0.0f;            // Current age of the plant
    float growSpeed;             // Growth speed (based on type)
    int maxAge;                  // Maximum growth stage index
    bool harvestable = false;    // Whether the plant is harvestable
    int yOffset;                 // Adjust sprite positioning
};

#endif
