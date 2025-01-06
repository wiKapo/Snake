#include "draw.h"

#define ANIMATION_TIME 250

void DrawTopBar(SDL_Surface *screen, SDL_Surface *charset, uint32_t deltaTime, state_et state, int score) {
    DrawBox(screen, charset, (SDL_Rect) {0, 0, screen->w, 30}, 1);

    char text[100];
    sprintf(text, "Snake by wiKapo");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, 10, text, GREEN);

    sprintf(text, "Score: %05d", score);
    DrawString(screen, charset, 30, 10, text);

    sprintf(text, "1234ABCDEFGHI", score);
    DrawColorString(screen, charset, 128, 10, text, DARK_GRAY);

    if (state == PLAY)
        DrawTime(screen, charset, screen->w - 100, 10, deltaTime);
    else if (state == PAUSE || state == PAUSE_INFO) {
        DrawString(screen, charset, screen->w - 100 - 9 * 8, 10, "[PAUSED]");
        DrawColorTime(screen, charset, screen->w - 100, 10, deltaTime, GRAY);
    } else if (state == NEW_GAME)
        DrawColorTime(screen, charset, screen->w - 100, 10, deltaTime, GRAY);
    else
        DrawColorString(screen, charset, screen->w - 100, 10, "XX:XX.XXX", GRAY);
}

void DrawGameOver(SDL_Surface *screen, SDL_Surface *charset, int score, int time) {
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 30 * 8 / 2, screen->h / 3, 30 * 8, 12 * 8}, 0);

    char text[100];
    sprintf(text, "GAME OVER");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 15, text, RED);

    sprintf(text, "Score: %d", score);
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 30, text);

    DrawTime(screen, charset, screen->w / 2 - 9 * 8 / 2, screen->h / 3 + 45, time);

    sprintf(text, "             New game [n]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 75, text,
                    LIGHT_GREEN);
    sprintf(text, "Quit [Esc]               ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 75, text,
                    LIGHT_RED);
}

void DrawWin(SDL_Surface *screen, SDL_Surface *charset, int score, int time) {
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 30 * 8 / 2, screen->h / 3, 30 * 8, 12 * 8}, 0);

    char text[100];
    sprintf(text, "CONGRATULATIONS! YOU WON!");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 15, text, YELLOW);

    sprintf(text, "Score: %d", score);
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 30, text);

    DrawTime(screen, charset, screen->w / 2 - 9 * 8 / 2, screen->h / 3 + 45, time);

    sprintf(text, "             New game [n]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 75, text,
                    LIGHT_GREEN);
    sprintf(text, "Quit [Esc]               ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 75, text,
                    LIGHT_RED);
}

void DrawHelp(SDL_Surface *screen, SDL_Surface *charset) {
    //Main box TODO fix size
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 4, screen->h / 4, screen->w / 2, screen->h / 4 + 16}, 1);
    //"Controls" text box TODO fix size
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 50, screen->h / 4 + 10, 100, 30}, 0);

    char text[100];
    sprintf(text, "Controls");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 20, text);

    sprintf(text, "New game        [n] ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 40, text,
                    LIGHT_GREEN);
    sprintf(text, "Move up         [\030] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 55, text);
    sprintf(text, "Move down       [\031] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 70, text);
    sprintf(text, "Move left       [\032] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 85, text);
    sprintf(text, "Move right      [\033] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 100, text);
    sprintf(text, "Quick save      [s] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 115, text);
    sprintf(text, "Quick load      [l] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 130, text);
    sprintf(text, "Pause game      [p] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 145, text);
    sprintf(text, "Show controls   [h] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 160, text);
    sprintf(text, "Quit game      [Esc]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 175, text,
                    LIGHT_RED);
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

    for (int i = x + 8; i < x + w - 8; i += 8) {
        SDL_BlitSurface(charset, &(SDL_Rect) {(border[3] % 16) * 8, (border[3] / 16) * 8, 8, 8},
                        screen, &(SDL_Rect) {i, y, 8, 8});
        SDL_BlitSurface(charset, &(SDL_Rect) {(border[3] % 16) * 8, (border[3] / 16) * 8, 8, 8},
                        screen, &(SDL_Rect) {i, y + h - 8, 8, 8});
    }

    for (int i = y + 8; i < y + h - 8; i += 8) {
        SDL_BlitSurface(charset, &(SDL_Rect) {(border[0] % 16) * 8, (border[0] / 16) * 8, 8, 8},
                        screen, &(SDL_Rect) {x, i, 8, 8});
        SDL_BlitSurface(charset, &(SDL_Rect) {(border[0] % 16) * 8, (border[0] / 16) * 8, 8, 8},
                        screen, &(SDL_Rect) {x + w - 8, i, 8, 8});
    }

    SDL_BlitSurface(charset, &(SDL_Rect) {(border[1] % 16) * 8, (border[1] / 16) * 8, 8, 8},
                    screen, &(SDL_Rect) {x + w - 8, y, 8, 8});              //TOP RIGHT

    SDL_BlitSurface(charset, &(SDL_Rect) {(border[2] % 16) * 8, (border[2] / 16) * 8, 8, 8},
                    screen, &(SDL_Rect) {x, y + h - 8, 8, 8});              //BOTTOM LEFT

    SDL_BlitSurface(charset, &(SDL_Rect) {(border[4] % 16) * 8, (border[4] / 16) * 8, 8, 8},
                    screen, &(SDL_Rect) {x + w - 8, y + h - 8, 8, 8});   //BOTTOM RIGHT

    SDL_BlitSurface(charset, &(SDL_Rect) {(border[5] % 16) * 8, (border[5] / 16) * 8, 8, 8},
                    screen, &(SDL_Rect) {x, y, 8, 8});                          // TOP LEFT
}

void DrawProgressBar(
        SDL_Surface *screen,
        SDL_Surface *charset,
        SDL_Rect rect,
        int value,
        int maxValue,
        SDL_Color color
) {
    SDL_Rect source, destination;
    source.w = source.h = destination.w = destination.h = 8;
    source.x = 0;
    source.y = 13 * source.h;
    destination.x = rect.x;
    destination.y = rect.y;
    SDL_FillRect(screen, &(SDL_Rect) {rect.x, rect.y, rect.w * (value / (float) maxValue), rect.h},
                 SDL_MapRGB(screen->format, color.r, color.g, color.b));
    SDL_BlitSurface(charset, &source, screen, &destination);
    source.x = source.w;
    for (int i = 0; i < rect.w / 8 - 2; i++) {
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
    source.w = source.h = destination.w = destination.h = 8;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        source.x = px;
        source.y = py;
        destination.x = x;
        destination.y = y;
        SDL_BlitSurface(charset, &source, screen, &destination);
        x += 8;
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

    // Vertical movement
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
    source.w = source.h = destination.w = destination.h = 32;

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
                    source.y = i % 2 ? 32 : 64;
                else
                    source.y = i % 2 ? 160 : 192;
                break;
            case TAIL:
                source.y = i % 2 ? 96 : 128;
        }

        switch (snakePart.direction) {
            case RIGHT:
            case LEFTUP:
                source.x = 0;
                break;
            case DOWN:
            case LEFTDOWN:
                source.x = 32;
                break;
            case LEFT:
            case RIGHTDOWN:
                source.x = 64;
                break;
            case UP:
            case RIGHTUP:
                source.x = 96;
                break;
            case NONE:
            default:
                source.x = 224;
                source.y = 224;
                break;
        }
        destination.x = pos[i].x * 32 + gameArea.x;
        destination.y = pos[i].y * 32 + gameArea.y;
        SDL_BlitSurface(objects,
                        &source, screen, &destination);
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
    source.w = source.h = destination.w = destination.h = 32;

    for (int i = 0; i < length; i++) {
        if (pos[i].x == NULL_POS) break;
        if (i == APPLE) {
            source.x = 192;
            source.y = type * 32;
        } else if (i == ORANGE) {
            source.x = 224;
            source.y = type * 32;
        } else {
            source.x = 160;
            source.y = 0;
        }
        destination.x = pos[i].x * 32 + gameArea.x;
        destination.y = pos[i].y * 32 + gameArea.y;
        SDL_BlitSurface(objects, &source, screen, &destination);
    };
};

void DrawGame(SDL_Surface *screen, game_t game, uint32_t *time) {
    DrawSnake(screen, game.objectMap, game.area, game.snake.pos, game.snake.length);
    if (*time < ANIMATION_TIME / 2)
        DrawObjects(screen, game.objectMap, game.area, game.objectPos, 2 + game.config.portal_count, 0);
    else if (*time >= ANIMATION_TIME / 2 && *time < ANIMATION_TIME)
        DrawObjects(screen, game.objectMap, game.area, game.objectPos, 2 + game.config.portal_count, 1);
    else *time -= ANIMATION_TIME;
}