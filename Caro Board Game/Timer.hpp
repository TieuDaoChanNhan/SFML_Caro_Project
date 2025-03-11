#ifndef TIMER_HPP
#define TIMER_HPP

#include "UIUX_Game.hpp"
#include "UIUX.hpp"

class Timer {
private:
    // --- Timer ---
    sf::Clock clock;
    sf::Time timeLimit = sf::seconds(0.0f);
    bool isPaused = false;
public:
    Timer() {};

    // --- Timer Functions ---
    void restartTimer() {
        clock.restart();
    }

    void setTimelimit(sf::Time limit) {
        timeLimit = limit;
    }

    sf::Time getTimeLimit() {
        return timeLimit;
    }

    bool isTimeUp() {
        return clock.getElapsedTime() >= timeLimit;
    }

    sf::Time getRemainingTime() {
        return timeLimit - clock.getElapsedTime();
    }

    void changeState() {
        isPaused = !isPaused;
        if (isPaused) clock.stop();
        else clock.start();
    }

    bool getState() {
        return isPaused;
    }
};

#endif // !TIMER_HPP
