#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Player.h"

class Overlay {
private:
    sf::RenderWindow& window;  // Reference to the SFML window where the overlay will be drawn
    Player* player;            // Pointer to the player object, used to get selected tools and seeds
    std::unordered_map<std::string, sf::Texture> toolsTextures;  // Holds textures for the player's tools
    std::unordered_map<std::string, sf::Sprite> toolsSprites;    // Holds sprites for the player's tools
    std::unordered_map<std::string, sf::Texture> seedsTextures;  // Holds textures for the player's seeds
    std::unordered_map<std::string, sf::Sprite> seedsSprites;    // Holds sprites for the player's seeds

    // Constant map for overlay positions of the tool and seed
    const std::map<std::string, sf::Vector2f> OVERLAY_POSITIONS = {
        {"tool", sf::Vector2f(35.f, 720 - 100.f)},  // Position for the tool icon
        {"seed", sf::Vector2f(70.f, 720 - 100.f)}   // Position for the seed icon
    };

public:
    Overlay(sf::RenderWindow& window, Player* player);  // Constructor to initialize the overlay with the window and player
    void display(const sf::View& camera);  // Method to display the overlay based on the camera view
};

#endif
