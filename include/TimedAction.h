#ifndef TIMED_ACTION_H_
#define TIMED_ACTION_H_

#include <Arduino.h>

/**
 * Class to perform an action after a specified interval.
 */
class TimedAction {
    unsigned long previousMillis; ///< The last time the action was performed.
    const long interval; ///< The interval between each action.

public:
    /**
     * Constructor for the TimedAction class.
     *
     * @param interval The interval between each action in milliseconds.
     */
    TimedAction(long interval) : interval(interval), previousMillis(0) {}

    /**
     * Checks if it's time to perform the action.
     *
     * @return true if it's time to perform the action, false otherwise.
     */
    bool isTime() {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            return true;
        }
        return false;
    }
};

#endif // TIMED_ACTION_H_