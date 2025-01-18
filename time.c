#include "time.h"

void UpdateTime(clock_t *clock, int *delta, uint32_t *tickLast, uint32_t pauseTime, input_et inputState) {
    uint32_t tickCurrent = SDL_GetTicks() - clock->start - pauseTime;
    *delta = tickCurrent - *tickLast;
    *tickLast = tickCurrent;

    if (inputState == NORMAL) {
        clock->delta += *delta;

        clock->move += *delta;
        clock->acceleration += *delta;
    }
    if (inputState != DONE)
        clock->animation += *delta;
}

void ResetTime(clock_t *clock) {
    clock->delta = 0;
    clock->acceleration = 0;
    clock->animation = 0;
    clock->move = 0;
    clock->notification = 0;
}