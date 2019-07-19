#ifndef HEADER_H
#define HEADER_H

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define FPS 60
#define MAX_VELOCITY_Y 40
#define MAX_VELOCITY_X 35
#define MIN_VELOCITY_Y 8
#define MIN_VELOCITY_X 16

#define PLAYER_VELOCITY 20
#define PLAYER_WIDTH 15
#define PLAYER_HEIGHT 100

#define PRIME_1 163
#define PRIME_2 151

extern Uint8 *key_state;
Uint8 *key_state;

extern int TURN;
int TURN;

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
#endif