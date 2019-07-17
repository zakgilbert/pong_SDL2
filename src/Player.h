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
    void (*player_1_bindings)(struct _Player *this);
    void (*player_2_bindings)(struct _Player *this);
    struct SDL_Rect rect;

    int player;
    int vel;
} Player;
Player *player_create(struct SDL_Renderer *renderer, int x, int y, int w, int h, int player);
#endif /* PLAYER_H */
