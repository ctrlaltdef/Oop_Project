// Inventory.cpp
#include <iostream>
#include "Inventory.h"

Inventory::Inventory() {}

void Inventory::addItem(const std::string &item, int quantity) {
    if (items.size() >= capacity && items.find(item) == items.end()) {
        std::cout << "Inventory is full!" << std::endl;
        return;
    }
    items[item] += quantity;
}


bool Inventory::removeItem(const std::string &item, int quantity) {
    if (items[item] >= quantity) {
        items[item] -= quantity;
        return true;
    }
    return false;
}

int Inventory::getItemCount(const std::string &item) const {
    return items.at(item);
}

void Inventory::render(sf::RenderWindow &window) {
    sf::Font font;
    if (!font.loadFromFile("../fonts/arial.ttf")) { // Adjust the path as necessary
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    float startX = 50.0f; // Starting X position
    float startY = 50.0f; // Starting Y position
    float spacing = 30.0f; // Spacing between items

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