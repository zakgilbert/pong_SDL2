
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include "Header.h"
#include "Window_and_Renderer.h"
#include "Delta.h"
#include "Render_Q.h"
#include "Ball.h"
#include "Player.h"

void test_func(void *obj, struct SDL_Renderer *renderer)
{
    printf("function is being called\n");
}

int main(int argc, char **argv)
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    int quit;
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    window = make_window("Window");
    renderer = make_renderer(&window);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    set_up_timer();
    quit = 0;

    Ball *ball = ball_create("art/ball.png", renderer);
    Render_Q *render_q = render_q_create();
    Player *player_1 = player_create(renderer);
    int spd = 20;
    ball->rect.x = 0;
    ball->rect.y = WINDOW_HEIGHT / 2;
    union SDL_Event ev;
    while (!quit)
    {
        start_timer();
        render_q->enqueue(render_q, render_q->create_node(ball, ball->render));
        render_q->enqueue(render_q, render_q->create_node(player_1, player_1->render));
        SDL_RenderClear(renderer);
        render_q = render_q->execute(render_q, renderer);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&ev) != 0)
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            }
        }

        ball->behavior(ball);
        delay();
        reset_timer();
    }
    ball->destroy(ball);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
