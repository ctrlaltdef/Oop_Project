// Market.h
#ifndef MARKET_H
#define MARKET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

class Market {
public:
    Market();
    void render(sf::RenderWindow &window);
    void handleEvent(const sf::Event &event);
    void update(float dt);
    bool buyItem(const std::string &item, int quantity, int &playerMoney);
    bool sellItem(const std::string &item, int quantity, int &playerMoney);

private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape background;

    struct Item {
        std::string name;
        int price;
        sf::Text label;
        sf::RectangleShape button;
    };

    std::vector<Item> items;
    std::unordered_map<std::string, int> prices;

    void loadAssets();
};

#endif
