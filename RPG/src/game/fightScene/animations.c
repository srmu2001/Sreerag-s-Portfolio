
// This is where we'll be doing our animation for the fightScene

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App app;
extern Forest forest;
extern FightScene fightscene;

void loadAnimation(char str[], Entity* e, int i, int count, int frames)
{

    char text[500];

    while (count <= frames)
    {
        sprintf(text, "%s/%d.png", str, count);

        if (i == 0)
        {
            e->animation[count] = loadTexture(text);
        }
        else if (i == 1)
        {
            e->effects[count] = loadTexture(text);
        }
        else if (i == 2)
        {
            e->sEffects[count] = loadTexture(text);
        }
        count++;
    }
}

void animation(Entity * e)
{
    if (forest.attackingEntity->dead || forest.player->dead)
    {
        // If either entity is dead, destroys the bigTexture of the given entity
        SDL_DestroyTexture(e->bigTexture);
        refreshDraw();
    }
    else if (!forest.attackingEntity->dead || !forest.player->dead)
    {
        for (int i = 0; i <= 3; i++)
        {
            // Set the bigTexture of the entity to the current animation frame
            e->bigTexture = e->animation[i];
            refreshDraw();
        }

        playSound(getSoundEntity(e), 0);
        effects(e, 1);
    }
}

void effects(Entity* r, int a)
{

    for (int i = 0; i <= 4; i++)
    {
        if (a == 1)
        {
            r->effects[0] = r->effects[i];
        }
        else if (a == 2)
        {
            r->sEffects[0] = r->sEffects[i];
        }
        refreshDraw();
    }

}

void refreshDraw()
{
        drawMe();
        SDL_RenderPresent(app.renderer);
        SDL_Delay(150);
}