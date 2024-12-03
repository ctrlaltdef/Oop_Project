#ifndef SUPPORT_H
#define SUPPORT_H

#include <SFML/Graphics.hpp>  // Include SFML for using textures
#include <vector>              // Include for using vector containers
#include <string>              // Include for using strings

// Function to load all textures from a folder and return them in a vector
std::vector<sf::Texture> importFolder(const std::string &path);

#endif
