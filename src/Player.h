#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct _Ball Ball;

int confirm_keystate(int key_val);

typedef struct _Player
{
    void (*destroy)(struct _Player *this);
    void (*render)(void *obj, struct SDL_Renderer *renderer);
    void (*player_bindings)(struct _Player *this, int up, int down);
    char *(*get_score)(struct _Player *this);
    struct SDL_Rect rect;

    int player;
    int vel;

    int score;
    char score_str[10];

} Player;
Player *player_create(struct SDL_Renderer *renderer, int x, int y, int w, int h, int player);
#endif /* PLAYER_H */
