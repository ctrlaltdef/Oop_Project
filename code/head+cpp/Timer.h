#ifndef TIMER_H
#define TIMER_H

#include <SFML/System.hpp>  // Include SFML's Clock class for time management
#include <functional>        // Include for using function callbacks

class Timer {
private:
    sf::Clock clock;           // SFML Clock to track elapsed time
    float duration;            // Duration for which the timer runs (in milliseconds)
    bool active;               // Flag to check if the timer is currently active
    std::function<void()> callback;  // Callback function to execute when timer completes

public:
    // Default constructor: Initializes timer with default values
    Timer();

    // Parameterized constructor: Initializes timer with a specified duration and optional callback
    Timer(float duration, std::function<void()> callback = nullptr);

    // Activate the timer, starting the countdown
    void activate();

    // Deactivate the timer, stopping the countdown
    void deactivate();

    // Update method to check if the timer has expired and execute the callback if set
    void update();

    // Checks if the timer is currently active
    bool isActive() const;
};

#endif
