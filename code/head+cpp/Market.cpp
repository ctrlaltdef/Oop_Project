#include "Market.h"
#include "Player.h"

// Constructor: Initializes the market, sets font and UI elements
Market::Market() {
    font.loadFromFile("../font/LycheeSoda.ttf");  // Load font for text display

    // Set up the title text
    title.setFont(font);
    title.setString("Market");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setPosition(250, 110);

    // Set up the background of the market interface
    background.setSize({400, 400});
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(100, 100);

    // Item prices stored in a dictionary (unordered_map)
    prices = {
        {"Corn Seed", 4},
        {"Tomato Seed", 5},
        {"Corn Crop", 10},
        {"Tomato Crop", 20}
    };

    // Initialize the list of items for sale in the market
    float y = 200;
    for (const auto &pricePair : prices) {
        Item item{pricePair.first, pricePair.second};  // Create Item object

        // Set the label for each item
        item.label.setFont(font);
        item.label.setString(item.name + " - $" + std::to_string(item.price));
        item.label.setCharacterSize(23);
        item.label.setFillColor(sf::Color::White);
        item.label.setPosition(130, y);

        // Set the quantity text for each item
        item.quantityText.setFont(font);
        item.quantityText.setCharacterSize(23);
        item.quantityText.setFillColor(sf::Color::White);
        item.quantityText.setPosition(300, y);

        items.push_back(item);  // Add item to the market list
        y += 60;  // Increment y position for next item
    }
}

// Renders the market UI and updates the item quantity display
void Market::render(sf::RenderWindow& window, const Inventory& inventory, int playerMoney) {
    window.draw(background);  // Draw background
    window.draw(title);  // Draw title

    // Display player's money
    sf::Text moneyText;
    moneyText.setFont(font);
    moneyText.setString("Money: $" + std::to_string(playerMoney));
    moneyText.setCharacterSize(23);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(250, 150);
    window.draw(moneyText);

    // Draw each item and its corresponding quantity in the player's inventory
    for (auto& item : items) {
        window.draw(item.label);  // Draw item label
        item.quantityText.setString("Owned: " + std::to_string(inventory.getItemCount(item.name)));  // Update owned quantity
        window.draw(item.quantityText);  // Draw quantity text
    }
}

// Buy item from market
bool Market::buyItem(const std::string &item, int quantity, Player &player) {
    int totalPrice = prices[item] * quantity;  // Calculate total cost for the item
    if (player.getMoney() >= totalPrice) {  // Check if player has enough money
        player.getMoney() -= totalPrice;  // Deduct money from player
        player.getInventory().addItem(item, quantity);  // Add item to player's inventory
        return true;  // Return success
    }
    return false;  // Return failure if not enough money
}

// Sell item to market
bool Market::sellItem(const std::string &item, int quantity, Player &player) {
    if (player.getInventory().getItemCount(item) >= quantity) {  // Check if player has enough of the item
        player.getInventory().removeItem(item, quantity);  // Remove item from player's inventory
        player.getMoney() += (prices[item] * quantity);  // Add money to player
        return true;  // Return success
    }
    return false;  // Return failure if player doesn't have enough of the item
}
