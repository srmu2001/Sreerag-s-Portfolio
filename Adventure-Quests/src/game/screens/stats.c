
//SREERAG MURALEEDHARAN



//  Stats are drawn here

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App	   app;
extern Forest forest;

static Entity* e;
static Monster* m1, * m2;
static Texture* l1;
static Texture* playerChar;
static Texture* enemyChar;
static Texture* statsChar;

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

//     Initializes the combat logic 
static void logic(void);

//     Draws the stats of player and enemy(depends on the fight Scene environment)
static void draw(void);

//     handles the rendering of player and enemy statistics on the screen.
//     The function utilizes the SDL graphics library to draw various text elements,
//     such as player health, attack, defense, level, experience points, and health potions.
static void drawStats(void);

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

void initStats(Entity* enemy)
{
    e = enemy;
    m1 = getMonsterData(forest.player);

    if (enemy != NULL)
    {
        enemyChar = getEntityBigTexture(enemy);
        m2 = getMonsterData(enemy);
    }

    playerChar = getEntityBigTexture(forest.player);
    statsChar = loadTexture("res/assets/forest/statesImage.png");

    app.delegate.logic = logic;
    app.delegate.draw = draw;
}

static void logic(void)
{
    if (e != NULL)
    {
        if (app.keyboard[SDL_SCANCODE_TAB])
        {
            app.keyboard[SDL_SCANCODE_TAB] = 0;
            playSound(SND_BUTTON, 0);
            clearInput();
            initFightSceneView();
        }
    }
    else
    {
        if (app.keyboard[SDL_SCANCODE_TAB])
        {
            app.keyboard[SDL_SCANCODE_TAB] = 0;
            playSound(SND_BUTTON, 0);
            clearInput();
            SDL_RenderClear(app.renderer);
            initForestView(2);
            paused = 0;
        }
    }
}

static void draw(void)
{
    if (e != NULL)
    {
        drawMe();

        drawRect(100, 100, 1110, 500, 0, 0, 0, 240);

        drawOutlineRect(100, 100, 1110, 500, 255, 255, 255, 255);

        blit(playerChar, 150, 320, 0, SDL_FLIP_NONE);

        blit(enemyChar, 1060, 335, 0, SDL_FLIP_NONE);
    }
    else
    {
        drawMap();

        drawEntities();

        drawRect(300, 100, 700, 500, 0, 0, 0, 240);

        drawOutlineRect(300, 100, 700, 500, 255, 255, 255, 255);

        blit(playerChar, 400, 320, 0, SDL_FLIP_NONE);
    }

    drawStats();
}

static void drawStats(void)
{
	
	char	   text[MAX_DESCRIPTION_LENGTH];

	sprintf(text, "STATS");
	drawBigText(text, 580, 150, 255, 255, 255);
	
	if (e != NULL)
	{
		sprintf(text, "PLAYER HP :  %d / %d", getHealth(m1), getMaxHealth(m1));
		drawSmallText(text, 315, 300, 170, 255, 0);

		sprintf(text, "ATTACK :  %d", getAttack(m1));
		drawSmallText(text, 315, 335, 170, 255, 0);

		sprintf(text, "DEFENSE :  %d", getDefense(m1));
		drawSmallText(text, 315, 370, 170, 255, 0);

		sprintf(text, "LEVEL :  %d", getLevel(m1));
		drawSmallText(text, 315, 405, 170, 255, 0);

		sprintf(text, "XP :  %d / %d", getXp(m1), getRequiredXP(m1));
		drawSmallText(text, 315, 440, 170, 255, 0);

		sprintf(text, "HP POT:  %d", getPlayerPots(m1));
		drawSmallText(text, 315, 475, 170, 255, 0);

		sprintf(text, "ORC  HP :  %d / %d", getHealth(m2), getMaxHealth(m2));
		drawSmallText(text, 825, 300, 255, 64, 64);

		sprintf(text, "ORC ATTACK :  %d", getAttack(m2));
		drawSmallText(text, 825, 335, 255, 64, 64);

		sprintf(text, "ORC DEFENSE :  %d", getDefense(m2));
		drawSmallText(text, 825, 370, 255, 64, 64);
	}
	else
	{
		sprintf(text, "PLAYER HP :  %d / %d", getHealth(m1), getMaxHealth(m1));
		drawSmallText(text, 590, 300, 170, 255, 0);

		sprintf(text, "ATTACK :  %d", getAttack(m1));
		drawSmallText(text, 590, 335, 170, 255, 0);

		sprintf(text, "DEFENSE :  %d", getDefense(m1));
		drawSmallText(text, 590, 370, 170, 255, 0);

		sprintf(text, "LEVEL :  %d", getLevel(m1));
		drawSmallText(text, 590, 405, 170, 255, 0);

		sprintf(text, "XP :  %d / %d", getXp(m1), getRequiredXP(m1));
		drawSmallText(text, 590, 440, 170, 255, 0);

		sprintf(text, "HP POT:  %d", getPlayerPots(m1));
		drawSmallText(text, 590, 475, 170, 255, 0);
	}

}



