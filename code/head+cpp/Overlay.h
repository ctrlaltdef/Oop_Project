#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "Timer.h"
#include "Settings.h"
#include "Support.h"
#include <unordered_map>
#include "Player.h" 

class Player;

class Overlay {
private:
    Player* player;
    std::unordered_map<std::string, sf::Texture> toolsTextures;
    std::unordered_map<std::string, sf::Sprite> toolsSprites;
    std::unordered_map<std::string, sf::Texture> seedsTextures;
    std::unordered_map<std::string, sf::Sprite> seedsSprites;

public:
    Overlay(Player* player);
    void display(sf::RenderWindow& window);
};

#endif


