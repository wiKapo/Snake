#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "structs.h"

#ifndef SNAKEWKP_INITSNAKE_H
#define SNAKEWKP_INITSNAKE_H

config_t read_config(char* path);
void initSDL(config_t config, game_t *game);
void initAssets(game_t *game);

#endif //SNAKEWKP_INITSNAKE_H
