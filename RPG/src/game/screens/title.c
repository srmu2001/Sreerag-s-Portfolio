
// Title Screen is setup here

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

Classes c;

extern App app;
extern Forest forest;

static Texture* background;
static Texture* playerWarrior;
static Texture* playerMage;
static Texture* titleLogo;

static int fadeTimer;
static double displayTimer;

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

/// <summary>
/// Initializing Music for Title Screen
/// </summary>
static void initTitleMusic();

/// <summary>
/// Initializing Textures for Title Screen
/// </summary>
static void initTitleScreen();

//  Initializes the combat logic
static void logic(void);

//   Draws the main title screen with class selection and game start prompt.
//   Fades in the background and displays character images, class selection UI, and instructions.
//   Also handles class stats display.
static void draw(void);

// Draws stats based on the Class the user chooses
static void showstats();

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

void initTitle(void)
{
	displayTimer = FPS + 15;
	fadeTimer = 0;

	initTitleScreen();
	initTitleMusic();

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void initTitleScreen()
{
	background = loadTexture("res/assets/forest/background2.jpg");

	playerWarrior = loadTexture("res/assets/PlayerWarrior/3.png");

	playerMage = loadTexture("res/assets/PlayerMage/3.png");

	titleLogo = loadTexture("res/assets/forest/Title.png");

	SDL_SetTextureAlphaMod(background, 0);
}

static void initTitleMusic()
{
	loadMusic("res/sys/music/titlescreen_music.mp3");

	playMusic(1);
}

static void logic(void)
{
	displayTimer = MAX(displayTimer - app.deltaTime, 0);

	if (displayTimer == 0)
	{
		if (app.keyboard[SDL_SCANCODE_SPACE])
		{
			app.keyboard[SDL_SCANCODE_SPACE] = 0;

			clearInput();

			if (getClasses() == WARRIOR || getClasses() == MAGE)
			{
				playSound(SND_BUTTON, 0);
				clearInput();
				initForest();
			}
			else
			{
				playSound(SND_ERROR, 0);
			}
		}

		if (app.keyboard[SDL_SCANCODE_Z])
		{
			app.keyboard[SDL_SCANCODE_Z] = 0;
			clearInput();

			setClasses(WARRIOR);
			playSound(SND_BUTTON, 0);
		}
		else if (app.keyboard[SDL_SCANCODE_X])
		{
			app.keyboard[SDL_SCANCODE_X] = 0;

			clearInput();
			setClasses(MAGE);
			playSound(SND_BUTTON, 0);
		}
	}
}

static void draw(void)
{
	char text[200];

	if (fadeTimer == 0)
	{
		fadeIn(app.renderer, background, 50);
		fadeTimer++;
	}
	else
	{
		SDL_Delay(100);

		blit(background, 0, 0, 0, SDL_FLIP_NONE);
		blit(playerWarrior, 150, 290, 0, SDL_FLIP_NONE);
		blit(playerMage, 1100, 290, 0, SDL_FLIP_HORIZONTAL);

		drawRect(255, 55, 725, 95, 0, 0, 0, 160);
		drawOutlineRect(255, 55, 725, 95, 255, 255, 255, 255);

		blit(titleLogo, 260, 60, 0, SDL_FLIP_NONE);

		drawRect(480, 280, 320, 150, 0, 0, 0, 160);
		drawOutlineRect(480, 280, 320, 150, 255, 255, 255, 255);

		sprintf(text, "PRESS SPACE TO START");
		drawSmallText(text, 550, 300, 255, 255, 255);

		sprintf(text, "CLASSES");
		drawSmallText(text, 600, 347, 255, 255, 255);

		sprintf(text, "(PRESS  Z / X  TO SELECT A CLASS)");
		drawSmallText(text, 500, 365, 255, 255, 255);

		if (getClasses() == WARRIOR || getClasses() == MAGE)
		{
			showstats();
		}
	}
}

static void showstats()
{
	char text[200];

	if (getClasses() == WARRIOR)
	{
		drawRect(90, 440, 200, 200, 0, 0, 0, 160);
		drawOutlineRect(90, 280, 200, 360, 255, 255, 255, 255);

		sprintf(text, "CLASS  :  WARRIOR");
		drawSmallText(text, 110, 460, 8, 143, 143);

		sprintf(text, "HP  :  40");
		drawSmallText(text, 110, 495, 8, 143, 143);

		sprintf(text, "ATTACK  :  12");
		drawSmallText(text, 110, 530, 8, 143, 143);

		sprintf(text, "DEFENSE  :  7");
		drawSmallText(text, 110, 565, 8, 143, 143);
	}
	else if (getClasses() == MAGE)
	{
		drawRect(1050, 440, 190, 200, 0, 0, 0, 160);
		drawOutlineRect(1050, 280, 190, 360, 255, 255, 255, 255);

		sprintf(text, "CLASS : MAGE");
		drawSmallText(text, 1070, 460, 8, 143, 143);

		sprintf(text, "HP : 25");
		drawSmallText(text, 1070, 495, 8, 143, 143);

		sprintf(text, "ATTACK : 16");
		drawSmallText(text, 1070, 530, 8, 143, 143);

		sprintf(text, "DEFENSE : 5");
		drawSmallText(text, 1070, 565, 8, 143, 143);
	}
}

