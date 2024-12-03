#include "Inventory.h"

// Constructor initializes the inventory with no items
Inventory::Inventory() {}

// Adds a specified quantity of an item to the inventory
void Inventory::addItem(const std::string &item, int quantity) {
    if (quantity > 0) {  // Ensure quantity is positive
        items[item] += quantity;  // Increment the quantity for the given item
    }
}

// Removes a specified quantity of an item from the inventory
bool Inventory::removeItem(const std::string &item, int quantity) {
    // Check if the item exists and the quantity to remove is valid
    if (quantity > 0 && items.find(item) != items.end() && items[item] >= quantity) {
        items[item] -= quantity;  // Decrease the item's quantity
        if (items[item] == 0) {  // If quantity reaches 0, remove the item from inventory
            items.erase(item);
        }
        return true;  // Indicate successful removal
    }
    return false;  // Removal failed due to insufficient quantity or missing item
}

// Retrieves the current quantity of a specified item in the inventory
int Inventory::getItemCount(const std::string &item) const {
    // Check if the item exists in the inventory
    if (items.find(item) != items.end()) {
        return items.at(item);  // Return the item's quantity
    }
    return 0;  // Return 0 if the item is not found
}
