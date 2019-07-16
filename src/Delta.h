#ifndef DELTA_H
#define DELTA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

void set_up_timer();
void start_timer();
void reset_timer();
void delay();
void print_time_delay();
int check_delta();
void update_delta();

#endif