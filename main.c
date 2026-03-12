#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <windows.h>
#include <math.h>

#ifndef __WIN32
typedef void* HINSTANCE;
#endif

SDL_FRect CenterFRect(const SDL_FRect outer, 
    float iw, float ih){
    SDL_FRect result;
    result.w = iw;
    result.h = ih;
    result.x = outer.x + (outer.w - iw) / 2.0f;
    result.y = outer.y + (outer.h - ih) / 2.0f;
    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nShowCmd){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window=SDL_CreateWindow("SDL",SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,800,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,
        SDL_RENDERER_ACCELERATED);
    SDL_Texture* txt=SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,
        1000,800);
    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(txt,SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer,txt);
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer,NULL);
    bool running=true;
    SDL_FRect plr={0.f,0.f,100.f,100.f};
    int plr_speed=400;
    float dt;
    bool drawing=false;
    bool erasing=false;
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
        Uint32 mouse=SDL_GetMouseState(NULL,NULL);
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
        drawing=false;
        erasing=false;
        if (mouse & SDL_BUTTON_LMASK) drawing=true;
        if (mouse & SDL_BUTTON_RMASK) erasing=true;

        SDL_SetRenderTarget(renderer,txt);

        if (drawing){
            SDL_FRect trail=CenterFRect(plr,10.f,10.f);
            SDL_SetRenderDrawColor(renderer,0,0,255,255);
            SDL_RenderFillRectF(renderer,&trail);
        }
        if (erasing){
            SDL_FRect trail=plr;
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderFillRectF(renderer,&trail);
        }

        SDL_SetRenderTarget(renderer,NULL);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,txt,NULL,NULL);

        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderFillRectF(renderer,&plr);

        SDL_RenderPresent(renderer);
    }
    return 0;
}
