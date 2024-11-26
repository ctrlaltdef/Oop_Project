#include "MarketUI.h"
#include "Inventory.h" 
#include <iostream>

MarketUI::MarketUI() {
    // Add items for sale
    itemsForSale["corn"] = 10;
    itemsForSale["tomato"] = 15;
}

void MarketUI::buyItem(const std::string &item, int price, int quantity, Inventory &playerInventory, int &playerMoney) {
    if (playerMoney >= price * quantity) {
        playerMoney -= price * quantity;
        playerInventory.addItem(item, quantity);
        std::cout << "Bought " << quantity << " " << item << "(s)" << std::endl;
    } else {
        std::cout << "Not enough money!" << std::endl;
    }
}

void MarketUI::sellItem(const std::string &item, int price, int quantity, Inventory &playerInventory, int &playerMoney) {
    if (playerInventory.getItemCount(item) >= quantity) {
        playerInventory.removeItem(item, quantity);
        playerMoney += price * quantity;
        std::cout << "Sold " << quantity << " " << item << "(s)" << std::endl;
    } else {
        std::cout << "Not enough items to sell!" << std::endl;
    }
}

void MarketUI::render(sf::RenderWindow &window) {
    // Implement rendering logic (similar to Inventory::render)
}
