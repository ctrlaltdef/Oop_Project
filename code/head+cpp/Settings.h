#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/System/Vector2.hpp>
#include <string>
#include <map>
#include <vector>

// Screen settings
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 720;
const int TILE_SIZE = 64;

// Overlay positions
const std::map<std::string, sf::Vector2f> OVERLAY_POSITIONS = {
    {"tool", sf::Vector2f(35, SCREEN_HEIGHT - 100)},
    {"seed", sf::Vector2f(70, SCREEN_HEIGHT - 100)}
};

const std::map<std::string, sf::Vector2f> PLAYER_TOOL_OFFSET = {
    {"left", sf::Vector2f(-50, 40)},
    {"right", sf::Vector2f(50, 40)},
    {"up", sf::Vector2f(0, -10)},
    {"down", sf::Vector2f(0, 50)}
};

// Layers
const std::map<std::string, int> LAYERS = {
    {"water", 0},
    {"ground", 1},
    {"soil", 2},
    {"soil water", 3},
    {"rain floor", 4},
    {"house bottom", 5},
    {"ground plant", 6},
    {"main", 7},
    {"house top", 8},
    {"fruit", 9},
    {"rain drops", 10}
};

// Apple positions
const std::map<std::string, std::vector<sf::Vector2i>> APPLE_POS = {
    {"Small", {{18, 17}, {30, 37}, {12, 50}, {30, 45}, {20, 30}, {30, 10}}},
    {"Large", {{30, 24}, {60, 65}, {50, 50}, {16, 40}, {45, 50}, {42, 70}}}
};

// Growth speed
const std::map<std::string, float> GROW_SPEED = {
    {"corn", 1.0f},
    {"tomato", 0.7f}
};

// Sale prices
const std::map<std::string, int> SALE_PRICES = {
    {"wood", 4},
    {"apple", 2},
    {"corn", 10},
    {"tomato", 20}
};

// Purchase prices
const std::map<std::string, int> PURCHASE_PRICES = {
    {"corn", 4},
    {"tomato", 5}
};

#endif
