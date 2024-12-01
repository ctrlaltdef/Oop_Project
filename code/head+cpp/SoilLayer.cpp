#include "SoilLayer.h"
#include <iostream>
#include <map>
#include "Player.h"


// Constructor
SoilLayer::SoilLayer() {
    // Load soil texture
    if (!soilTexture.loadFromFile("../graphics/soil/o.png")) {
        std::cerr << "Error: Could not load soil texture!" << std::endl;
    }

    // Preload seed textures
    seedTextures["corn"] = loadSeedTextures("corn");
    seedTextures["tomato"] = loadSeedTextures("tomato");

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

// Load seed textures for a specific seed
std::vector<sf::Texture> SoilLayer::loadSeedTextures(const std::string& seed) {
    std::vector<sf::Texture> textures;
    for (int i = 0; i < 5; ++i) {  // Assuming you have 5 growth stages
        std::string texturePath = "../graphics/fruit/" + seed + "/" + std::to_string(i) + ".png";
        sf::Texture texture;
        if (!texture.loadFromFile(texturePath)) {
            std::cerr << "Error: Could not load texture for " << seed << " at stage " << i << "!" << std::endl;
        } else {
            textures.push_back(texture);
        }
    }
    return textures;
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
        if (tile.hasSoil) {
            if (!tile.isWatered) {
                tile.isWatered = true;

                // Add water visuals
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

            // Update growth only if crop type matches
            if (tile.hasPlant && tile.isWatered && tile.growthCounter < 3) {
                tile.growthCounter++;
                update_plants(position, tile.cropType, tile.growthCounter, tile);
            }
        } else {
            std::cout << "Cannot water this tile: (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}

void SoilLayer::plant_seeds(const sf::Vector2f& target_pos, const std::string& seed, Player& player, sf::RenderWindow& window) {
    sf::Vector2i index = getTileIndex(target_pos);

    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];

        // Debug output for tile status
        std::cout << "Tile status at (" << index.x << ", " << index.y << "): "
                  << "Has Soil: " << tile.hasSoil
                  << ", Is Watered: " << tile.isWatered
                  << ", Has Plant: " << tile.hasPlant << std::endl;
        
        std::string inventorySeedName;

        if (seed == "tomato") {
            inventorySeedName = "Tomato Seed";
        } else if (seed == "corn") {
            inventorySeedName = "Corn Seed";
        } else {
            inventorySeedName = seed; // Default to the original name if unrecognized
        }

        // Check if the player has enough seeds in the inventory
        int seedCount = player.getInventory().getItemCount(inventorySeedName);
        std::cout << "Player seed count for " << seed << ": " << seedCount << std::endl;

        if (seedCount <= 0) {
            return; // Don't allow planting if no seeds are available
        }
        if (tile.hasSoil && tile.isWatered && !tile.hasPlant) {
            tile.hasPlant = true;
            tile.cropType = seed; // Set the crop type

            sf::Vector2f tilePosition(index.x * 64, index.y * 64);

            // Use the preloaded texture for the seed (initial growth stage)
            sf::Texture& texture = seedTextures[seed][0];

            auto waterCheckFunc = [&tile](const sf::Vector2f&) {
                return tile.isWatered;
            };

            // Create the plant object and associate it with the tile
            plants.emplace_back(seed, tilePosition, texture, waterCheckFunc);
            tile.plant = &plants.back();

            // Create and store the plant sprite
            sf::Sprite plantSprite;
            plantSprite.setTexture(texture);
            plantSprite.setPosition(tilePosition);
            plantSprites.push_back(plantSprite);

            // Remove one seed from the player's inventory after planting
            player.getInventory().removeItem(inventorySeedName, 1);
            std::cout << "Removed 1 seed from player's inventory. New count: " 
                    << player.getInventory().getItemCount(inventorySeedName) << std::endl;




            std::cout << "Planted seed '" << seed << "' at (" << index.y << ", " << index.x << ")" << std::endl;
        } else {
            std::cerr << "Cannot plant seed here at (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}

//plant growth
void SoilLayer::update_plants(const sf::Vector2f& target_pos, const std::string& seed, int count, TileState& tile) {
    sf::Vector2i index = getTileIndex(target_pos);

    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        if (tile.hasPlant && tile.cropType == seed) { // Match crop type
            sf::Texture& texture = seedTextures[seed][count];

            // Update plant sprite texture
            for (auto& plantSprite : plantSprites) {
                if (plantSprite.getPosition() == sf::Vector2f(index.x * 64, index.y * 64)) {
                    plantSprite.setTexture(texture);
                    break;
                }
            }

            std::cout << "Updated plant at (" << index.y << ", " << index.x << ") to stage " << count << std::endl;
        }
    } else {
        std::cout << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
    }
}


// Harvesting
void SoilLayer::harvest(const sf::Vector2f& target_pos, Player& player) {
    sf::Vector2i index = getTileIndex(target_pos);

    if (index.x >= 0 && index.x < grid[0].size() &&
        index.y >= 0 && index.y < grid.size()) {

        TileState& tile = grid[index.y][index.x];
        if (tile.hasPlant && tile.growthCounter >=3) {
            std::string cropType = tile.cropType; // Get crop type
            cropType[0] = toupper(cropType[0]); // Capitalize the first letter
            cropType += " Crop"; // Append " Crop"

            std::cout << "Harvesting " << cropType << " at (" << index.y << ", " << index.x << ")" << std::endl;

            player.getInventory().addItem(cropType, 1); // Add to inventory

            // Reset tile state
            tile.hasPlant = false;
            tile.growthCounter = 0;
            tile.cropType.clear(); // Clear crop type
            tile.plant = nullptr;

            // Remove water and soil visuals
            waterSprites.erase(std::remove_if(waterSprites.begin(), waterSprites.end(), 
            [&](const sf::Sprite& waterSprite) {
                return waterSprite.getPosition() == sf::Vector2f(index.x * 64, index.y * 64);
            }), waterSprites.end());
        
            soilTiles.erase(std::remove_if(soilTiles.begin(), soilTiles.end(), 
            [&](const SoilTile& soilTile) {
                return soilTile.getPosition() == sf::Vector2f(index.x * 64, index.y * 64);
            }), soilTiles.end());

            tile.isFarmable = true;
            tile.hasSoil = false;
            tile.isWatered = false;

            // Remove plant sprite
            for (auto it = plantSprites.begin(); it != plantSprites.end(); ++it) {
                if (it->getPosition() == sf::Vector2f(index.x * 64, index.y * 64)) {
                    plantSprites.erase(it);
                    break;
                }
            }
        } else {
            std::cerr << "Cannot harvest: No mature plant at (" << index.y << ", " << index.x << ")" << std::endl;
        }
    } else {
        std::cerr << "Out of bounds: (" << index.y << ", " << index.x << ")" << std::endl;
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