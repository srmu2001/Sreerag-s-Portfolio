
//SREERAG MURALEEDHARAN


// This is where items are initialized

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern Forest forest;

void addItems(void)
{
	int i, j, k;

	// Add Health Packs
	for (i = 0; i < 5; i++)
	{
		addEntityToForest(initEntity("Health Pack"));
	}

	// Add Armor (only 1)
	for (j = 0; j < 1; j++)
	{
		addEntityToForest(initEntity("Armor"));
	}

	// Add Weapons (only 1)
	for (k = 0; k < 1; k++)
	{
		addEntityToForest(initEntity("Weapon"));
	}
}

Item* createItem(Entity* e)
{
	Item* i;

	i = malloc(sizeof(Item));
	memset(i, 0, sizeof(Item));

	setType(e, ET_ITEM);
	setItemData(e, i);

	return i;
}

void initHealthPack(Entity* e)
{
	Item* i;

	i = createItem(e);
	e->touch = touchPot;
	setHpPot(i, 1);

	setName(e, "Health Pack");
	setEntityTexture(e, "res/assets/forest/HpPot.png");
}

void initArmor(Entity* e)
{
	Item* i;

	i = createItem(e);
	e->touch = touchArmor;
	i->armor = 1;

	setName(e, "Armor");

	// Change armor textures based on the selected class
	if (getClasses() == WARRIOR)
	{
		setEntityTexture(e, "res/assets/forest/WarriorArmor.png");
	}
	else if (getClasses() == MAGE)
	{
		setEntityTexture(e, "res/assets/forest/MageArmor.png");
	}
}

void initWeapon(Entity* e)
{
	Item* i;

	i = createItem(e);
	e->touch = touchWeapon;
	i->weapon = 1;

	setName(e, "Weapon");

	// Change weapon textures based on the selected class
	if (getClasses() == WARRIOR)
	{
		setEntityTexture(e, "res/assets/forest/WarriorWeapon.png");
	}
	else if (getClasses() == MAGE)
	{
		setEntityTexture(e, "res/assets/forest/MageWeapon.png");
	}
}

void touchPot(Entity* self, Entity* other)
{
	Monster* m;
	Item* i;

	char text[MAX_DESCRIPTION_LENGTH];

	if (other == forest.player)
	{
		m = getMonsterData(other);
		i = getItemData(self);

		setPlayerPots(m, getPlayerPots(m) + getHpPot(i));

		destroyItem(self);
	}
}

void touchArmor(Entity* self, Entity* other)
{
	Monster* m;
	char text[MAX_DESCRIPTION_LENGTH];

	if (other == forest.player)
	{
		m = getMonsterData(other);

		setDefense(m, getDefense(m) + 5);

		destroyItem(self);
	}
}

void touchWeapon(Entity* self, Entity* other)
{
	Monster* m;

	if (other == forest.player)
	{
		m = getMonsterData(other);

		setAttack(m, getAttack(m) + 5);

		destroyItem(self);
	}
}

void destroyItem(Entity* self)
{
	char text[MAX_DESCRIPTION_LENGTH];
	sprintf(text, "Picked up a %s.", getName(self));
	addHudMessage(HUD_MSG_GREEN, text);

	removeEntityFromForest(self);

	playSound(SND_ITEM, 0);
}

//*********************      SETTERS      ************************

void setHpPot(Item* i, int HpPot)
{
	i->hppot = HpPot;
}

//*********************      GETTERS      ************************

int getHpPot(Item* i)
{
	return i->hppot;
}

