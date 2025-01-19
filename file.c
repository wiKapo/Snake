#include "file.h"

#define SCORES_PATH     "../scores.txt"
#define MIN_BOARD_WIDTH     3 //positions
#define MIN_BOARD_HEIGHT    3 //positions

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

    config.width = config.width < MIN_BOARD_WIDTH ? MIN_BOARD_WIDTH : config.width;
    config.height = config.height < MIN_BOARD_HEIGHT ? MIN_BOARD_HEIGHT : config.height;

    config.acceleration = 1 - config.acceleration;
    config.bonus_slow_down = 1 + config.bonus_slow_down;
    return config;
}

void SaveGame(game_t game) {
    FILE *file = fopen("../qsave.txt", "w");

    char *text[100];
    config_t config = game.config;
    sprintf(text, "%d %d\n", config.width, config.height);
    fputs(text, file);
    sprintf(text, "%d\n", config.max_speed);
    fputs(text, file);
    sprintf(text, "%f %d\n", config.acceleration, config.acceleration_interval);
    fputs(text, file);
    sprintf(text, "%d\n", config.apple_value);
    fputs(text, file);
    sprintf(text, "%d %d %d\n", config.orange_value, config.orange_delay, config.orange_chance);
    fputs(text, file);
    sprintf(text, "%f %d\n", config.bonus_slow_down, config.bonus_shorten);
    fputs(text, file);
    sprintf(text, "%d %d\n", config.portal_count, config.fruit_mode);
    fputs(text, file);

    sprintf(text, "%d %d %d %d\n", game.area.x, game.area.y, game.area.w, game.area.h);
    fputs(text, file);

    clock_t clock = game.clock;
    sprintf(text, "%d %d\n", clock.delta, clock.move);
    fputs(text, file);
    sprintf(text, "%d %d\n", clock.game, clock.acceleration);
    fputs(text, file);
    sprintf(text, "%d %d\n", clock.animation, clock.orange);
    fputs(text, file);

    sprintf(text, "%d\n", game.score);
    fputs(text, file);

    snake_t snake = game.snake;
    sprintf(text, "%d %d %d\n", snake.length, snake.direction, snake.speed);
    fputs(text, file);

    int amount = 2 + game.config.portal_count * 2 + game.snake.length;
    for (int i = 0; i < amount; i++) {
        sprintf(text, "%d %d\n", game.objectPos[i].x, game.objectPos[i].y);
        fputs(text, file);
    }

    fclose(file);
}

void LoadGame(game_t *game) {
    FILE *file = fopen("../qsave.txt", "r");

    if (file == NULL)
        return;

    if (!game->automatic)
        game->state = LOAD;

    config_t *config = &game->config;
    int oldBoardW = config->width;
    int oldBoardH = config->height;

    fscanf(file, "%d %d\n", &config->width, &config->height);
    fscanf(file, "%d\n", &config->max_speed);
    fscanf(file, "%f %d\n", &config->acceleration, &config->acceleration_interval);
    fscanf(file, "%d\n", &config->apple_value);
    fscanf(file, "%d %d %d\n", &config->orange_value, &config->orange_delay, &config->orange_chance);
    fscanf(file, "%f %d\n", &config->bonus_slow_down, &config->bonus_shorten);
    fscanf(file, "%d %d\n", &config->portal_count, &config->fruit_mode);

    fscanf(file, "%d %d %d %d\n", &game->area.x, &game->area.y, &game->area.w, &game->area.h);

    clock_t *clock = &game->clock;
    fscanf(file, "%d %d\n", &clock->delta, &clock->move);
    fscanf(file, "%d %d\n", &clock->game, &clock->acceleration);
    fscanf(file, "%d %d\n", &clock->animation, &clock->orange);
    game->clock.notification = 0;

    fscanf(file, "%d\n", &game->score);

    free(game->objectPos);
    int objectCount = 2 + config->portal_count * 2;
    game->objectPos = malloc(sizeof(point_t) * (objectCount + config->width * config->height));
    for (int i = 0; i < 2 + objectCount; i++) {
        game->object[i].pos = &game->objectPos[i];
        game->object[i].show = 0;
    }

    snake_t *snake = &game->snake;
    snake->pos = &game->objectPos[2 + config->portal_count * 2];

    //Clear snake positions
    for (int i = 0; i < config->width * config->height; i++)
        snake->pos[i] = (point_t) {NULL_POS, NULL_POS};

    fscanf(file, "%d %d %d\n", &snake->length, &snake->direction, &snake->speed);
    snake->change_direction = 0;

    for (int i = 0; i < objectCount; i++)
        fscanf(file, "%d %d\n", &game->objectPos[i].x, &game->objectPos[i].y);

    for (int i = 0; i < snake->length; i++)
        fscanf(file, "%d %d\n", &snake->pos[i].x, &snake->pos[i].y);

    if (game->object[ORANGE].pos->x != -99)
        game->object[ORANGE].show = 1;
    else
        game->object[ORANGE].show = 0;

//    if (config->width != oldBoardW) { TODO change window size and board size when loading from different game
//        if (config->width > MAX_SMALL_BOARD_WIDTH){
//
//        } else if (oldBoardW > MAX_SMALL_BOARD_WIDTH && config->width < MAX_SMALL_BOARD_WIDTH){
//            SDL_SetWindowSize(game->window, 700, 700);
//        }
//    }
//    if (config->height != oldBoardH) {}

    fclose(file);
}