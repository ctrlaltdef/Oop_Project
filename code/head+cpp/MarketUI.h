// MarketUI.h
#ifndef MARKETUI_H
#define MARKETUI_H

#include <unordered_map>
#include <SFML/Graphics.hpp>

class MarketUI {
public:
    MarketUI();
    void render(sf::RenderWindow &window);
    void buyItem(const std::string &item, int price, int quantity, Inventory &playerInventory, int &playerMoney);
    void sellItem(const std::string &item, int price, int quantity, Inventory &playerInventory, int &playerMoney);

private:
    std::unordered_map<std::string, int> itemsForSale; // Item name -> price
};

#endif
