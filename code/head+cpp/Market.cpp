// Market.cpp
#include <iostream>
#include "Market.h"
#include "Inventory.h"
#include "Player.h"
#include "Support.h"

Market::Market() {
    // Load font and set up UI elements
    font.loadFromFile("../font/LycheeSoda.ttf");

    title.setFont(font);
    title.setString("Market");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setPosition(250, 110);

    background.setSize(sf::Vector2f(400, 400));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(100, 100);

    // Initialize prices
    prices = {
        {"Corn Seed", 4},
        {"Tomato Seed", 5},
        {"Corn Crop", 10},
        {"Tomato Crop", 20},
    };

    // Set up items for UI
    float y = 200;
    for (const auto &pricePair : prices) { // Loop through prices to create UI elements
        Item item;
        item.name = pricePair.first;
        item.price = pricePair.second;

        // Set up label with price
        item.label.setFont(font);
        item.label.setString(item.name + " - $" + std::to_string(item.price));
        item.label.setCharacterSize(20);
        item.label.setFillColor(sf::Color::White);
        item.label.setPosition(130, y);

        // Remove button setup and use "Owned" text in the same position
        item.quantityText.setFont(font);
        item.quantityText.setCharacterSize(20);
        item.quantityText.setFillColor(sf::Color::White);
        item.quantityText.setPosition(300, y);

        items.push_back(item); // Add to items list
        y += 60;
    }
}

void Market::render(sf::RenderWindow& window, const Inventory& inventory, int playerMoney) {
    // Draw background and title
    window.draw(background);
    window.draw(title);

    // Display player's money
    sf::Text moneyText;
    moneyText.setFont(font);
    moneyText.setString("Money: $" + std::to_string(playerMoney));
    moneyText.setCharacterSize(25);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(250, 150); // Adjust position as needed
    window.draw(moneyText);

    // Render market items
    for (auto& item : items) {
        // Draw item label (name and price)
        window.draw(item.label);

        // Update and draw "Owned" quantity
        int ownedQuantity = inventory.getItemCount(item.name);
        item.quantityText.setString("Owned: " + std::to_string(ownedQuantity));
        window.draw(item.quantityText);
    }
}


bool Market::buyItem(const std::string &item, int quantity, Player &player) {
    int totalPrice = prices[item] * quantity;
    if (player.getMoney() >= totalPrice) {
        player.getMoney() -= totalPrice;
        player.getInventory().addItem(item, quantity);
        std::cout << "Bought " << quantity << " " << item << "(s)" << std::endl;
        return true;
    }
    std::cout << "Not enough money to buy " << item << "!" << std::endl;
    return false;
}

bool Market::sellItem(const std::string &item, int quantity, Player &player) {
    if (player.getInventory().getItemCount(item) >= quantity) {
        player.getInventory().removeItem(item, quantity);
        player.getMoney() += (prices[item] * quantity); // Sell at half price
        std::cout << "Sold " << quantity << " " << item << "(s)" << std::endl;
        return true;
    }
    std::cout << "Not enough " << item << " to sell!" << std::endl;
    return false;
}
