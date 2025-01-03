#include "draw.h"

void DrawTopBar(SDL_Surface *screen, SDL_Surface *charset, uint32_t deltaTime, state_et state, int score) {
    DrawBox(screen, charset, (SDL_Rect) {0, 0, screen->w, 30}, 1);

    char text[100];
    sprintf(text, "Snake by wiKapo");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, 10, text, (SDL_Color) {0, 255, 0});

    sprintf(text, "Score: %04d", score);
    DrawString(screen, charset, 30, 10, text);

    sprintf(text, "1234ABCDEFGHI", score);
    DrawColorString(screen, charset, 128, 10, text, (SDL_Color) {64, 64, 64});

    if (state == PLAY)
        DrawTime(screen, charset, screen->w - 100, 10, deltaTime);
    else if (state == PAUSE) {
        DrawString(screen, charset, screen->w - 100 - 9 * 8, 10, "[PAUSED]");
        DrawColorTime(screen, charset, screen->w - 100, 10, deltaTime, (SDL_Color) {128, 128, 128});
    } else if (state == NEW_GAME)
        DrawColorTime(screen, charset, screen->w - 100, 10, deltaTime, (SDL_Color) {128, 128, 128});
    else
        DrawColorString(screen, charset, screen->w - 100, 10, "XX:XX.XXX", (SDL_Color) {128, 128, 128});
}

void DrawGameOver(SDL_Surface *screen, SDL_Surface *charset, int score, int time) {
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 30 * 8 / 2, screen->h / 3, 30 * 8, 12 * 8}, 0);

    char text[100];
    sprintf(text, "GAME OVER");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 15, text);

    sprintf(text, "Score: %d", score);
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 30, text);

    DrawTime(screen, charset, screen->w / 2 - 9 * 8 / 2, screen->h / 3 + 45, time);

    sprintf(text, "             New game [n]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 75, text,
                    (SDL_Color) {128, 255, 128});
    sprintf(text, "Quit [Esc]               ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 75, text,
                    (SDL_Color) {255, 128, 128});
}

void DrawWin(SDL_Surface *screen, SDL_Surface *charset, int score, int time) {
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 30 * 8 / 2, screen->h / 3, 30 * 8, 12 * 8}, 0);

    char text[100];
    sprintf(text, "CONGRATULATIONS! YOU WON!");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 30, text);

    sprintf(text, "Score: %d", score);
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 15, text);

    DrawTime(screen, charset, screen->w / 2 - 9 * 8 / 2, screen->h / 3 + 45, time);

    sprintf(text, "Quit [Esc]   New game [n]");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 75, text);
}

void DrawHelp(SDL_Surface *screen, SDL_Surface *charset) {
    //Main box
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 4, screen->h / 4, screen->w / 2, screen->h / 4}, 1);
    //"Controls" text box
    DrawBox(screen, charset, (SDL_Rect) {screen->w / 2 - 50, screen->h / 4 + 10, 100, 30}, 0);

    char text[100];
    sprintf(text, "Controls");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 20, text);

    sprintf(text, "New game        [n] ");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 40, text,
                    (SDL_Color) {128, 255, 128});
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
    sprintf(text, "Show controls   [h] ");
    DrawString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 145, text);
    sprintf(text, "Quit game      [Esc]");
    DrawColorString(screen, charset, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4 + 160, text,
                    (SDL_Color) {255, 128, 128});
}

//type: 0 - single line, 1 - double line
void DrawBox(SDL_Surface *screen, SDL_Surface *charset, SDL_Rect rect, int type) {
    DrawColorBox(screen, charset, rect, type, SDL_MapRGB(screen->format, 0, 0, 0));
}

void DrawColorBox(SDL_Surface *screen, SDL_Surface *charset, SDL_Rect rect, int type, uint32_t color) {
    int singleBorder[6] = {179, 191, 192, 196, 217, 218};// │ ┐ └ ─ ┘ ┌
    int doubleBorder[6] = {186, 187, 200, 205, 188, 201};// ║ ╗ ╚ ═ ╝ ╔
    int err[6] = {0, 0, 0, 0, 0, 0};
    int *border = type == 0 ? singleBorder :
                  type == 1 ? doubleBorder : err;

    int x = rect.x, y = rect.y, w = rect.w, h = rect.h;

    SDL_FillRect(screen, &(SDL_Rect) {x, y, w, h}, color);

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

void DrawString(SDL_Surface *screen, SDL_Surface *charset, int x, int y, const char *text) {
    int px, py, c;
    SDL_Rect source, destination;
    source.w = 8;
    source.h = 8;
    destination.w = 8;
    destination.h = 8;
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
    if (last.x == -99)
        snakePart.type = HEAD;
    else if (next.x == -99)
        snakePart.type = TAIL;

    // Vertical movement
    if (last.x == curr.x && curr.x == next.x || (last.x == -99 && curr.x == next.x) ||
        (last.x == curr.x && next.x == -99)) {
        if ((last.y > curr.y && last.x != -99) || (next.y != -99 && curr.y > next.y))
            snakePart.direction = DOWN;
        else
            snakePart.direction = UP;
    }
        // Horizontal movement
    else if (last.y == curr.y && curr.y == next.y || (last.y == -99 && curr.y == next.y) ||
             (last.y == curr.y && next.y == -99)) {
        if ((curr.x < last.x && last.x != -99) || (curr.x > next.x && next.x != -99))
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

void
DrawSnake(SDL_Surface *screen, SDL_Surface *objects, const SDL_Rect gameArea, const point_t *pos, const int length) {
    SDL_Rect source, destination;
    source.w = 32;
    source.h = 32;
    destination.w = 32;
    destination.h = 32;

    for (int i = 0; i < length; i++) {
        part_t snakePart = GetDirection(
                i > 0 ? pos[i - 1] : (point_t) {-99, -99},
                pos[i],
                i < length - 1 ? pos[i + 1] : (point_t) {-99, -99});

        switch (snakePart.type) {
            case HEAD:
                source.y = 0;
                break;
            case BODY:
            default:
                if (snakePart.direction >= RIGHT && snakePart.direction <= UP)
                    source.y = i % 2 ? 32 : 64;
                else source.y = i % 2 ? 160 : 192;
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
        SDL_BlitSurface(objects, &source, screen, &destination);
    }
}

//void DrawObject(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *objects) {
//    int px, py, c;
//    SDL_Rect source, destination;
//    source.w = 32;
//    source.h = 32;
//    destination.w = 32;
//    destination.h = 32;
//    while (*text) {
//        c = *text & 255;
//        px = (c % 8) * 32;
//        py = (c / 8) * 32;
//        source.x = px;
//        source.y = py;
//        destination.x = x;
//        destination.y = y;
//        SDL_BlitSurface(objects, &source, screen, &destination);
//        x += 32;
//        text++;
//    };
//};

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, nullptr, screen, &dest);
}

//void TestPrint(SDL_Surface *screen, SDL_Surface *objects) {
//    SDL_Rect source, destination;
//    source.w = 32;
//    source.h = 32;
//    destination.w = 32;
//    destination.h = 32;
//    source.x = 0;
//    source.y = 0;
//    destination.x = 100;
//    destination.y = 100;
//    SDL_BlitSurface(objects, &source, screen, &destination);
//}
