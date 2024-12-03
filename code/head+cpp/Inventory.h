// Inventory.h
#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp> 

class Inventory {
public:
    Inventory();
    void addItem(const std::string &item, int quantity = 1);
    bool removeItem(const std::string &item, int quantity = 1);
    int getItemCount(const std::string &item) const;

private:
    std::unordered_map<std::string, int> items;
};

#endif
