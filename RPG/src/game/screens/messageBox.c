
//SREERAG MURALEEDHARAN


// messageBox is drawn and initialized here

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App	   app;
extern Forest forest;

static Texture* monsterKing;

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

//Handles game logic for the messageBox.
static void logic(void);

// Draws the messageBox
static void draw(void);

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

void initMessageBox(void)
{
    monsterKing = loadTexture("res/assets/forest/messageBoxORC.png");

    app.delegate.logic = logic;
    app.delegate.draw = draw;
}

static void logic(void)
{
    if (app.keyboard[SDL_SCANCODE_SPACE])
    {
        app.keyboard[SDL_SCANCODE_SPACE] = 0;

        clearInput();

        initForestView(2);
    }
}

static void draw(void)
{
    char text[200];

    drawMap();
    drawEntities();

    drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 130);

    drawRect(0, 500, 1280, 250, 0, 0, 0, 160);
    drawOutlineRect(0, 500, 1280, 250, 255, 255, 255, 150);

    drawRect(250, 470, 200, 65, 0, 0, 0, 255);
    drawOutlineRect(250, 470, 200, 65, 255, 255, 255, 255);

    blit(monsterKing, 0, 400, 0, SDL_FLIP_NONE);

    sprintf(text, "ORC - KING");
    drawSmallText(text, 300, 490, 255, 64, 64);

    sprintf(text, "YOU  ARE  SO  WEAK  TO  FACE  ME  !!!");
    drawSmallText(text, 300, 560, 255, 64, 64);

    sprintf(text, "(  LEVEL  6  REQUIRED  TO  FACE  ORC  -  BOSS  )");
    drawSmallText(text, 300, 595, 255, 255, 255);
}
