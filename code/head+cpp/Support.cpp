#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp> 

std::vector<sf::Texture> importFolder(const std::string& path) {
    std::vector<sf::Texture> textureList;
    
    DIR* dir = opendir(path.c_str()); 
    if (dir == nullptr) {
        std::cerr << "Unable to open directory: " << path << std::endl;
        return textureList;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) { 
        std::string filename = entry->d_name;

        if (filename == "." || filename == "..") {
            continue;
        }

        std::string fullPath = path + "/" + filename;
        
        if (fullPath.substr(fullPath.find_last_of(".") + 1) == "png") {
            sf::Texture texture;
            if (texture.loadFromFile(fullPath)) {
                textureList.push_back(texture);  
            } else {
                std::cerr << "Failed to load image: " << fullPath << std::endl;
            }
        }
    }

    closedir(dir);  // Close the directory
    return textureList;
}
