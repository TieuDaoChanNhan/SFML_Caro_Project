#ifndef TIMER_HPP
#define TIMER_HPP

#include "UIUX.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Timer {
private:
    // --- Timer ---
    sf::Clock clock; // Clock to keep track of elapsed time
    sf::Time timeLimit = sf::seconds(0.0f); // Time limit for the timer
    bool isPaused = false; // Flag indicating if the timer is paused

public:
    Timer() {} // Default constructor

    // --- Timer Functions ---
    void restartTimer() {
        // Restarts the timer
        clock.restart();
    }

    void setTimelimit(sf::Time limit) {
        // Sets the time limit for the timer
        timeLimit = limit;
    }

    sf::Time getTimeLimit() {
        // Returns the current time limit
        return timeLimit;
    }

    bool isTimeUp() {
        // Checks if the timer has reached its time limit
        return clock.getElapsedTime() >= timeLimit;
    }

    sf::Time getRemainingTime() {
        // Returns the remaining time on the timer
        return timeLimit - clock.getElapsedTime();
    }

    void changeState() {
        // Toggles the pause state of the timer
        isPaused = !isPaused;
        if (isPaused) clock.stop();
        else clock.restart();
    }

    bool getState() {
        // Returns the current pause state of the timer
        return isPaused;
    }
};

#endif // !TIMER_HPP