#ifndef SOIL_LAYER_H
#define SOIL_LAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "SoilTile.h"
#include "Plant.h"

class SoilLayer {
public:
    SoilLayer();
    void water(const sf::Vector2f& position);
    void getHit(const sf::Vector2f& position); // Handle interactions with the grid
    void draw(sf::RenderWindow& window);       // Draw soil patches

    //plants
    void update_plants();
    void plant_seeds(const sf::Vector2f& target_pos, const std::string& seed);

private:
    struct TileState {
        bool isFarmable = false; // Whether the tile can be farmed
        bool hasSoil = false;    // Whether soil has been placed on the tile
        bool isWatered = false;
        bool hasPlant = false;
        Plant* plant = nullptr;
    };

    std::vector<std::vector<TileState>> grid; // 2D grid of tile states represeting farming area
    std::vector<SoilTile> soilTiles;          // Active soil patches
    sf::Texture soilTexture;                  // Texture for soil patches
    sf::Texture waterTexture;
    std::vector<sf::Sprite> waterSprites;
    std::vector<sf::Sprite> plantSprites;
    sf::Vector2i getTileIndex(const sf::Vector2f& position); // Convert position to grid index
    std::vector<Plant> plants;


    
};

#endif
