
/************************
	 *  Player.c
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"
#include "Header.h"
#include "Ball.h"
#include "Rectangle_Functions.h"

int confirm_keystate(int key_val)
{
    if (!key_state[key_val])
        return 0;
    return 1;
}
static void _destroy(Player *this)
{
    if (NULL != this)
        free(this);
}
static char *_get_score(Player *this)
{
    sprintf(this->score_str, "%d", this->score);
    return this->score_str;
}
static void _render(void *obj, struct SDL_Renderer *renderer)
{
    Player *this = (Player *)obj;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

static void _player_bindings(Player *this, int up, int down)
{
    if (confirm_keystate(up) && this->rect.y > 0)
        this->rect.y -= PLAYER_VELOCITY;
    else if (confirm_keystate(down) && get_bottom(this->rect) < WINDOW_HEIGHT)
        this->rect.y += PLAYER_VELOCITY;
}

Player *player_create(struct SDL_Renderer *renderer, int x, int y)
{
    Player *this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->render = _render;
    this->player_bindings = _player_bindings;
    this->get_score = _get_score;

    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = PLAYER_WIDTH;
    this->rect.h = PLAYER_HEIGHT;

    this->score = 0;

    return this;
}