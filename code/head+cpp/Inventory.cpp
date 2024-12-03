#include "Inventory.h"

Inventory::Inventory() {}

// Add item to inventory
void Inventory::addItem(const std::string &item, int quantity) {
    if (quantity > 0) {
        items[item] += quantity;
    }
}

// Remove item from inventory
bool Inventory::removeItem(const std::string &item, int quantity) {
    if (quantity > 0 && items.find(item) != items.end() && items[item] >= quantity) {
        items[item] -= quantity;
        if (items[item] == 0) {
            items.erase(item);
        }
        return true;
    }
    return false;
}

// Get item count from inventory
int Inventory::getItemCount(const std::string &item) const {
    if (items.find(item) != items.end()) {
        return items.at(item);
    }
    return 0;
}
