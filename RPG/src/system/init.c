
// This is where the MAIN GAME initializations occurs

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "../common.h"
#include "../system.h"
#include "../game.h"

extern App app;

void initSDL(void)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    app.window = SDL_CreateWindow("ADVENTURE - QUESTS (Sreerag's Project)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_ShowCursor(0);
}

void initGameSystem(void)
{
    initFonts();
    initEntityFactory();
    initAStar();
    initSound();
}

void cleanup(void)
{
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);

    SDL_Quit();
}