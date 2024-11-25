#include "SoilLayer.h"
#include "Plant.h"
#include <iostream>
#include <map>

// Constructor
SoilLayer::SoilLayer() {
    // Load soil texture
    if (!soilTexture.loadFromFile("../graphics/soil/o.png")) {
        std::cerr << "Error: Could not load soil texture!" << std::endl;
    }

    // Preload seed textures
    if (!seedTextures["corn"].loadFromFile("../graphics/fruit/corn/0.png")) {
        std::cerr << "Error: Could not load corn texture!" << std::endl;
    }
    if (!seedTextures["tomato"].loadFromFile("../graphics/fruit/tomato/0.png")) {
        std::cerr << "Error: Could not load tomato texture!" << std::endl;
    }

    // Grid dimensions
    int rows = 40; // Total rows in the grid
    int cols = 50; // Total columns in the grid
    grid.resize(rows, std::vector<TileState>(cols));

    // Define farmable areas
    for (int row = 13; row <= 24; ++row) {
        for (int col = 9; col <= 26; ++col) {
            grid[row][col].isFarmable = true;
        }
    }

    // House area (non-farmable)
    for (int row = 15; row <= 22; ++row) {
        for (int col = 18; col <= 24; ++col) {
            grid[row][col].isFarmable = false;
        }
    }

    // Example specific non-farmable tile
    grid[13][12].isFarmable = false;
}

// Convert world position to grid index
sf::Vector2i SoilLayer::getTileIndex(const sf::Vector2f& position) {
    return sf::Vector2i(static_cast<int>(position.x / 64), static_cast<int>(position.y / 64));
}

// Handle soil creation
void SoilLayer::getHit(const sf::Vector2f& position) {
    sf::Vector2i index = getTileIndex(position);

    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];
        if (tile.isFarmable && !tile.hasSoil) {
            tile.hasSoil = true;

            sf::Vector2f tilePosition(index.x * 64, index.y * 64);
            soilTiles.emplace_back(tilePosition, soilTexture);
            std::cout << "Soil patch created at (" << index.y << ", " << index.x << ")" << std::endl;
        } else {
            std::cout << "Tile not farmable or already has soil at (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}

// Handle watering
void SoilLayer::water(const sf::Vector2f& position, const std::string& seed) {
    sf::Vector2i index = getTileIndex(position);

    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];
        if (tile.hasSoil && !tile.isWatered) {
            tile.isWatered = true;
            count = 0;
            sf::Sprite waterSprite;
            if (!waterTexture.loadFromFile("../graphics/soil_water/0.png")) {
                std::cerr << "Error: Could not load water texture!" << std::endl;
                return;
            }

            waterSprite.setTexture(waterTexture);
            waterSprite.setPosition(index.x * 64, index.y * 64);
            waterSprites.push_back(waterSprite);
            std::cout << "Watered soil patch at (" << index.y << ", " << index.x << ")" << std::endl;
        } 
        else if (tile.hasSoil && tile.hasPlant && count < 4 &&tile.isWatered) {
            tile.isWatered = true;
            count += 1;
            sf::Sprite waterSprite;
            if (!waterTexture.loadFromFile("../graphics/soil_water/0.png")) {
                std::cerr << "Error: Could not load water texture!" << std::endl;
                return;
            }

            waterSprite.setTexture(waterTexture);
            waterSprite.setPosition(index.x * 64, index.y * 64);
            waterSprites.push_back(waterSprite);
            std::cout << "Watered soil patch at (" << index.y << ", " << index.x << ")" << std::endl;

            update_plants(position, seed, count);
        }
        else {
            std::cout << "Cannot water this tile: (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}

// Handle planting seeds
void SoilLayer::plant_seeds(const sf::Vector2f& target_pos, const std::string& seed) {
    sf::Vector2i index = getTileIndex(target_pos);

    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];
        if (tile.hasSoil && tile.isWatered && !tile.hasPlant) {
            tile.hasPlant = true;

            sf::Vector2f tilePosition(index.x * 64, index.y * 64);

            // Use preloaded texture
            sf::Texture& texture = seedTextures[seed];

            auto waterCheckFunc = [&tile](const sf::Vector2f&) {
                return tile.isWatered;
            };

            plants.emplace_back(seed, tilePosition, texture, waterCheckFunc);
            tile.plant = &plants.back();

            sf::Sprite plantSprite;
            plantSprite.setTexture(texture);
            plantSprite.setPosition(tilePosition);
            plantSprites.push_back(plantSprite);

            std::cout << "Planted seed '" << seed << "' at (" << index.y << ", " << index.x << ")" << std::endl;
        } 
        else {
            std::cerr << "Cannot plant seed here at (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}

// Update plant growth
// void SoilLayer::update_plants(const sf::Vector2f& target_pos, const std::string& seed, int count) {
//     for (auto& plant : plants) {
//             // Construct the new texture path based on the seed and count
//             std::string texturePath = "../graphics/fruit/" + seed + "/" + std::to_string(count) + ".png";
            
//             if (!seedTextures[seed].loadFromFile(texturePath)) {
//                 std::cerr << "Error: Could not load texture for " << seed << " at stage " << count << "!" << std::endl;
//                 continue;
//             }
//     }

//     // Update corresponding plant sprites
//     // plantSprites.clear();
//     for (auto& plant : plants) {
//         sf::Sprite plantSprite;
//         plantSprite.setTexture(seedTextures[seed]);
//         plantSprite.setPosition(target_pos); // Assume `getPosition()` gets the plant's position
//         plantSprites.push_back(plantSprite);
//     }

//     std::cout << "Plants updated to growth stage: " << count << std::endl;
// }
void SoilLayer::update_plants(const sf::Vector2f& target_pos, const std::string& seed, int count) {
    sf::Vector2i index = getTileIndex(target_pos);

    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];
        if (tile.hasPlant) {
            // Construct the new texture path for the specific seed and growth stage
            std::string texturePath = "../graphics/fruit/" + seed + "/" + std::to_string(count) + ".png";
            if (!seedTextures[seed].loadFromFile(texturePath)) {
                std::cerr << "Error: Could not load texture for " << seed << " at stage " << count << "!" << std::endl;
                return;
            }

            // Update the corresponding plant sprite
            for (auto& plantSprite : plantSprites) {
                if (plantSprite.getPosition() == sf::Vector2f(index.x * 64, index.y * 64)) {
                    plantSprite.setTexture(seedTextures[seed]);
                    break;
                }
            }

            std::cout << "Updated plant at (" << index.y << ", " << index.x << ") to stage " << count << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}


// Draw method
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
