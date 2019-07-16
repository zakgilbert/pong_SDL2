
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

    set_up_timer();
    quit = 0;
    Render_Q *test_q = render_q_create();

    for (int i = 0; i < 10; i++)
    {
        test_q->enqueue(test_q, test_q->create_node(NULL, test_func));
    }
    test_q->print(test_q);
    test_q = test_q->execute(test_q, renderer);
    test_q->print(test_q);
    union SDL_Event ev;
    while (!quit)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            }
        }
    }
    test_q->destroy(test_q);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
