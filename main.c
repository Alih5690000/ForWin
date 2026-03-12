#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int main(int,char**){
    SDL_Window* window=SDL_CreateWindow("SDL",SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,800,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,
        SDL_RENDERER_ACCELERATED);
    bool running=true;
    SDL_FRect plr={0.f,0.f,100.f,100.f};
    int plr_speed=400;
    float dt;
    int start,end;
    while (running){
        start=SDL_GetTicks();
        dt=(start-end)/1000.f;
        end=start;
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type==SDL_QUIT)
                running=false;
        }
        const Uint8* keys=SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W]){
            plr.y-=plr_speed*dt;
        }
        if (keys[SDL_SCANCODE_S]){
            plr.y+=plr_speed*dt;
        }
        if (keys[SDL_SCANCODE_A]){
            plr.x-=plr_speed*dt;
        }
        if (keys[SDL_SCANCODE_D]){
            plr.x+=plr_speed*dt;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderFillRectF(renderer,&plr);
        SDL_RenderPresent(renderer);
    }
    return 0;
}
