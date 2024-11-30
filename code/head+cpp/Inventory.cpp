#include <iostream>
#include "Inventory.h"

Inventory::Inventory() {}

void Inventory::addItem(const std::string &item, int quantity) {
    if (items.find(item) == items.end()) {
        items[item] = 0;  // Add item if not present
    }
    items[item] += quantity;
}

bool Inventory::removeItem(const std::string &item, int quantity) {
    if (items.find(item) != items.end() && items[item] >= quantity) {
        items[item] -= quantity;
        return true;
    }
    return false;
}

int Inventory::getItemCount(const std::string &item) const {
    if (items.find(item) != items.end()) {
        return items.at(item);
    }
    return 0; // Return 0 if item not found
}

void Inventory::render(sf::RenderWindow &window) {
    sf::Font font;
    if (!font.loadFromFile("../font/LycheeSoda.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    float startX = 50.0f;
    float startY = 50.0f;
    float spacing = 30.0f;

    int index = 0;
    for (const auto &item : items) {
        sf::Text text;
        text.setFont(font);
        text.setString(item.first + ": " + std::to_string(item.second));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(startX, startY + index * spacing);
        window.draw(text);
        ++index;
    }
}
