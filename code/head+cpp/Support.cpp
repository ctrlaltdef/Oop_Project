#include <dirent.h>          // Include for directory handling functions
#include <vector>            // Include for using vector containers
#include <string>            // Include for string manipulations
#include <SFML/Graphics.hpp> // Include for using SFML textures

// Function to load all PNG textures from a specified folder
std::vector<sf::Texture> importFolder(const std::string& path) {
    std::vector<sf::Texture> textureList;  // Vector to hold loaded textures
    DIR* dir = opendir(path.c_str());      // Open directory for reading
    if (dir == nullptr) {                  // If directory couldn't be opened, return empty vector
        return textureList;
    }

    struct dirent* entry;  // Structure to hold each directory entry
    // Loop through the directory entries
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;  // Get the name of the current file
        if (filename == "." || filename == "..") { // Skip current (.) and parent (..) directories
            continue;
        }

        std::string fullPath = path + "/" + filename; // Get the full path of the file
        // Check if the file is a PNG image
        if (fullPath.substr(fullPath.find_last_of(".") + 1) == "png") {
            sf::Texture texture;  // Create a texture object
            // Try to load the texture from the file
            if (texture.loadFromFile(fullPath)) {
                textureList.push_back(texture);  // If loaded successfully, add to the list
            }
        }
    }

    closedir(dir);  // Close the directory after processing all entries
    return textureList;  // Return the list of loaded textures
}
