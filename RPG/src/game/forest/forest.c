

// This is where we'll be creating our forest environment

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App	   app;
extern Forest forest;

static double displayTimer;
static double dTimer;

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

///      <summary>
///      Handles the logic for the forest scene, including entity movements,
///      animations, and input processing.
///      <summary>
static void logic(void);

///      <summary>
///      Draws the forest map ,entities and hub.
///      <summary>
static void draw(void);

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

void initForest(void)
{
	// Setting the display timer to the FPS value.
	displayTimer = FPS ;

	dTimer = FPS + 50;

	// Initialize the step counter.
	steps = 0;

	// Initialize the pause flag to indicate the game is not paused.
	paused = 0;

	memset(&forest, 0, sizeof(forest));

	initMap();
	initHud();
	createForest();
	loadMusic("res/sys/music/forest_music.mp3");
	playMusic(1);

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

void createForest(void)
{
	initEntities();
	initEntity("Player");
	generateMap();
	addItems();
	addMonsters();
	forest.currentEntity = forest.player;
}

static void logic(void)
{
	displayTimer = MAX(displayTimer - app.deltaTime, 0);
	dTimer = MAX(dTimer - app.deltaTime, 0);

	if (displayTimer == 0)
	{
		if (!paused)
		{
			doEntities();
			doHud();

			forest.animationTimer = MAX(forest.animationTimer - app.deltaTime, 0);

			if (forest.animationTimer <= FPS / 5)
			{
				forest.attackingEntity = NULL;

				if (forest.animationTimer == 0)
				{
					if (dTimer == 0)
					{
						if (forest.currentEntity == forest.player)
						{
							doPlayer();
						}
						else
						{
							doMonsters();
						}
					}
				}
			}
			doCamera();
		}

		if (app.keyboard[SDL_SCANCODE_TAB])
		{
			app.keyboard[SDL_SCANCODE_TAB] = 0;
			playSound(SND_BUTTON, 0);
			paused = 1;
			clearInput();
			initStats(NULL);
		}
	}
}

void doCamera(void)
{
	forest.camera.x = forest.player->x - MAP_RENDER_WIDTH / 2;
	forest.camera.y = forest.player->y - MAP_RENDER_HEIGHT / 2;
}

static void draw(void)
{
	if (displayTimer == 0)
	{
		drawMap();
		drawEntities();
		drawHud();
	}
	else if (displayTimer != 0)
	{
		loading();
	}
}

void initForestView(int p)
{  
	if (p == 1)
	{
		
		displayTimer = FPS;
		dTimer = FPS + 60;

		loadMusic("res/sys/music/forest_music.mp3");
		playMusic(1);

		app.delegate.draw = draw;
		app.delegate.logic = logic;

	}
	else if (p == 2)
	{
		app.delegate.draw = &draw;
		app.delegate.logic = &logic;
	}	   
}

