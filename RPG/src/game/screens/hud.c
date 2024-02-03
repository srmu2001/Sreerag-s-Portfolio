
//SREERAG MURALEEDHARAN


//  This is where the HUD display initializes and displays

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App	   app;
extern Forest forest;
extern Game	   game;
extern Monster* player, * enemy;

static double infoMessageTimer;

void initHud(void)
{
    infoMessageTimer = 0;
}

void doHud(void)
{
    infoMessageTimer = MAX(infoMessageTimer - app.deltaTime, 0);
}

void addHudMessage(int type, char* text)
{
    int i;

    infoMessageTimer = FPS * 4.5;

    for (i = NUM_HUD_MESSAGES - 1; i > 0; i--)
    {
        memcpy(&game.messages[i], &game.messages[i - 1], sizeof(HudMessage));
    }

    game.messages[0].type = type;
    STRCPY(game.messages[0].text, text);
}

void drawHud(void)
{
    drawMessages();
}

void drawMessages(void)
{
    int i, y;
    SDL_Color c;

    y = SCREEN_HEIGHT - 35;

    // Set the color based on the type of the message
    for (i = 0; i < NUM_HUD_MESSAGES; i++)
    {
        switch (game.messages[i].type)
        {
        case HUD_MSG_GOOD:
            c.r = 40;
            c.g = 200;
            c.b = 255;
            break;

        case HUD_MSG_BAD:
            c.r = 255;
            c.g = c.b = 64;
            break;

        case HUD_MSG_GREEN:
            c.r = 170;
            c.g = 255;
            c.b = 0;
            break;

        default:
            c.r = c.g = c.b = 255;
            break;
        }
        if (infoMessageTimer > 0)
        {
            drawText(game.messages[i].text, 10, y, c.r, c.g, c.b);
            y -= 30;
        }
    }
}

void drawTopBar()
{
    char text[200];
    double healthPercent;
    double healthPercent2;

    healthPercent = (1.0 * getHealth(player)) / getMaxHealth(player);

    healthPercent2 = (1.0 * getHealth(enemy) / getMaxHealth(enemy));

    sprintf(text, "PLAYER   :");
    drawText(text, 225, 350, 170, 255, 0);

    sprintf(text, "  %d / %d", getHealth(player), getMaxHealth(player));

    if (healthPercent <= 0.2)
    {
        drawText(text, 300, 350, 255, 64, 64);
    }
    else if (healthPercent <= 0.5)
    {
        drawText(text, 300, 350, 255, 255, 0);
    }
    else
    {
        drawText(text, 300, 350, 255, 255, 255);
    }

    if (getType(enemy) == ET_MONSTERKING)
    {
        sprintf(text, "ORC  KING  :");
        drawText(text, 1000, 350, 255, 64, 64);
    }
    else
    {
        sprintf(text, "ORC        :");
        drawText(text, 1000, 350, 255, 64, 64);
    }

    sprintf(text, " %d / %d", getHealth(enemy), getMaxHealth(enemy));

    if (healthPercent2 <= 0.2)
    {
        drawText(text, 1070, 350, 255, 64, 64);
    }
    else if (healthPercent2 <= 0.5)
    {
        drawText(text, 1070, 350, 255, 255, 0);
    }
    else
    {
        drawText(text, 1070, 350, 255, 255, 255);
    }
}




