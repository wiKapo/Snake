#include "draw.h"

#define ANIMATION_TIME      250 //milliseconds

void DrawTopBar(SDL_Surface *screen, SDL_Surface *charset, uint32_t deltaTime, state_et state, int score) {
    DrawBox(screen, charset, (SDL_Rect) {0, 0, screen->w, 4 * CHAR_SIZE}, 1);

    char text[100];
    sprintf(text, "Snake by wiKapo");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, 1.5 * CHAR_SIZE, text, GREEN);

    sprintf(text, "Score: %05d", score);
    DrawString(screen, charset, 4 * CHAR_SIZE, 1.5 * CHAR_SIZE, text);

    sprintf(text, "1234ABCDEFGhI");
    DrawColorString(screen, charset, screen->w / 4 - 2.25 * CHAR_SIZE, 1.5 * CHAR_SIZE, text, DARK_GRAY);

    if (state == PLAY)
        DrawTime(screen, charset, screen->w - 13 * CHAR_SIZE, 1.5 * CHAR_SIZE, deltaTime);
    else if (state == PAUSE || state == PAUSE_INFO || state == LOAD) {
        DrawString(screen, charset, screen->w - (13 + 9) * CHAR_SIZE, 1.5 * CHAR_SIZE, "[PAUSED]");
        DrawColorTime(screen, charset, screen->w - 13 * CHAR_SIZE, 1.5 * CHAR_SIZE, deltaTime, GRAY);
    } else if (state == NEW_GAME)
        DrawColorTime(screen, charset, screen->w - 13 * CHAR_SIZE, 1.5 * CHAR_SIZE, deltaTime, GRAY);
    else
        DrawColorString(screen, charset, screen->w - 13 * CHAR_SIZE, 1.5 * CHAR_SIZE, "XX:XX.XXX", GRAY);
}

void DrawGameOver(SDL_Surface *screen, SDL_Surface *charset, int score, int time) {
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 15 * CHAR_SIZE, screen->h / 3, 30 * CHAR_SIZE, 12 * CHAR_SIZE},
            0);

    char text[100];
    sprintf(text, "GAME OVER");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 1.5 * CHAR_SIZE,
                    text, RED);

    sprintf(text, "Score: %d", score);
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 3.5 * CHAR_SIZE, text);

    DrawTime(screen, charset, screen->w / 2 - 9 * CHAR_SIZE / 2, screen->h / 3 + 5.5 * CHAR_SIZE, time);

    sprintf(text, "             New game [n]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 9.5 * CHAR_SIZE,
                    text, LIGHT_GREEN);
    sprintf(text, "Quit [Esc]               ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 9.5 * CHAR_SIZE,
                    text, LIGHT_RED);
}

void DrawWin(SDL_Surface *screen, SDL_Surface *charset, int score, int time) {
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 15 * CHAR_SIZE, screen->h / 3, 30 * CHAR_SIZE, 12 * CHAR_SIZE},
            0);

    char text[100];
    sprintf(text, "CONGRATULATIONS! YOU WON!");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 1.5 * CHAR_SIZE,
                    text, YELLOW);

    sprintf(text, "Score: %d", score);
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 3.5 * CHAR_SIZE, text);

    DrawTime(screen, charset, screen->w / 2 - 9 * CHAR_SIZE / 2, screen->h / 3 + 5.5 * CHAR_SIZE, time);

    sprintf(text, "             New game [n]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 9.5 * CHAR_SIZE,
                    text, LIGHT_GREEN);
    sprintf(text, "Quit [Esc]               ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 3 + 9.5 * CHAR_SIZE,
                    text, LIGHT_RED);
}

void DrawHelp(SDL_Surface *screen, SDL_Surface *charset) {
    DrawBox(screen, charset, (SDL_Rect)
            {screen->w / 2 - 15 * CHAR_SIZE, screen->h / 4, 30 * CHAR_SIZE, 26 * CHAR_SIZE}, 1);
    DrawBox(screen, charset, (SDL_Rect)
            {screen->w / 2 - 6 * CHAR_SIZE, screen->h / 4 + CHAR_SIZE, 12 * CHAR_SIZE, 4 * CHAR_SIZE}, 0);

    char text[100];
    sprintf(text, "Controls");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 2.5 * CHAR_SIZE, text);

    sprintf(text, "New game        [n] ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 5.5 * CHAR_SIZE,
                    text, LIGHT_GREEN);
    sprintf(text, "Move up         [\030] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 7.5 * CHAR_SIZE, text);
    sprintf(text, "Move down       [\031] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 9.5 * CHAR_SIZE, text);
    sprintf(text, "Move left       [\032] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 11.5 * CHAR_SIZE, text);
    sprintf(text, "Move right      [\033] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 13.5 * CHAR_SIZE, text);
    sprintf(text, "Quick save      [s] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 15.5 * CHAR_SIZE, text);
    sprintf(text, "Quick load      [l] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 17.5 * CHAR_SIZE, text);
    sprintf(text, "Pause game      [p] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 19.5 * CHAR_SIZE, text);
    sprintf(text, "Show controls   [h] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 21.5 * CHAR_SIZE, text);
    sprintf(text, "Quit game      [Esc]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 4 + 23.5 * CHAR_SIZE,
                    text, LIGHT_RED);
}

//type: 0 - single line, 1 - double line
void DrawBox(SDL_Surface *screen, SDL_Surface *charset, SDL_Rect rect, int type) {
    DrawColorBox(screen, charset, rect, type, BLACK);
}

void DrawColorBox(SDL_Surface *screen, SDL_Surface *charset, SDL_Rect rect, int type, SDL_Color color) {
    int singleBorder[6] = {179, 191, 192, 196, 217, 218};// │ ┐ └ ─ ┘ ┌
    int doubleBorder[6] = {186, 187, 200, 205, 188, 201};// ║ ╗ ╚ ═ ╝ ╔
    int err[6] = {0, 0, 0, 0, 0, 0};
    int *border = type == 0 ? singleBorder :
                  type == 1 ? doubleBorder : err;

    int x = rect.x, y = rect.y, w = rect.w, h = rect.h;

    SDL_FillRect(screen, &(SDL_Rect) {x, y, w, h}, SDL_MapRGB(screen->format, color.r, color.g, color.b));

    for (int i = x + CHAR_SIZE; i < x + w - CHAR_SIZE; i += CHAR_SIZE) { //HORIZONTAL LINES
        SDL_BlitSurface(charset, &(SDL_Rect)
                                {(border[3] % 16) * CHAR_SIZE, (border[3] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                        screen, &(SDL_Rect) {i, y, CHAR_SIZE, CHAR_SIZE});
        SDL_BlitSurface(charset, &(SDL_Rect)
                                {(border[3] % 16) * CHAR_SIZE, (border[3] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                        screen, &(SDL_Rect) {i, y + h - CHAR_SIZE, CHAR_SIZE, CHAR_SIZE});
    }

    for (int i = y + CHAR_SIZE; i < y + h - CHAR_SIZE; i += CHAR_SIZE) { //VERTICAL LINES
        SDL_BlitSurface(charset, &(SDL_Rect)
                                {(border[0] % 16) * CHAR_SIZE, (border[0] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                        screen, &(SDL_Rect) {x, i, CHAR_SIZE, CHAR_SIZE});
        SDL_BlitSurface(charset, &(SDL_Rect)
                                {(border[0] % 16) * CHAR_SIZE, (border[0] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                        screen, &(SDL_Rect) {x + w - CHAR_SIZE, i, CHAR_SIZE, CHAR_SIZE});
    }

    SDL_BlitSurface(charset, &(SDL_Rect) //TOP RIGHT
                            {(border[1] % 16) * CHAR_SIZE, (border[1] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                    screen, &(SDL_Rect) {x + w - CHAR_SIZE, y, CHAR_SIZE, CHAR_SIZE});

    SDL_BlitSurface(charset, &(SDL_Rect) //BOTTOM LEFT
                            {(border[2] % 16) * CHAR_SIZE, (border[2] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                    screen, &(SDL_Rect) {x, y + h - CHAR_SIZE, CHAR_SIZE, CHAR_SIZE});

    SDL_BlitSurface(charset, &(SDL_Rect) //BOTTOM RIGHT
                            {(border[4] % 16) * CHAR_SIZE, (border[4] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                    screen, &(SDL_Rect) {x + w - CHAR_SIZE, y + h - CHAR_SIZE, CHAR_SIZE, CHAR_SIZE});

    SDL_BlitSurface(charset, &(SDL_Rect) // TOP LEFT
                            {(border[5] % 16) * CHAR_SIZE, (border[5] / 16) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE},
                    screen, &(SDL_Rect) {x, y, CHAR_SIZE, CHAR_SIZE});
}

void DrawProgressBar(
        SDL_Surface *screen,
        SDL_Surface *charset,
        SDL_Rect gameArea,
        int value,
        int maxValue,
        SDL_Color color
) {
    SDL_Rect rect = {gameArea.x - CHAR_SIZE, gameArea.y - 2 * CHAR_SIZE, gameArea.w + 2 * CHAR_SIZE, CHAR_SIZE};
    SDL_Rect source, destination;
    source.w = source.h = destination.w = destination.h = CHAR_SIZE;
    source.x = 0;
    source.y = 13 * source.h;
    destination.x = rect.x;
    destination.y = rect.y;
    SDL_FillRect(screen, &(SDL_Rect) {rect.x, rect.y, rect.w * (value / (float) maxValue), rect.h},
                 SDL_MapRGB(screen->format, color.r, color.g, color.b));
    SDL_BlitSurface(charset, &source, screen, &destination);
    source.x = source.w;
    for (int i = 0; i < rect.w / CHAR_SIZE - 2; i++) {
        destination.x += destination.w;
        SDL_BlitSurface(charset, &source, screen, &destination);
    }
    source.x = source.w * 2;
    destination.x += destination.w;
    SDL_BlitSurface(charset, &source, screen, &destination);
}

void FillScreen(SDL_Surface *screen, SDL_Color color) {
    SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, color.r, color.g, color.b));
}

void DrawString(SDL_Surface *screen, SDL_Surface *charset, int x, int y, const char *text) {
    int px, py, c;
    SDL_Rect source, destination;
    source.w = source.h = destination.w = destination.h = CHAR_SIZE;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * CHAR_SIZE;
        py = (c / 16) * CHAR_SIZE;
        source.x = px;
        source.y = py;
        destination.x = x;
        destination.y = y;
        SDL_BlitSurface(charset, &source, screen, &destination);
        x += CHAR_SIZE;
        text++;
    }
}

void DrawColorString(SDL_Surface *screen, SDL_Surface *charset, int x, int y, const char *text, SDL_Color color) {
    SDL_SetSurfaceColorMod(charset, color.r, color.g, color.b);
    DrawString(screen, charset, x, y, text);
    SDL_SetSurfaceColorMod(charset, 255, 255, 255);
}

void DrawTime(SDL_Surface *screen, SDL_Surface *charset, int x, int y, uint32_t time) {
    char text[100];
    sprintf(text, "%02d:%02d.%03d", (time / 1000) / 60, (time / 1000) % 60, time % 1000);
    DrawString(screen, charset, x, y, text);
}

void DrawColorTime(SDL_Surface *screen, SDL_Surface *charset, int x, int y, uint32_t time, SDL_Color color) {
    char text[100];
    sprintf(text, "%02d:%02d.%03d", (time / 1000) / 60, (time / 1000) % 60, time % 1000);
    DrawColorString(screen, charset, x, y, text, color);
}

part_t GetDirection(const point_t last, const point_t curr, const point_t next) {
    part_t snakePart = {BODY, NONE};
    if (last.x == NULL_POS)
        snakePart.type = HEAD;
    else if (next.x == NULL_POS)
        snakePart.type = TAIL;

    //     Vertical movement
    if (last.x == curr.x && curr.x == next.x || (last.x == NULL_POS && curr.x == next.x) ||
        (last.x == curr.x && next.x == NULL_POS)) {
        if ((last.y > curr.y && last.x != NULL_POS) || (next.y != NULL_POS && curr.y > next.y))
            snakePart.direction = DOWN;
        else
            snakePart.direction = UP;
    }
        // Horizontal movement
    else if (last.y == curr.y && curr.y == next.y || (last.y == NULL_POS && curr.y == next.y) ||
             (last.y == curr.y && next.y == NULL_POS)) {
        if ((curr.x < last.x && last.x != NULL_POS) || (curr.x > next.x && next.x != NULL_POS))
            snakePart.direction = RIGHT;
        else
            snakePart.direction = LEFT;
    }
        // Diagonal movement
    else if ((last.y == curr.y && curr.x == next.x) || (last.x == curr.x && curr.y == next.y)) {
        if (last.x > curr.x || next.x > curr.x) {// connects right
            if (curr.y < next.y || curr.y < last.y) // connects down
                snakePart.direction = RIGHTDOWN;
            else // connects up
                snakePart.direction = RIGHTUP;

        } else {// connects left
            if (curr.y < next.y || curr.y < last.y) // connects down
                snakePart.direction = LEFTDOWN;
            else // connects up
                snakePart.direction = LEFTUP;
        }
    }

    return snakePart;
}

void DrawSnake(
        SDL_Surface
        *screen,
        SDL_Surface *objects,
        const SDL_Rect gameArea,
        const point_t *pos,
        const int length
) {
    SDL_Rect source, destination;
    source.w = source.h = destination.w = destination.h = OBJECT_SIZE;

    for (int i = 0; i < length; i++) {
        part_t snakePart = GetDirection(
                i > 0 ? pos[i - 1] : (point_t) {NULL_POS, NULL_POS},
                pos[i],
                i < length - 1 ? pos[i + 1] : (point_t) {NULL_POS, NULL_POS});

        switch (snakePart.type) {
            case HEAD:
                source.y = 0;
                break;
            case BODY:
            default:
                if (snakePart.direction >= RIGHT && snakePart.direction <= UP)
                    source.y = i % 2 ? OBJECT_SIZE : 2 * OBJECT_SIZE;
                else
                    source.y = i % 2 ? 5 * OBJECT_SIZE : 6 * OBJECT_SIZE;
                break;
            case TAIL:
                source.y = i % 2 ? 3 * OBJECT_SIZE : 4 * OBJECT_SIZE;
        }

        switch (snakePart.direction) {
            case RIGHT:
            case LEFTUP:
                source.x = 0;
                break;
            case DOWN:
            case LEFTDOWN:
                source.x = OBJECT_SIZE;
                break;
            case LEFT:
            case RIGHTDOWN:
                source.x = 2 * OBJECT_SIZE;
                break;
            case UP:
            case RIGHTUP:
                source.x = 3 * OBJECT_SIZE;
                break;
            case NONE:
            default:
                source.x = 7 * OBJECT_SIZE;
                source.y = 7 * OBJECT_SIZE;
                break;
        }
        destination.x = pos[i].x * OBJECT_SIZE + gameArea.x;
        destination.y = pos[i].y * OBJECT_SIZE + gameArea.y;
        SDL_BlitSurface(objects, &source, screen, &destination);
    }
}

void DrawObjects(
        SDL_Surface *screen,
        SDL_Surface *objects,
        const SDL_Rect gameArea,
        const point_t *pos,
        const int length,
        int type
) {
    SDL_Rect source, destination;
    source.w = source.h = destination.w = destination.h = OBJECT_SIZE;

    for (int i = 0; i < length; i++) {
        if (pos[i].x == NULL_POS) break;
        if (i == APPLE) {
            source.x = 6 * OBJECT_SIZE;
            source.y = type * OBJECT_SIZE;
        } else if (i == ORANGE) {
            source.x = 7 * OBJECT_SIZE;
            source.y = type * OBJECT_SIZE;
        } else {
            source.x = 5 * OBJECT_SIZE;
            source.y = 0;
        }
        destination.x = pos[i].x * OBJECT_SIZE + gameArea.x;
        destination.y = pos[i].y * OBJECT_SIZE + gameArea.y;
        SDL_BlitSurface(objects, &source, screen, &destination);
    };
};

void DrawGame(SDL_Surface *screen, game_t game, uint32_t *time) {
    DrawSnake(screen, game.objectMap, game.area, game.snake.pos, game.snake.length);
    if (game.state != GAME_OVER && game.state != WIN)
        if (*time < ANIMATION_TIME / 2)
            DrawObjects(screen, game.objectMap, game.area, game.objectPos, 2 + game.config.portal_count, 0);
        else if (*time >= ANIMATION_TIME / 2 && *time < ANIMATION_TIME)
            DrawObjects(screen, game.objectMap, game.area, game.objectPos, 2 + game.config.portal_count, 1);
        else *time -= ANIMATION_TIME;
    else
        DrawObjects(screen, game.objectMap, game.area, game.objectPos, 2 + game.config.portal_count, 0);
}

#define SCORES_OFFSET 12    //number of rows

void DrawScores(SDL_Surface *screen, SDL_Surface *charset, score_t *scores) {
    int baseY = screen->h / 3 + SCORES_OFFSET * CHAR_SIZE;
    DrawBox(screen, charset, (SDL_Rect)
            {screen->w / 2 - 7.5 * CHAR_SIZE, baseY, 15 * CHAR_SIZE, 11 * CHAR_SIZE}, 0);

    char text[100];
    sprintf(text, "High Scores");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2,
                    baseY + 2 * CHAR_SIZE, text, YELLOW);

    for (int i = 0; i < 3; i++) {
        sprintf(text, "%s", scores[i].name);
        DrawString(screen, charset, screen->w / 2 - 5 * CHAR_SIZE,
                   baseY + 4.5 * CHAR_SIZE + i * (1.5 * CHAR_SIZE), text);

        sprintf(text, "%d", scores[i].score);
        DrawString(screen, charset, screen->w / 2 + 5 * CHAR_SIZE - strlen(text) * CHAR_SIZE,
                   baseY + 4.5 * CHAR_SIZE + i * (1.5 * CHAR_SIZE), text);
    }
}

void DrawInput(SDL_Surface *screen, SDL_Surface *charset, char *name, int blink) {
    char text[100];
    sprintf(text, "Enter your name:");
    DrawBox(screen, charset, (SDL_Rect)
            {screen->w / 2 - ((strlen(text) + 14) * CHAR_SIZE) / 2, screen->h / 2 - 2 * CHAR_SIZE,
             (strlen(text) + 14) * CHAR_SIZE, 8 * CHAR_SIZE}, 0);
    DrawString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 2 - 1 * CHAR_SIZE, text);

    sprintf(text, "     ");
    text[0] = strlen(name) > 0 ? name[0] : blink ? ' ' : '_';
    text[2] = strlen(name) > 1 ? name[1] : blink && strlen(name) ? ' ' : '_';
    text[4] = strlen(name) > 2 ? name[2] : blink && strlen(name) == 2 ? ' ' : '_';
    DrawString(screen, charset, screen->w / 2 - (strlen(text) * CHAR_SIZE) / 2, screen->h / 2 + CHAR_SIZE, text);

    sprintf(text, "             Confirm [Enter]");
    if (strlen(name) < 3)
        DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 2 + 4 * CHAR_SIZE,
                        text, GRAY);
    else
        DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 2 + 4 * CHAR_SIZE,
                        text, LIGHT_GREEN);
    sprintf(text, "Cancel [Esc]                ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * CHAR_SIZE / 2, screen->h / 2 + 4 * CHAR_SIZE,
                    text, LIGHT_RED);
}