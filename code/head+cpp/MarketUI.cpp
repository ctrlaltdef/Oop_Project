#include "MarketUI.h"
#include "Inventory.h" 
#include <iostream>

MarketUI::MarketUI() {
    // Initialize items for sale in the market
    itemsForSale["Corn"] = 4;
    itemsForSale["Tomato"] = 5;
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

void MarketUI::render(sf::RenderWindow &window, Inventory &playerInventory) {
    if (!font.loadFromFile("../font/LycheeSoda.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    float startX = 50.0f;  // Starting X position for items
    float startY = 50.0f;  // Starting Y position for items
    float spacing = 30.0f; // Spacing between items

    int index = 0;
    for (auto &item : itemsForSale) {
        sf::Text itemText;
        itemText.setFont(font);
        itemText.setString(item.first + " - $" + std::to_string(item.second));
        itemText.setCharacterSize(20);
        itemText.setFillColor(sf::Color::White);
        itemText.setPosition(startX, startY + index * spacing);
        window.draw(itemText);

        // Display player's inventory count for the item
        int inventoryCount = playerInventory.getItemCount(item.first);
        sf::Text inventoryText;
        inventoryText.setFont(font);
        inventoryText.setString("Qty: " + std::to_string(inventoryCount));
        inventoryText.setCharacterSize(20);
        inventoryText.setFillColor(sf::Color::White);
        inventoryText.setPosition(startX + 200, startY + index * spacing);  // Adjust position for quantity
        window.draw(inventoryText);

        ++index;
    }
}
