#ifndef TIMER_H
#define TIMER_H

#include "time.h"

namespace timer {

    /**
     * @brief Starts the game timer.
     */
    void start();

    /**
     * @brief Returns the number of seconds since the game timer started.
     * 
     * @return The number of seconds since the game timer started.
     */
    time_t stop();
} // namespace timer

#endif
