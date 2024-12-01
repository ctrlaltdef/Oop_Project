#include "Inventory.h"
#include <iostream>
#include "Support.h"

Inventory::Inventory() {}

// Add item to inventory
void Inventory::addItem(const std::string &item, int quantity) {
    if (quantity <= 0) {
        return; // Ignore invalid quantities
    }

    // Debug: print the item being added
    std::cout << "Adding " << quantity << " " << item << "(s) to inventory." << std::endl;

    items[item] += quantity;

    // Debug: print the current inventory count for the item
    std::cout << "Current inventory count for " << item << ": " << items[item] << std::endl;
}

// Remove item from inventory
bool Inventory::removeItem(const std::string &item, int quantity) {
    if (quantity <= 0) {
        return false; // Invalid quantity
    }

    if (items.find(item) != items.end() && items[item] >= quantity) {
        items[item] -= quantity;
        if (items[item] == 0) {
            items.erase(item);
        }
        return true;
    }

    return false; // Item not found or not enough quantity
}

// Get item count from inventory
int Inventory::getItemCount(const std::string &item) const {
    int count = 0;

    // Debug: print the item being checked
    std::cout << "Getting item count for " << item << std::endl;

    if (items.find(item) != items.end()) {
        count = items.at(item);
    }

    // Debug: print the found count
    std::cout << "Item count for " << item << ": " << count << std::endl;

    return count;
}

