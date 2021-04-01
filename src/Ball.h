#ifndef BALL_H
#define BALL_H

typedef struct _Player Player;

typedef struct _Ball
{
    /* Frees memory allocated in Ball object creation */
    void (*destroy)(struct _Ball *this);

    /* Determines the balls behavior based on which wall the ball has collided with and postion of the player */
    void (*behavior)(struct _Ball *this, Player *player_1, Player *player_2);

    /* Checks if the ball has collided with a player */
    void (*collision)(struct _Ball *this, Player *player);

    /* Renders ball image */
    void (*render)(void *obj, struct SDL_Renderer *renderer);

    struct SDL_Texture *texture;
    struct SDL_Rect rect;

    int vel_x;
    int vel_y;
    int start_vel_x;
    int start_vel_y;
    
    int ball_in_play;

} Ball;

Ball *ball_create(const char *path, struct SDL_Renderer *renderer);

#endif /* BALL_H */
