#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

// The Inventory class manages a collection of items with quantities
class Inventory {
public:
    Inventory();  // Default constructor

    // Adds a specified quantity of an item to the inventory
    void addItem(const std::string &item, int quantity = 1);

    // Removes a specified quantity of an item from the inventory
    // Returns true if successful, false if the item doesn't exist or quantity is insufficient
    bool removeItem(const std::string &item, int quantity = 1);

    // Retrieves the quantity of a specified item in the inventory
    int getItemCount(const std::string &item) const;

private:
    // Stores items and their respective quantities using a hash map
    std::unordered_map<std::string, int> items;
};

#endif
