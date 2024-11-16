#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>  // Assuming SFML for image loading

std::vector<sf::Texture> importFolder(const std::string& path) {
    std::vector<sf::Texture> textureList;
    
    DIR* dir = opendir(path.c_str());  // Open the directory
    if (dir == nullptr) {
        std::cerr << "Unable to open directory: " << path << std::endl;
        return textureList;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {  // Read each file in the directory
        std::string filename = entry->d_name;

        // Skip . and .. directories
        if (filename == "." || filename == "..") {
            continue;
        }

        std::string fullPath = path + "/" + filename;
        
        // Check if the file is an image (here assuming you know image files end with .png)
        if (fullPath.substr(fullPath.find_last_of(".") + 1) == "png") {
            sf::Texture texture;
            if (texture.loadFromFile(fullPath)) {
                textureList.push_back(texture);  // Add the texture to the list
            } else {
                std::cerr << "Failed to load image: " << fullPath << std::endl;
            }
        }
    }

    closedir(dir);  // Close the directory
    return textureList;
}
