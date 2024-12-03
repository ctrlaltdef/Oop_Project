#include "Timer.h"

// Default constructor: Initializes the timer with no duration, inactive state, and no callback
Timer::Timer() : duration(0), active(false), callback(nullptr) {}

// Parameterized constructor: Initializes the timer with a specified duration and optional callback function
Timer::Timer(float duration, std::function<void()> callback)
    : duration(duration), callback(callback), active(false) {}

// Activates the timer and resets the clock to start counting
void Timer::activate() {
    active = true;               // Set the timer to active state
    clock.restart();             // Restart the clock to start timing from zero
}

// Deactivates the timer, stopping the countdown
void Timer::deactivate() {
    active = false;             // Set the timer to inactive state
}

// Updates the timer, checks if the duration has passed, and triggers the callback if it has
void Timer::update() {
    if (active && clock.getElapsedTime().asMilliseconds() >= duration) { 
        deactivate();             // Deactivate the timer once it has finished
        if (callback) {           // If a callback function is set, call it
            callback();
        }
    }
}

// Returns whether the timer is currently active
bool Timer::isActive() const {
    return active;               // Return the active state of the timer
}
