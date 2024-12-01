// Market.h
#ifndef MARKET_H
#define MARKET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include "Inventory.h"


class Player;

class Market {
public:
    Market();
    void render(sf::RenderWindow& window, const Inventory& inventory, int playerMoney);
    bool buyItem(const std::string &item, int quantity, Player &player);
    bool sellItem(const std::string &item, int quantity, Player &player);
private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape background;

    struct Item {
        std::string name;
        int price;
        sf::Text label;
        sf::Text quantityText;
    };

    std::vector<Item> items;
    std::unordered_map<std::string, int> prices;
};

#endif

