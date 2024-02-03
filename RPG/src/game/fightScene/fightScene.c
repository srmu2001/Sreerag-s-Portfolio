
// This is where the FightScene occurs

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

Monster* player, * enemy;
Entity* Player, * Enemy;

extern App app;
extern Forest forest;
extern FightScene fightscene;

int type;
static int fadeTimer;
static double displayTimer;

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

///      <summary>
///      Initializes the combat logic  
///      </summary>
static void logic(void);

///      <summary>
///      Function to draw background,entities and hud
///      </summary>
static void draw(void);

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

void initFight(Entity* attacker, Entity* target)
{
  
    steps = 0;
	paused = 1;
    fadeTimer = 0;
    displayTimer = FPS  ;

    Player = target;
    Enemy = attacker;
    forest.player = target;
    forest.attackingEntity = attacker;
    player = getMonsterData(target);
    enemy = getMonsterData(attacker);
    
    memset(&fightscene, 0, sizeof(FightScene));
    
    loadMusic("res/sys/music/fightscene_music.mp3");
    playMusic(1);

    fightscene.textbox = loadTexture("res/assets/forest/Main.png");
	fightscene.background = loadTexture("res/assets/forest/Background.jpg");
	
    SDL_SetTextureAlphaMod(fightscene.background, 0);

	app.delegate.logic = logic;
	app.delegate.draw = draw;

}

static void logic(void)
{
    displayTimer = MAX(0, displayTimer - app.deltaTime);

    if (displayTimer == 0)
    {
        if (app.keyboard[SDL_SCANCODE_1])
        {
            app.keyboard[SDL_SCANCODE_1] = 0;
            clearInput();
            playSound(SND_BUTTON, 0);
            playerAttack();
        }
        if (app.keyboard[SDL_SCANCODE_2])
        {
            app.keyboard[SDL_SCANCODE_2] = 0;
            playSound(SND_BUTTON, 0);
            clearInput();
            usingPots();
        }
        if (app.keyboard[SDL_SCANCODE_3])
        {
            app.keyboard[SDL_SCANCODE_3] = 0;
            playSound(SND_BUTTON, 0);
            clearInput();
            runningAway();
        }
        if (app.keyboard[SDL_SCANCODE_4])
        {
            app.keyboard[SDL_SCANCODE_4] = 0;
            playSound(SND_BUTTON, 0);
            SDL_Quit();
        }
        if (app.keyboard[SDL_SCANCODE_TAB])
        {
            app.keyboard[SDL_SCANCODE_TAB] = 0;
            playSound(SND_BUTTON, 0);
            clearInput();
            initStats(forest.attackingEntity);
        }
    }
}

static void draw(void)
{
        if (fadeTimer == 0)
        {
            fadeIn(app.renderer, fightscene.background, 50);
            fadeTimer++;
        }
            else
            {
                drawMe();
            }
}

void drawMe(void)
{
    blit(fightscene.background, 0, 0, 0, SDL_FLIP_NONE);
    blit(fightscene.textbox, 315, 550, 0, SDL_FLIP_NONE);
    blit(getEntityBigTexture(Enemy), 1000, 400, 0, SDL_FLIP_NONE);
    blit(getEntityBigTexture(Player), 225, 400, 0, SDL_FLIP_NONE);
    blit(Enemy->effects[0], 210, 400, 0, SDL_FLIP_NONE);
    blit(Player->effects[0], 1000, 400, 0, SDL_FLIP_HORIZONTAL);
    blit(Player->sEffects[0], 210, 400, 0, SDL_FLIP_NONE);
    drawTopBar();
    drawHud();
}

void initFightSceneView(void)
{
    app.delegate.logic = &logic;
    app.delegate.draw = &draw;
}