
/************************
	 *  Ball.c   
     *  Contains all type defined functions for the ping pong ball        
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Ball.h"
#include "Header.h"
#include "Window_and_Renderer.h"
#include "Player.h"

/**
 * ratio
 * such that if x is the returned value
 * 
 *         x / MAX_VELOCITY_Y  =  value / 100
 *  if value = 25 then 
 *         x / MAX_VELOCITY_Y  =  25 / 100
 *         x * 100 = MAX_VELOCITY * 25
 *         x = (MAX_VELOCITY * 25) / 100
 *         return x         
 */
static int ratio(int value)
{
    int y = MAX_VELOCITY_Y * value;
    return y / 100;
}

/**
 * get_middle_y
 * returns the middle y value of the rectangle
 */
static int get_middle_y(struct SDL_Rect rect)
{
    return (rect.y + (rect.h / 2));
}

/**
 * get_intersection
 * Returns the difference in middle y values of two rectangles.
 * 
 * If the middle_y_value of r1 is 100, and the middle_y_value of r2 is 150
 * Then the intersection is 50. 
 */
static int get_intersection(struct SDL_Rect r1, struct SDL_Rect r2)
{
    int ball   = (get_middle_y(r1));
    int player = (get_middle_y(r2));

    return (ball - player);
}

/**
 * ricochet
 * Changes the balls velocity to positive or negative.
 * the value of the velocity is ratio of the intersection of ball and player with respect to the height of the player and the maximum allowed velocity.
 */
static int ricochet(Ball* ball, Player* player)
{
    int neg = 1;
    if (ball->vel_y < 0)
        neg = -1;

    return ball->vel_y = ratio(abs(get_intersection(ball->rect, player->rect))) * neg;
}

/* Frees memory allocated in Ball object creation */
static void _destroy(Ball* this)
{
    if (NULL != this)
        free(this);

    this = NULL;
}

/* Determines the balls behavior based on which wall the ball has collided with and postion of the player */
static void _behavior(Ball* this, Player* player_1, Player* player_2)
{
    if (this->rect.x < -1) {
        if (this->ball_in_play) {
            player_2->score++;
            this->ball_in_play = 0;
        }
        this->rect.x = WINDOW_WIDTH - 50;
        this->vel_x  = this->start_vel_x * -1;
        this->vel_y  = this->start_vel_y;
        if ((player_2->rect.y + (player_2->rect.h / 2)) > WINDOW_HEIGHT / 2)
            this->rect.y = 0;
        else
            this->rect.y = WINDOW_HEIGHT - 50;
    } else if (this->rect.x > (WINDOW_WIDTH)) {
        if (this->ball_in_play) {
            player_1->score++;
            this->ball_in_play = 0;
        }
        this->rect.x = 0;
        this->vel_x  = this->start_vel_x;
        this->vel_y  = this->start_vel_y;
        if ((player_1->rect.y + (player_1->rect.h / 2)) > WINDOW_HEIGHT / 2)
            this->rect.y = 0;
        else
            this->rect.y = WINDOW_HEIGHT - 50;
    } else if (this->rect.y < -1 || this->rect.y > (WINDOW_HEIGHT - this->rect.h)) {
        this->vel_y = -this->vel_y;
    }
    this->rect.x += this->vel_x;
    this->rect.y += this->vel_y;
}

/* Checks if the ball has collided with a player */
static void _collision(Ball* this, Player* player)
{
    if (SDL_HasIntersection(&player->rect, &this->rect)) {
        this->ball_in_play = 1;
        this->vel_x        = -this->vel_x;
        if (this->vel_x < 0)
            this->vel_x--;
        else
            this->vel_x++;

        this->vel_y = ricochet(this, player);
    }
}

/* Renders ball image */
static void _render(void* obj, struct SDL_Renderer* renderer)
{
    Ball* this = (Ball*)obj;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

Ball* ball_create(const char* path, struct SDL_Renderer* renderer)
{
    Ball* this = malloc(sizeof(*this));

    this->destroy     = _destroy;
    this->render      = _render;
    this->behavior    = _behavior;
    this->collision   = _collision;
    this->start_vel_x = MIN_VELOCITY_X;
    this->start_vel_y = MIN_VELOCITY_Y;
    this->vel_x       = this->start_vel_x;
    this->vel_y       = this->start_vel_y;

    this->ball_in_play = 0;

    this->rect.w = 15;
    this->rect.h = 15;
    return this;
}
