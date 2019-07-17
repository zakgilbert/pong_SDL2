
/************************
	 *  Player.c
	*/

#include "Player.h"
#include "Header.h"
#include "Ball.h"

int confirm_keystate(int key_val)
{
    if (!key_state[key_val])
        return 0;
    return 1;
}

enum bindings_player_1
{
    W = SDL_SCANCODE_W,
    S = SDL_SCANCODE_S,
    A = SDL_SCANCODE_A,
    D = SDL_SCANCODE_D
};

enum bindings_player_2
{
    UP = SDL_SCANCODE_UP,
    DOWN = SDL_SCANCODE_DOWN,
    LEFT = SDL_SCANCODE_LEFT,
    RIGHT = SDL_SCANCODE_RIGHT
};

static void _render(void *obj, struct SDL_Renderer *renderer)
{
    Player *this = (Player *)obj;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

static void _player_1_bindings(Player *this)
{
    if (confirm_keystate(W))
        this->rect.y -= this->vel;
    else if (confirm_keystate(S))
        this->rect.y += this->vel;
}

static void _player_2_bindings(Player *this)
{
    if (confirm_keystate(UP))
        this->rect.y -= this->vel;
    else if (confirm_keystate(DOWN))
        this->rect.y += this->vel;
}

Player *player_create(struct SDL_Renderer *renderer, int x, int y, int w, int h, int player)
{
    Player *this = malloc(sizeof(*this));
    this->render = _render;
    this->player_1_bindings = _player_1_bindings;
    this->player_2_bindings = _player_2_bindings;

    this->rect.w = w;
    this->rect.h = h;
    this->rect.x = x;
    this->rect.y = y;

    this->vel = 20;

    this->player = player;

    return this;
}