#include "SoilLayer.h"
#include "Plant.h"
#include <iostream>

SoilLayer::SoilLayer() {
    // Load soil texture
    if (!soilTexture.loadFromFile("../graphics/soil/o.png")) {
        std::cerr << "Error: Could not load soil texture!" << std::endl;
    }

    // Define farmable areas
    // Grid dimensions
    int rows = 40; // Total rows in the grid
    int cols = 50; // Total columns in the grid
    grid.resize(rows, std::vector<TileState>(cols));

    // Define farmable area
    for (int row = 13; row <= 24; ++row) {
        for (int col = 9; col <= 26; ++col) {
            grid[row][col].isFarmable = true;
        }
    }
    //house
    for (int row = 15; row <= 22; ++row) {
        for (int col = 18; col <= 24; ++col) {
            grid[row][col].isFarmable = false;
        }
    }
           grid[13][12].isFarmable = false;

    }


sf::Vector2i SoilLayer::getTileIndex(const sf::Vector2f& position) {
    return sf::Vector2i(static_cast<int>(position.x / 64), static_cast<int>(position.y / 64));
}

void SoilLayer::getHit(const sf::Vector2f& position) {
    sf::Vector2i index = getTileIndex(position); // Convert position to grid index
    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];
        if (tile.isFarmable  && !tile.hasSoil) {
            tile.hasSoil = true;
           
           sf::Vector2f tilePosition(index.x * 64, index.y * 64);
            soilTiles.emplace_back(tilePosition, soilTexture);
            std::cout << "Soil patch created at (" << index.y << ", " << index.x << ")" << std::endl;
        }
        else {
            std::cout << "Tile not farmable or already has soil at (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
 }


void SoilLayer::water(const sf::Vector2f& position) {
    sf::Vector2i index = getTileIndex(position); // Convert position to grid index

    // Check if the index is within bounds
    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];

        // Check if the tile has soil and can be watered
        if (tile.hasSoil && !tile.isWatered) {
            tile.isWatered = true;

            sf::Vector2f tilePosition(index.x * 64, index.y * 64);
            // Create water sprite on top of the soil patch
            sf::Sprite waterSprite;
            if (!waterTexture.loadFromFile("../graphics/soil_water/0.png")) {
                std::cerr << "Error: Could not load water texture!" << std::endl;
                return;
            }
            waterSprite.setTexture(waterTexture);
            waterSprite.setPosition(index.x * 64, index.y * 64);
            waterSprites.push_back(waterSprite); // Store the water sprite

            std::cout << "Watered soil patch at (" << index.y << ", " << index.x << ")" << std::endl;
        } else {
            std::cout << "Cannot water this tile: (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}


void SoilLayer::plant_seeds(const sf::Vector2f& target_pos, const std::string& seed) {
    sf::Vector2i index = getTileIndex(target_pos);

    // Check if within bounds
    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];

        // Check if the tile has soil and is watered, and not already planted
        if (tile.hasSoil && tile.isWatered && !tile.hasPlant) {
            tile.hasPlant = true;

            // Create a default texture and function for water checking

            sf::Texture defaultTexture;
            if(seed == "corn"){
                defaultTexture.loadFromFile("../graphics/fruit/corn/0.png");
            }
            else if (seed == "tomato"){
                defaultTexture.loadFromFile("../graphics/fruit/tomato/0.png");
            }

            auto waterCheckFunc = [&tile](const sf::Vector2f&) {
                return tile.isWatered;
            };

            // Now instantiate the plant correctly with all required arguments
            plants.emplace_back(seed, sf::Vector2f(index.x * 64, index.y * 64), defaultTexture, waterCheckFunc);
            tile.plant = &plants.back();

            sf::Sprite plantSprite;
            plantSprite.setTexture(defaultTexture);
            plantSprite.setPosition(index.x * 64, index.y * 64);
            plantSprites.push_back(plantSprite);  // Store the plant sprite

            std::cout << "Planted seed '" << seed << "' at (" << index.y << ", " << index.x << ")" << std::endl;
        } else if (!tile.isWatered) {
            std::cout << "Cannot plant here: Tile is not watered at (" << index.y << ", " << index.x << ")" << std::endl;
        } else {
            std::cout << "Cannot plant here: Tile already has a plant at (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}


void SoilLayer::update_plants() {
    for (auto& plant : plants) {
        plant.grow();
    }
}

void SoilLayer::draw(sf::RenderWindow& window) {
    for (auto& tile : soilTiles) {
        tile.draw(window);
    }
    for (auto& waterSprite : waterSprites) {
        window.draw(waterSprite);
    }
    for (auto& plantSprite : plantSprites) {
        window.draw(plantSprite);
    }
}


