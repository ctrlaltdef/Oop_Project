#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Player.h"

class Overlay {
private:
    sf::RenderWindow& window;  // Reference to the SFML window
    Player* player;            // Pointer to the player
    std::unordered_map<std::string, sf::Texture> toolsTextures;
    std::unordered_map<std::string, sf::Sprite> toolsSprites;
    std::unordered_map<std::string, sf::Texture> seedsTextures;
    std::unordered_map<std::string, sf::Sprite> seedsSprites;

    const std::map<std::string, sf::Vector2f> OVERLAY_POSITIONS = {
    {"tool", sf::Vector2f(35.f, 720 - 100.f)},
    {"seed", sf::Vector2f(70.f, 720 - 100.f)}
};

public:
    Overlay(sf::RenderWindow& window, Player* player);
    void display(const sf::View& camera);
};

#endif
