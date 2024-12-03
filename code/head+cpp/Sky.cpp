#include "Sky.h"
#include <iostream>

// Constructor: Initializes the display surface, rectangle shape, and colors for the sky transition
Sky::Sky(sf::RenderWindow& window)
    : displaySurface(window), 
      fullSurf(static_cast<sf::Vector2f>(window.getSize())),  // Set the size of the rectangle to the window size
      start_color(sf::Color(255, 255, 255)),  // Initial color (white)
      end_color(sf::Color(38, 101, 189))  // Final color (light blue)
{
    fullSurf.setFillColor(start_color);  // Set the initial color for the rectangle
}

// Display method: Handles the sky color transition and draws the rectangle
void Sky::display(float dt) {
    const float transitionRate = 0.000223f;  // Rate at which the color changes over time

    // Transition from start_color to end_color by gradually reducing RGB values
    if (start_color.r > end_color.r) {
        start_color.r -= (transitionRate * dt);  // Decrease red component over time
    }

    if (start_color.g > end_color.g) {
        start_color.g -= (transitionRate * dt);  // Decrease green component over time
    }

    if (start_color.b > end_color.b) {
        start_color.b -= (transitionRate * dt);  // Decrease blue component over time
    }

    // If the color has transitioned fully to the end color, reset it to the start color
    if ((start_color.r <= end_color.r) && (start_color.g <= end_color.g) && (start_color.b <= end_color.b)) {
        start_color.r = 255;  // Reset red to max
        start_color.g = 255;  // Reset green to max
        start_color.b = 255;  // Reset blue to max
    }

    // Get the current view size and center from the window to adjust the background rectangle's position
    sf::View view = displaySurface.getView();
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();

    // Set the size and position of the background rectangle to match the window
    fullSurf.setSize(viewSize); 
    fullSurf.setPosition(viewCenter - (viewSize / 2.f));

    // Set the current sky color for the rectangle
    fullSurf.setFillColor(start_color);

    // Draw the rectangle with the current sky color on the window
    displaySurface.draw(fullSurf, sf::BlendMultiply);
}
