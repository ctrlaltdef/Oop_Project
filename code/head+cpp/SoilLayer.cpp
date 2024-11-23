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
    // path
    //   for (int row = 5; row <= 9; ++row) {        
    //         grid[row][5].isFarmable = false;
    //     }
    //     for (int col = 6; col <= 9; ++col) {        
    //         grid[8][col].isFarmable = false;
    //     }
    //     grid[7][8].isFarmable = false;
    //     grid[9][8].isFarmable = false;
    //     grid[9][7].isFarmable = false;
    //     grid[9][6].isFarmable = false;
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




void SoilLayer::draw(sf::RenderWindow& window) {
    for (auto& tile : soilTiles) {
        tile.draw(window);
    }
}

