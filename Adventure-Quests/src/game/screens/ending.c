
//SREERAG MURALEEDHARAN


// This is where we'll be doing our END screen

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App	app;

static int type;
static int fadeTimer;
static Texture* backgroundEND;

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

///      <summary>
///      Logic function for the ending screen
///      </summary>
static void logic(void);

///      <summary>
///      Draw function for the ending screen
///      <summary>
static void draw(void);

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

void initEnding(int outcome)
{
    fadeTimer = 0;

    // Load background image and set initial alpha
    if (outcome == 1)
    {
        backgroundEND = loadTexture("res/assets/forest/Win.png");
        SDL_SetTextureAlphaMod(backgroundEND, 0);
        loadMusic("res/sys/music/victory_music.mp3");
        playMusic(1);
    }
    else if (outcome == 2)
    {
        backgroundEND = loadTexture("res/assets/forest/Lose.png");
        SDL_SetTextureAlphaMod(backgroundEND, 0);
        loadMusic("res/sys/music/endscreen_music.mp3");
        playMusic(1);
    }


    app.delegate.logic = logic;
    app.delegate.draw = draw;
}

static void logic(void)
{
    // Check for space key to return to the title screen
    if (app.keyboard[SDL_SCANCODE_SPACE])
    {
        app.keyboard[SDL_SCANCODE_SPACE] = 0;
        clearInput();
        initTitle();
        playSound(SND_BUTTON, 0);
    }

    // Check for escape key to quit the game
    if (app.keyboard[SDL_SCANCODE_ESCAPE])
    {
        app.keyboard[SDL_SCANCODE_ESCAPE] = 0;
        clearInput();
        SDL_Quit();
        playSound(SND_BUTTON, 0);
    }
}

static void draw(void)
{
    // Apply fade-in effect on the background image
    if (fadeTimer == 0)
    {
        fadeIn(app.renderer, backgroundEND, 60);
        fadeTimer++;
    }
    else
    {
        // Draw the background image after fade-in
        blit(backgroundEND, 0, 0, 0, SDL_FLIP_NONE);
    }
}


