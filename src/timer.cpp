#include "time.h"

#include "timer.h"

namespace timer {

    time_t start_time;

    /**
     * @brief Starts the game timer.
     */
    void start() {
        start_time = time(NULL);
    }

    /**
     * @brief Returns the number of seconds since the game timer started.
     * 
     * @return The number of seconds since the game timer started.
     */
    time_t stop() {
        return time(NULL) - start_time;
    }
} // namespace timer
