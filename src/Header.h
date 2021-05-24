#ifndef HEADER_H
#define HEADER_H

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define FPS 60
#define MAX_VELOCITY_Y 35
#define MAX_VELOCITY_X 30
#define MIN_VELOCITY_Y 4
#define MIN_VELOCITY_X 8

#define PLAYER_VELOCITY 16
#define PLAYER_WIDTH 17
#define PLAYER_HEIGHT 110

#define BALL_SIZE 15

#define PRIME_1 163
#define PRIME_2 151

extern Uint8* key_state;
Uint8* key_state;

extern int TURN;
int TURN;

enum bindings_player_1 {
    W = SDL_SCANCODE_W,
    S = SDL_SCANCODE_S,
    A = SDL_SCANCODE_A,
    D = SDL_SCANCODE_D
};

enum bindings_player_2 {
    UP    = SDL_SCANCODE_UP,
    DOWN  = SDL_SCANCODE_DOWN,
    LEFT  = SDL_SCANCODE_LEFT,
    RIGHT = SDL_SCANCODE_RIGHT
};
#endif