#include <SDL.h>
#include "structs.h"

#ifndef SNAKEWKP_TIME_H
#define SNAKEWKP_TIME_H

void UpdateTime(clock_t *clock, int *delta, uint32_t *tickLast, uint32_t pauseTime, input_et inputState);

void ResetTime(clock_t *clock);

#endif //SNAKEWKP_TIME_H
