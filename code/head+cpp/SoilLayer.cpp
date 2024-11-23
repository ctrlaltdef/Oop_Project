#include "SoilLayer.h"
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
    return sf::Vector2i(static_cast<int>(position.x) / 64, static_cast<int>(position.y) / 64);
}

void SoilLayer::getHit(const sf::Vector2f& position) {
    sf::Vector2i index = getTileIndex(position); // Convert position to grid index
    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];
        if (tile.isFarmable  && !tile.hasSoil) {
            tile.hasSoil = true;
           
            soilTiles.emplace_back(sf::Vector2f(index.x * 64, index.y * 64), soilTexture);
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


void SoilLayer::draw(sf::RenderWindow& window) {
    for (auto& tile : soilTiles) {
        tile.draw(window);
    }
    for (auto& waterSprite : waterSprites) {
        window.draw(waterSprite);
    }
}

