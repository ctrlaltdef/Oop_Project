#ifndef SOIL_LAYER_H
#define SOIL_LAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "SoilTile.h"
#include "Plant.h"
#include "Generic.h"

class Player; // Forward declaration of the Player class to avoid circular dependencies

// The SoilLayer class represents a grid-based farming area where players can farm,
// water, plant, and harvest crops. It inherits from the Generic class.
class SoilLayer: public Generic {
protected:
    // Structure to represent the state of an individual tile in the grid
    struct TileState {
        bool isFarmable = false; // Whether the tile can be farmed
        bool hasSoil = false;    // Whether soil has been placed on the tile
        bool isWatered = false;  // Whether the tile has been watered
        bool hasPlant = false;   // Whether there is a plant on the tile
        Plant* plant = nullptr;  // Pointer to the plant object (if any) on the tile
        std::string cropType;    // Type of crop planted on the tile
        int growthCounter = 0;   // Tracks plant growth stages
    };

    std::vector<std::vector<TileState>> grid; // 2D grid of tile states representing the farming area
    std::vector<SoilTile> soilTiles;          // Collection of active soil tiles
    sf::Texture soilTexture;                  // Texture for rendering soil tiles
    sf::Texture waterTexture;                 // Texture for rendering water effects
    std::vector<sf::Sprite> waterSprites;     // Sprites to display watered tiles
    std::vector<sf::Sprite> plantSprites;     // Sprites to display plants on tiles
    sf::Vector2i getTileIndex(const sf::Vector2f& position); // Converts a world position to grid index
    std::vector<Plant> plants;                // List of all plants in the soil layer
    std::map<std::string, std::vector<sf::Texture>> seedTextures; // Textures for different seed types

public:
    // Loads the textures for a given seed type
    std::vector<sf::Texture> loadSeedTextures(const std::string& seed);

    // Constructor
    SoilLayer();

    // Waters the soil tile at the given position and handles seed-related updates
    void water(const sf::Vector2f& position, const std::string& seed);

    // Handles interactions with the grid when a tile is hit
    void getHit(const sf::Vector2f& position);

    // Draws the soil layer and its components (soil, water, plants) on the window
    void draw(sf::RenderWindow& window);

    // Updates the state of plants, including growth and other mechanics
    void update_plants(const sf::Vector2f& target_pos, const std::string& seed, int count, TileState& tile);

    // Plants seeds at the target position, modifies player inventory, and updates the grid
    void plant_seeds(const sf::Vector2f& target_pos, const std::string& seed, Player& player, sf::RenderWindow& window);

    // Harvests the crop at the target position and updates the player state
    void harvest(const sf::Vector2f &target_pos, Player &player); 
};

#endif
