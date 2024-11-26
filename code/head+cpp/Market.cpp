// Market.cpp
#include "Market.h"

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

    // Set up items
    items = {
        {"Corn Seed", 4},
        {"Tomato Seed", 5},
        {"Corn Crop", 10},
        {"Tomato Crop", 20},

    };

    float y = 200;
    for (auto &item : items) {
        item.label.setFont(font);
        item.label.setString(item.name + " - $" + std::to_string(item.price));
        item.label.setCharacterSize(20);
        item.label.setFillColor(sf::Color::White);
        item.label.setPosition(130, y);

        item.button.setSize(sf::Vector2f(100, 40));
        item.button.setFillColor(sf::Color::Green);
        item.button.setPosition(300, y);

        y += 60;
    }
}

void Market::render(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(title);
    for (const auto &item : items) {
        window.draw(item.label);
        window.draw(item.button);
    }
}

void Market::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        for (auto &item : items) {
            if (item.button.getGlobalBounds().contains(mousePos)) {
                // Handle item purchase (e.g., deduct money, add item to inventory)
            }
        }
    }
}

void Market::update(float dt) {
    // Handle any animations or time-based logic
}

bool Market::buyItem(const std::string &item, int quantity, int &playerMoney) {
    if (prices[item] * quantity <= playerMoney) {
        playerMoney -= prices[item] * quantity;
        return true;
    }
    return false;
}

bool Market::sellItem(const std::string &item, int quantity, int &playerMoney) {
    playerMoney += prices[item] * quantity / 2; // Sell at half price
    return true;
}
