#include "initSnake.h"

#define CONFIG_PATH     "../config.txt" //with cmake '../' is required
#define PADDING         40

config_t read_config(char *path);

void initSDL(game_t *game);

void initAssets(game_t *game);

game_t initGame() {
    game_t game;

    game.config = read_config(CONFIG_PATH);
    game.objectPos = malloc(sizeof(point_t) * (game.config.width * game.config.height));
    for (int i = 0; i < game.config.width * game.config.height; i++)
        game.objectPos[i] = (point_t) {NULL_POS, NULL_POS};

    game.snake.pos = &game.objectPos[2 + game.config.portal_count];
    game.snake.length = game.config.start_length;
    game.snake.direction = UP;
    game.snake.speed = game.config.start_speed;
    game.snake.change_direction = 0;
    game.orangeTimer = -game.config.orange_delay;
    game.score = 0;
    game.state = INFO;
    game.startTime = 0;
    game.area = (SDL_Rect) {PADDING, 30 + PADDING, (game.config.width / 32 - 2) * 32,
                            ((game.config.height - 30) / 32 - 2) * 32};
    game.object = malloc(sizeof(object_t) * (game.config.portal_count + 2));
    for (int i = 0; i < game.config.portal_count; i++) {
        game.object[i].pos = &game.objectPos[i];
        game.object[i].show = 0;
    }

    initSDL(&game);
    initAssets(&game);

    return game;
}

config_t read_config(char *path) {
    FILE *file = fopen(path, "r");
    config_t config = {
            1280, 720, 1, 3, 1,
            0.1, 10000, 1, 10000, 5, 25,
            0.3, 3, 4, 0};
    if (file == NULL) {
        SDL_LogError(0, "Config not found!");
        return config;
    }

    while (!feof(file)) {
        char name[100];
        fscanf(file, "%s", name);
        if (!strcmp(name, "WINDOW_WIDTH"))
            fscanf(file, "%d", &config.width);
        else if (!strcmp(name, "WINDOW_HEIGHT"))
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

void initSDL(game_t *game) {
    config_t config = game->config;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(0, "SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    game->window = SDL_CreateWindow("Snake wiKapo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    config.width, config.height, SDL_WINDOW_SHOWN);

    if (!game->window) {
        SDL_LogError(0, "Failed to open %d x %d window: %s\n", config.width, config.height,
                     SDL_GetError());
        exit(1);
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    if (!game->renderer) {
        SDL_LogError(0, "Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void initAssets(game_t *game) {
    game->charset = SDL_LoadBMP("../assets/cs8x8.bmp");
    if (DEBUG)
        game->objectMap = SDL_LoadBMP("../assets/snakeDEBUG.bmp");
    else
        game->objectMap = SDL_LoadBMP("../assets/snake.bmp");


    if (!game->charset || !game->objectMap) {
        SDL_LogError(0, "Failed to load assets: %s\n", SDL_GetError());
        SDL_Quit();
        exit(99);
    }
}