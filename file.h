#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "structs.h"

#ifndef SNAKEWKP_FILE_H
#define SNAKEWKP_FILE_H

score_t *GetScores();

config_t GetConfig(char *path);

void UpdateScores(score_t *scores);

void SaveGame(game_t game);

void LoadGame(game_t *game);

#endif //SNAKEWKP_FILE_H
