#include "Market.h"
#include "Player.h"

Market::Market() {
    font.loadFromFile("../font/LycheeSoda.ttf");

    title.setFont(font);
    title.setString("Market");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setPosition(250, 110);

    background.setSize({400, 400});
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(100, 100);

    prices = {
        {"Corn Seed", 4},
        {"Tomato Seed", 5},
        {"Corn Crop", 10},
        {"Tomato Crop", 20}
    };

    float y = 200;
    for (const auto &pricePair : prices) {
        Item item{pricePair.first, pricePair.second};

        item.label.setFont(font);
        item.label.setString(item.name + " - $" + std::to_string(item.price));
        item.label.setCharacterSize(23);
        item.label.setFillColor(sf::Color::White);
        item.label.setPosition(130, y);

        item.quantityText.setFont(font);
        item.quantityText.setCharacterSize(23);
        item.quantityText.setFillColor(sf::Color::White);
        item.quantityText.setPosition(300, y);

        items.push_back(item);
        y += 60;
    }
}

void Market::render(sf::RenderWindow& window, const Inventory& inventory, int playerMoney) {
    window.draw(background);
    window.draw(title);

    sf::Text moneyText;
    moneyText.setFont(font);
    moneyText.setString("Money: $" + std::to_string(playerMoney));
    moneyText.setCharacterSize(23);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(250, 150);
    window.draw(moneyText);

    for (auto& item : items) {
        window.draw(item.label);
        item.quantityText.setString("Owned: " + std::to_string(inventory.getItemCount(item.name)));
        window.draw(item.quantityText);
    }
}

bool Market::buyItem(const std::string &item, int quantity, Player &player) {
    int totalPrice = prices[item] * quantity;
    if (player.getMoney() >= totalPrice) {
        player.getMoney() -= totalPrice;
        player.getInventory().addItem(item, quantity);
        return true;
    }
    return false;
}

bool Market::sellItem(const std::string &item, int quantity, Player &player) {
    if (player.getInventory().getItemCount(item) >= quantity) {
        player.getInventory().removeItem(item, quantity);
        player.getMoney() += (prices[item] * quantity);
        return true;
    }
    return false;
}
