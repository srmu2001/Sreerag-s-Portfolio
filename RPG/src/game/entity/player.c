
//SREERAG MURALEEDHARAN


//  Player is initalized here 

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

#define MOVE_DELAY 7

extern App	   app;
extern Forest forest;
extern Classes c;

static double moveDelay;

void initPlayer(Entity* e)
{
	Monster* m;

	m = malloc(sizeof(Monster));
	memset(m, 0, sizeof(Monster));

	switch (getClasses())
	{
	case WARRIOR:

		setHealth(m, 40);
		setMaxHealth(m, 40);
		setDefense(m, 5);
		setAttack(m, 12);
		setXp(m, 0);
		setRequiredXP(m, 10);
		setLevel(m, 1);

		setName(e, "Player");

		setType(e, ET_PLAYER);
		setSoundEntity(e, SND_WARRIORHIT);
		setEntityTexture(e, "res/assets/forest/PlayerWarrior.png");
		setEntityBigTexture(e, "res/assets/PlayerWarrior/3.png");
		setMonsterData(e, m);
		setSolid(e, 1);

		loadAnimation("res/assets/PlayerWarrior", e, 0, 0, 4);
		loadAnimation("res/assets/Animation/swipe", e, 1, 0, 4);
		loadAnimation("res/assets/Animation/heal", e, 2, 0, 4);

		break;

	case MAGE:

		setHealth(m, 25);
		setMaxHealth(m, 25);
		setDefense(m, 3);
		setAttack(m, 16);
		setXp(m, 0);
		setRequiredXP(m, 10);
		setLevel(m, 1);

		setName(e, "Player");

		setSoundEntity(e, SND_MAGEHIT);
		setType(e, ET_PLAYER);
		setEntityTexture(e, "res/assets/forest/PlayerMage.png");
		setEntityBigTexture(e, "res/assets/PlayerMage/3.png");
		setMonsterData(e, m);
		setSolid(e, 1);

		loadAnimation("res/assets/PlayerMage", e, 0, 0, 4);
		loadAnimation("res/assets/Animation/explosion", e, 1, 0, 4);
		loadAnimation("res/assets/Animation/heal", e, 2, 0, 4);

		break;

	default:
		break;
	}

	forest.player = e;
	moveDelay = 0;
}

void doPlayer(void)
{
	int dx, dy;

	// Reduce moveDelay based on deltaTime.
	moveDelay = MAX(0, moveDelay - app.deltaTime);

	if (moveDelay == 0)
	{
		dx = dy = 0;

		if (app.keyboard[SDL_SCANCODE_W])
		{
			dy = -1;
			steps += 1;
		}
		if (app.keyboard[SDL_SCANCODE_S])
		{
			dy = 1;
			steps += 1;
		}
		if (app.keyboard[SDL_SCANCODE_A])
		{
			dx = -1;
			steps += 1;
		}
		if (app.keyboard[SDL_SCANCODE_D])
		{
			dx = 1;
			steps += 1;
		}
		if (app.keyboard[SDL_SCANCODE_ESCAPE])
		{
			initTitle();
		}

		// If there is movement input, update the player's position and reset the moveDelay.
		if (dx != 0 || dy != 0)
		{
			moveEntity(forest.player, dx, dy);

			moveDelay = MOVE_DELAY;

			// Advance to the next monster
			nextMonster();
		}
	}
}

void addPlayerXP(int amount)
{
	Monster* m = getMonsterData(forest.player);
	int oldLevel, lvl;
	char text[MAX_DESCRIPTION_LENGTH];

	// Store the player's current level.
	oldLevel = getLevel(m);

	// Add experience points and check for level-up.
	setXp(m, getXp(m) + amount);

	do
	{
		setLevel(m, getLevel(m) + 1);
		setRequiredXP(m, getRequiredXP(m) + 5);

	} while (getXp(m) >= getRequiredXP(m));

	lvl = getLevel(m);

	// Update level and increase stats if leveled up
	if (getLevel(m) > oldLevel)
	{
		setXp(m, getXp(m) - getXp(m));
		setMaxHealth(m, getMaxHealth(m) + 5);
		setHealth(m, getMaxHealth(m));
		setDefense(m, getDefense(m) + 1);
		setAttack(m, getAttack(m) + 5);

		sprintf(text, "You are now level #%d! Your stats have increased!", getLevel(m));
		playSound(SND_LVLUP, 0);
		addHudMessage(HUD_MSG_GOOD, text);
	}
}

//*********************      SETTERS      ************************

void setClasses(int classes)
{
	c.classes = classes;
}

int getClasses(void)
{
	return c.classes;
}
	
void setName(Entity* e, char* name)
{
	STRCPY(e->name, name);
}

void setEntityTexture(Entity* e, char* texturePath)
{
	e->texture = loadTexture(texturePath);
}

void setEntityBigTexture(Entity* e, char* bigTexturePath)
{
	e->bigTexture = loadTexture(bigTexturePath);
}

void setType(Entity* e, int type)
{
	e->type = type;
}

void setSoundEntity(Entity* e, int sound)
{
	e->sound = sound;
}

void setSolid(Entity* e, int solid)
{
	e->solid = solid;
}
void setMonsterData(Entity* e, Monster* m)
{
	e->data = m;
}

void setDead(Entity* e, int dead)
{
	e->dead = 1;
}
void setFacing(Entity* e, int facing)
{
	e->facing;
}

void setItemData(Entity* e, Item* i)
{
	e->data = i;
}

//*********************      GETTERS      ************************

char* getName(Entity* e)
{
	return e->name;
}

Texture* getEntityTexture(Entity* e)
{
	return e->texture;
}

Texture* getEntityBigTexture(Entity* e)
{
	return e->bigTexture;
}

int getType(Entity* e)
{
	return e->type;
}

int getSoundEntity(Entity* e)
{
	return e->sound;
}

int getSolid(Entity* e)
{
	return	e->solid;
}

Monster* getMonsterData(Entity* e)
{
	return (Monster*)e->data;
}
int getDead(Entity* e)
{
	return e->dead;
}

Item* getItemData(Entity* e)
{
	return (Item*)e->data;
}