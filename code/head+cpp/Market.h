#ifndef MARKET_H
#define MARKET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include "Inventory.h"

// Forward declaration of Player class to avoid circular dependency
class Player;

class Market {
public:
    Market();  // Constructor initializes the market
    void render(sf::RenderWindow& window, const Inventory& inventory, int playerMoney);  // Renders market interface
    bool buyItem(const std::string &item, int quantity, Player &player);  // Buys item from market
    bool sellItem(const std::string &item, int quantity, Player &player);  // Sells item to market

private:
    sf::Font font;  // Font for text
    sf::Text title;  // Title text for the market
    sf::RectangleShape background;  // Background shape for the market interface

    // Inner structure for items in the market
    struct Item {
        std::string name;  // Name of the item
        int price;  // Price of the item
        sf::Text label;  // Label text to display item name and price
        sf::Text quantityText;  // Text displaying quantity owned by the player
    };

    std::vector<Item> items;  // List of items for sale in the market
    std::unordered_map<std::string, int> prices;  // Prices of the items
};

#endif
