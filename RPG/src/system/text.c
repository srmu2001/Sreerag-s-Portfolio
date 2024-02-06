
//SREERAG MURALEEDHARAN


// Text textures are draw and initialized here

#include <SDL_ttf.h>
#include "../common.h"
#include "../system.h"
#include "../game.h"

#define FONT_SIZE		  32
#define FONT_TEXTURE_SIZE 512
#define NUM_GLYPHS		  128
#define MAX_WORD_LENGTH	  32
#define MAX_LINE_LENGTH	  1024

extern App app;

static SDL_Color	white = { 255, 255, 255, 255 };
static TTF_Font* font;
static TTF_Font* bigfont;
static TTF_Font* smallfont;
static SDL_Texture* fontTexture;
static SDL_Texture* bigfontTexture;
static SDL_Texture* smallfontTexture;

void initFonts(void)
{
    font = TTF_OpenFont("res/sys/fonts/Crang.ttf", 12);
    bigfont = TTF_OpenFont("res/sys/fonts/TITLEFONT.ttf", 60);
    smallfont = TTF_OpenFont("res/sys/fonts/statsFont.ttf", 20);
}

SDL_Texture* getTextTexture(char* text, int type)
{
    SDL_Surface* surface;
    surface = TTF_RenderUTF8_Blended(font, text, white);
    return toTexture(surface, 1);
}

SDL_Texture* getBigTextTexture(char* text, int type)
{
    SDL_Surface* surface;
    surface = TTF_RenderUTF8_Blended(bigfont, text, white);
    return toTexture(surface, 1);
}

SDL_Texture* getSmallTextTexture(char* text, int type)
{
    SDL_Surface* surface;
    surface = TTF_RenderUTF8_Blended(smallfont, text, white);
    return toTexture(surface, 1);
}

void drawText(char* text, int x, int y, int r, int g, int b)
{
    fontTexture = getTextTexture(text, 1);
    SDL_SetTextureColorMod(fontTexture, r, g, b);
    blit(fontTexture, x, y, 0, SDL_FLIP_NONE);
}

void drawBigText(char* text, int x, int y, int r, int g, int b)
{
    bigfontTexture = getBigTextTexture(text, 1);
    SDL_SetTextureColorMod(bigfontTexture, r, g, b);
    blit(bigfontTexture, x, y, 0, SDL_FLIP_NONE);
}

void drawSmallText(char* text, int x, int y, int r, int g, int b)
{
    smallfontTexture = getSmallTextTexture(text, 1);
    SDL_SetTextureColorMod(smallfontTexture, r, g, b);
    blit(smallfontTexture, x, y, 0, SDL_FLIP_NONE);
}