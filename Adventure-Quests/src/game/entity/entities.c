
//SREERAG MURALEEDHARAN


// This is where we'll be doing our entity's initialization, logic and drawings

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

#define MAX_ENTS_TO_DRAW 128

extern App app;
extern Forest forest;

static Entity* entsToDraw[MAX_ENTS_TO_DRAW];

void initEntities(void)
{
	forest.entityTail = &forest.entityHead;
	forest.deadTail = &forest.deadHead;

}

void doEntities(void)
{
    Entity* e, * prev;
    int i;

    i = 0;
    memset(entsToDraw, 0, sizeof(Entity*) * MAX_ENTS_TO_DRAW);

    prev = &forest.entityHead;

    for (e = forest.entityHead.next; e != NULL; e = e->next)
    {
        if (!getDead(e))
        {
            if (i < MAX_ENTS_TO_DRAW)
            {
                // Add the entity to the array of entities to draw
                entsToDraw[i++] = e;
            }
        }
        else
        {
            // Remove the dead entity from the linked list.
            prev->next = e->next;

            if (e == forest.entityTail)
            {
                forest.entityTail = prev;
            }

            e->next = NULL;
            forest.deadTail->next = e;
            forest.deadTail = e;
            e = prev;
        }

        prev = e;
    }

    // Sort the array of entities to draw based on comparator function.
    qsort(entsToDraw, i, sizeof(Entity*), drawComparator);
}

void moveEntity(Entity* e, int dx, int dy)
{
    int x, y;

    // Calculate the new x and y coordinates for the entity.
    x = e->x + dx;
    y = e->y + dy;

    if (e == forest.player)
    {
        playSound(SND_WALK, 0);
    }

    if (getType(e) != ET_MONSTERKING)
    {
        if (dx < 0)
        {
            setFacing(e, FACING_LEFT);
        }
        else if (dx > 0)
        {
            setFacing(e, FACING_RIGHT);
        }

        // Check if the new position is within the valid map bounds, on the ground, not blocked by an obstacle.
        if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT && forest.map[x][y].tile >= TILE_GROUND && forest.map[x][y].tile < TILE_WALL && !isBlocked(e, x, y))
        {
            // Update the entity's position.
            e->x = x;
            e->y = y;
        }
    }
}

int isBlocked(Entity* e, int x, int y)
{
    Entity* other;
    Monster* k;

    k = getMonsterData(e);

    for (other = forest.entityHead.next; other != NULL; other = other->next)
    {
        // Check if the current entity is at the specified position.
        if (other->x == x && other->y == y)
        {
            switch (getType(other))
            {
            case ET_PLAYER:
                if (getType(e) != getType(other))
                {
                    initFight(e, other);
                }
                return 1;

            case ET_MONSTER:
                if (getType(e) != getType(other))
                {
                    initFight(other, e);
                }
                return 1;

            case ET_MONSTERKING:
                if (getType(e) != getType(other))
                {
                    if (getType(other) == ET_MONSTERKING)
                    {
                        if (k->level < 6)
                        {
                            initMessageBox();
                        }
                        else
                        {
                            initFight(other, e);
                        }
                    }
                }
                return 1;

            case ET_ITEM:
                other->touch(other, e);
                break;

            default:
                break;
            }
        }
    }
    return 0;
}

void addEntityToForest(Entity* e)
{
    int x, y, ok;

    if (e->type == ET_MONSTERKING)
    {
        x = 29;
        y = 30;
    }
    else
    {
        do
        {
            x = 1 + rand() % (MAP_WIDTH - 2);
            y = 1 + rand() % (MAP_HEIGHT - 2);
            ok = forest.map[x][y].tile > TILE_HOLE && forest.map[x][y].tile < TILE_WALL && !isOccupied(x, y);
        } while (!ok);
    }

    e->x = x;
    e->y = y;
}

void removeEntityFromForest(Entity* e)
{
    Entity* other, * prev;

    prev = &forest.entityHead;

    for (other = forest.entityHead.next; other != NULL; other = other->next)
    {
        if (other == e)
        {
            prev->next = other->next;

            if (other == forest.entityTail)
            {
                forest.entityTail = prev;
            }

            other->next = NULL;
        }
        prev = other;
    }
}

int isOccupied(int x, int y)
{
    Entity* e;

    for (e = forest.entityHead.next; e != NULL; e = e->next)
    {
        if (e->x == x && e->y == y)
        {
            return 1;
        }
    }
    return 0;
}

Entity* getEntityAt(int x, int y)
{
    Entity* e, * rtn;

    rtn = NULL;

    for (e = forest.entityHead.next; e != NULL; e = e->next)
    {
        if (e->x == x && e->y == y)
        {
            if (getSolid(e))
            {
                return e;
            }
            rtn = e;
        }
    }

    return rtn;
}

void drawEntities(void)
{
    Entity* e;
    int i;

    for (i = 0, e = entsToDraw[0]; i < MAX_ENTS_TO_DRAW && e != NULL; e = entsToDraw[++i])
    {
        drawEntity(e);
    }
}

void drawEntity(Entity* e)
{
    int x, y;

    x = (e->x - forest.camera.x);
    y = (e->y - forest.camera.y);

    if (x >= 0 && y >= 0 && x < MAP_RENDER_WIDTH && y < MAP_RENDER_HEIGHT)
    {
        x *= MAP_TILE_SIZE;
        y *= MAP_TILE_SIZE;

        blit(e->texture, x + MAP_RENDER_X, y + MAP_RENDER_Y, 0, e->facing == FACING_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    }
}

int drawComparator(const void* a, const void* b)
{
    Entity* e1, * e2;

    // Extract the actual entity pointers from the provided pointers.
    e1 = *((Entity**)a);
    e2 = *((Entity**)b);

    if (e1 == forest.attackingEntity || e2 == forest.attackingEntity)
    {
        return e1 == forest.attackingEntity ? 1 : -1;
    }
    // Compare entities based on their types, determining the drawing order.
    return getType(e2) - getType(e1);
}