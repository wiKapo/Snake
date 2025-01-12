#include "time.h"

void UpdateTime(clock_t *clock, int *delta, uint32_t *tickLast, uint32_t pauseTime, state_et state) {
    uint32_t tickCurrent = SDL_GetTicks() - clock->start - pauseTime;
    *delta = tickCurrent - *tickLast;
    *tickLast = tickCurrent;

    if (state == PLAY) {
        clock->delta += *delta;

        clock->move += *delta;
        clock->acceleration += *delta;
    }
    clock->animation += *delta;
}

void ResetTime(clock_t *clock) {
    clock->delta = 0;
    clock->acceleration = 0;
    clock->animation = 0;
    clock->move = 0;
}