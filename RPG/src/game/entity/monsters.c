
//SREERAG MURALEEDHARAN


//  Monsters and their AI is initalized and stepup here

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern Forest forest;

void doMonsters(void)
{

	int analizing;

	analizing = 1;
	
	do
	{
		// The enemy AI starts working after the player takes 10 steps
		if (steps > 10)
		{
			think(forest.currentEntity);
		}
			nextMonster();

			// Iterates through monster entities until it reaches player entity
			analizing = forest.animationTimer == 0 && forest.currentEntity != forest.player;

	} while (analizing);

}

void nextMonster(void)
{

	int found;
	Entity *e;

	e = forest.currentEntity;

	do
	{
		e = e->next;

		if (e == NULL)
		{
			e = forest.entityHead.next;
		}

		// Check if the entity is active (not dead) and specified type.
		found = !e->dead && (e->type == ET_MONSTER || e->type == ET_MONSTERKING || e->type == ET_PLAYER );
	} while (!found);

	// Update the forest's current entity with the found active entity.
	forest.currentEntity = e;

}

void think(Entity *e)
{

	Monster *m;

	m = (Monster *)e->data;
	
	// Decision-making based on the monster's state.
	if (!m->alert)
	{
		// Decision-making based on the monster's state.
		lookForPlayer(e, m);
	}
	    else if (hasLOS(e, forest.player->x, forest.player->y))
		{
		    // If alerted and has line of sight to the player, move toward the player.
			moveToPlayer(e, m);
		}
	        else if (m->alert)
			{
		        // If alerted but no line of sight to the player, patrol the assigned area.
				patrol(e, m);
			}
		
}

 void lookForPlayer(Entity *e, Monster *m)

{
	
	m->alert = getDistance(e->x, e->y, forest.player->x, forest.player->y) <= getVisRange(m) && hasLOS(e, forest.player->x, forest.player->y);
	
	if (getDistance(e->x, e->y, forest.player->x, forest.player->y) >= getVisRange(m) && hasLOS(e, forest.player->x, forest.player->y))
	{
		m->alert -= m->alert;// Player is out of visibility range; reduce alertness.
	}
	    else if (getDistance(e->x, e->y, forest.player->x, forest.player->y) <= getVisRange(m) && hasLOS(e, forest.player->x, forest.player->y))
		{
			m->alert += 1;// Player is within visibility range; increase alertness.
		}

}

void moveToPlayer(Entity *e, Monster *m)
{

	int dx, dy;

	createAStarRoute(e, forest.player->x, forest.player->y, &dx, &dy);

	moveEntity(e, dx, dy);


	// Update patrol destination to the player's current position.
	m->patrolDest.x = forest.player->x;
	m->patrolDest.y = forest.player->y;
	
}
void patrol(Entity *e, Monster *m)
{
	
	int		dx, dy;
	Entity* other;


	// Check if the patrol destination tile is on the ground and not a wall.
	if (forest.map[m->patrolDest.x][m->patrolDest.y].tile == TILE_GROUND && forest.map[m->patrolDest.x][m->patrolDest.y].tile < TILE_WALL)
	{
		// Get the entity at the patrol destination.
		other = getEntityAt(m->patrolDest.x, m->patrolDest.y);
	
		// Check if the destination is empty or not solid.
		if (other == NULL || other == forest.player || !other->solid)
		{
			// Calculate A* path to the patrol destination and move the monster.
			createAStarRoute(e, m->patrolDest.x, m->patrolDest.y, &dx, &dy);

			moveEntity(e, dx, dy);

			// Check if the monster reached the patrol destination.
			if (e->x == m->patrolDest.x && e->y == m->patrolDest.y)
			{	
				// Randomly select a new destination for patrolling.
				m->patrolDest.x = rand() % MAP_WIDTH;
				m->patrolDest.y = rand() % MAP_HEIGHT;

				// Calculate A* path to the new patrol destination and move the monster.
				createAStarRoute(e, m->patrolDest.x, m->patrolDest.y, &dx, &dy);
				moveEntity(e, dx, dy);

			}
		}
	}
	// If the patrol destination is invalid, randomly select a new destination and move the monster. 
		m->patrolDest.x = rand() % MAP_WIDTH;
		m->patrolDest.y = rand() % MAP_HEIGHT;

		moveEntity(e, &dx, &dy);

}

void addMonsters(void)
{

	int i;

	for (i = 0; i < 5; i++)
	{
		addEntityToForest(initEntity("Orc"));
	}

	addEntityToForest(initEntity("Orc King"));

}

Monster *createMonster(Entity *e)
{

	Monster *m;

	m = malloc(sizeof(Monster));
	memset(m, 0, sizeof(Monster));

	//e->solid = 1;
	setSolid(e, 1);
	setMonsterData(e, m);
	//e->data = m;

	return m;

}


void initOrc(Entity *e)
{
	Monster *m;

	m = createMonster(e);

	setHealth(m, 40);
	setMaxHealth(m, 40);
	setAttack(m, 15);
	setDefense(m, 2);
	setVisRange(m,1);
	setXp(m, 10);
	setAlert(m, 1);
	
	setName(e, "Orc");

	setEntityTexture(e, "res/assets/forest/Orc.png");
	setEntityBigTexture(e, "res/assets/Orc/3.png");
	setType(e, ET_MONSTER);
	setSoundEntity(e, SND_WARRIORHIT);
	loadAnimation("res/assets/Orc", e, 0, 0, 4 );
	loadAnimation("res/assets/Animation/swipe", e, 1 ,0, 4 );

}

void initOrcKing(Entity* e)
{
	Monster* m;

	m = createMonster(e);


	setHealth(m, 200);
	setMaxHealth(m, 200);
	setAttack(m, 25);
	setDefense(m, 15);
	setVisRange(m, 0);
	setXp(m, 0);

	setName(e, "Orc King");

	setEntityTexture(e, "res/assets/forest/OrcKing.png");
	setEntityBigTexture(e, "res/assets/OrcKing/3.png");
	setType(e, ET_MONSTERKING);
	setSoundEntity(e, SND_MAGEHIT);
	forest.orcKing = e;
	loadAnimation("res/assets/OrcKing", e, 0, 0, 4);
	loadAnimation("res/assets/Animation/explosion", e, 1, 0, 4);
	
}


//*********************      SETTERS      ************************

void setHealth(Monster* m,int hp)
{
	m->hp =  hp;
}

void setMaxHealth(Monster* m, int maxHp)
{
	m->maxHP = maxHp;
}

void setDefense(Monster* m, int defense)
{
	m->defense = defense;
}

void setAttack(Monster* m, int attack)
{
	m->attack = attack;
}

void setVisRange(Monster* m, int visRange)
{
	m->visRange = visRange;
}

void setXp(Monster* m, int xp)
{
	m->xp = xp;
}

void setAlert(Monster* m, int alert)
{
	m->alert = alert;
}

void setRequiredXP(Monster* m, int requiredXP)
{
	m->requiredXP = requiredXP;
}

void setLevel(Monster* m, int level)
{
	m->level = level;
}

void setPlayerPots(Monster* m, int pots)
{
	m->pots = pots;
}

//*********************      GETTERS      ************************

int getHealth(Monster* m)
{
	 return m->hp ;
}

int getMaxHealth(Monster* m)
{
	return m->maxHP;
}

int getDefense(Monster* m)
{
	return m->defense;
}

int getAttack(Monster* m)
{
	return m->attack;
}

int getVisRange(Monster* m)
{
	return m->visRange;
}

int getXp(Monster* m)
{
	return m->xp;
}

int getAlert(Monster* m)
{
	return m->alert;
}

int getPlayerPots(Monster* m)
{
	return m->pots;
}
int getRequiredXP(Monster* m)
{
	return m->requiredXP;
}

int getLevel(Monster* m)
{
	return m->level;
}




