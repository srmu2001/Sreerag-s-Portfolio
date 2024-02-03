
// Here we produce our entities as we load them

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern Forest forest;

static InitFunc head, *tail;

void initEntityFactory(void)
{
	// Setting initFunc linked list
	memset(&head, 0, sizeof(InitFunc));
	tail = &head;

	// We call addInitFunc passing in entity name and it's initialization, to setup init function
	addInitFunc("Player", initPlayer);
	addInitFunc("Orc", initOrc);
	addInitFunc("Health Pack", initHealthPack);
	addInitFunc("Armor", initArmor);
	addInitFunc("Weapon", initWeapon);
	addInitFunc("Orc King", initOrcKing);

}

Entity *initEntity(char *name)
{

	Entity *e;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Creating entity '%s'", name);

	e = spawnEntity();

	// To look for an initFunc with a name matching the one we passed into the function
	getInitFunc(name)->init(e);

	return e;

}

Entity *spawnEntity(void)
{

	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));

	forest.entityTail->next = e;
	forest.entityTail = e;
	return e;

}

void addInitFunc(char *name, void (*init)(Entity *e))
{

	InitFunc *i;

	i = malloc(sizeof(InitFunc));
	memset(i, 0, sizeof(InitFunc));

	tail->next = i;
	tail = i;

	//Copying the entity type name to the InitFunc structure.
	STRCPY(i->name, name);

	// Sets the entity initialization function in the InitFunc structure.
	i->init = init;

}

InitFunc *getInitFunc(char *name)
{

	InitFunc *i;

	for (i = head.next; i != NULL; i = i->next)
	{
		// Checks if the entity type name matches
		if (strcmp(i->name, name) == 0)
		{
			return i;
		}
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Unknown entity '%s'", name);
	exit(1);

	return NULL;

}
