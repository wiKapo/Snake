#include "file.h"

#define SCORES_PATH     "../scores.txt"

void MoveScore(score_t *scoreDest, score_t *scoreSrc) {
    strcpy(scoreDest->name, scoreSrc->name);
    scoreDest->score = scoreSrc->score;
}

void NewScore(score_t *scoreDest, const char *name, int score) {
    strcpy(scoreDest->name, name);
    scoreDest->score = score;
}

score_t *GetScores() {
    FILE *file = fopen(SCORES_PATH, "r");
    score_t *scores = malloc(sizeof(score_t) * 4); //3 HighScores from file and 1 for new score
    for (int i = 0; i < 4; i++)
        scores[i].name = malloc(sizeof(char) * 3);

    if (file == NULL) {
        SDL_LogError(0, "Scores not found!");
        return scores;
    }

    for (int i = 0; i < 3; i++) {
        if (feof(file)) NewScore(&scores[i], "___", 0);
        else
            fscanf(file, "%s %d\n", scores[i].name, &scores[i].score);
    }
    fclose(file);

    NewScore(&scores[3], "NEW", -99); //Prepared for handling of new scores
    return scores;
}

void UpdateScores(score_t *scores) {
    int score = scores[3].score;
    char *name = scores[3].name;

    if (score >= scores[0].score) {
        MoveScore(&scores[2], &scores[1]);
        MoveScore(&scores[1], &scores[0]);
        NewScore(&scores[0], name, score);
    } else if (score >= scores[1].score) {
        MoveScore(&scores[2], &scores[1]);
        NewScore(&scores[1], name, score);
    } else
        NewScore(&scores[2], name, score);

    FILE *file = fopen(SCORES_PATH, "w");
    if (file == NULL) {
        SDL_LogError(0, "Scores not found!");
        return;
    }
    for (int i = 0; i < 3 && scores[i].score != -99; i++)
        fprintf(file, "%s %d\n", scores[i].name, scores[i].score);

    fclose(file);

    NewScore(&scores[3], "", -99); //Cleared after the new score is handled
}

config_t GetConfig(char *path) {
    config_t config = {
            1280, 720, 1, 3, 1,
            0.1, 10000, 1, 10000, 5, 25,
            0.3, 3, 4, 0};

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        SDL_LogError(0, "Config not found!");
        return config;
    }

    while (!feof(file)) {
        char name[100];
        fscanf(file, "%s", name);
        if (!strcmp(name, "BOARD_WIDTH"))
            fscanf(file, "%d", &config.width);
        else if (!strcmp(name, "BOARD_HEIGHT"))
            fscanf(file, "%d", &config.height);
        else if (!strcmp(name, "START_SPEED"))
            fscanf(file, "%d", &config.start_speed);
        else if (!strcmp(name, "START_LENGTH"))
            fscanf(file, "%d", &config.start_length);
        else if (!strcmp(name, "MAX_SPEED"))
            fscanf(file, "%d", &config.max_speed);
        else if (!strcmp(name, "APPLE_VALUE"))
            fscanf(file, "%d", &config.apple_value);
        else if (!strcmp(name, "ORANGE_DELAY"))
            fscanf(file, "%d", &config.orange_delay);
        else if (!strcmp(name, "ORANGE_VALUE"))
            fscanf(file, "%d", &config.orange_value);
        else if (!strcmp(name, "ORANGE_CHANCE"))
            fscanf(file, "%d", &config.orange_chance);
        else if (!strcmp(name, "ACCELERATION"))
            fscanf(file, "%f", &config.acceleration);
        else if (!strcmp(name, "ACCELERATION_INTERVAL"))
            fscanf(file, "%d", &config.acceleration_interval);
        else if (!strcmp(name, "BONUS_SLOW_DOWN"))
            fscanf(file, "%f", &config.bonus_slow_down);
        else if (!strcmp(name, "BONUS_SHORTEN"))
            fscanf(file, "%d", &config.bonus_shorten);
        else if (!strcmp(name, "FRUIT_MODE"))
            fscanf(file, "%d", &config.fruit_mode);
        else if (!strcmp(name, "PORTAL_COUNT"))
            fscanf(file, "%d", &config.portal_count);
    }
    fclose(file);

    config.acceleration = 1 - config.acceleration;
    config.bonus_slow_down = 1 + config.bonus_slow_down;
    return config;
}