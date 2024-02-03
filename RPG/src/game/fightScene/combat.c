

// Handles the combat scenarios in the fightScene.

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App     app;
extern Forest forest;
extern FightScene fightscene;

extern Monster* player, * enemy;
extern Entity* Player, * Enemy;


void playerAttack()
{
    animation(Player);
    playerDamage();
    enemyAttack();
}

void usingPots()
{
    if (getHealth(player) == getMaxHealth(player))
    {
        fullHP();
    }
    else
    {
        if (getPlayerPots(player) == 0)
        {
            noPots();
        }
        else
        {
            effects(Player, 2);
            usePots();
            enemyAttack();
        }
    }
}

void runningAway()
{
    playSound(SND_RUNNING, 0);
    setHealth(enemy, getMaxHealth(enemy));
    SDL_Delay(1000);
    initForestView(1);
    paused = 0;
}

void enemyAttack()
{
    if (getHealth(enemy) == 0)
    {
        death(Enemy);
        SDL_Delay(1200);

        if (getType(Enemy) != ET_MONSTERKING)
        {
            if (Enemy->dead == 1)
            {
                // Add experience points to the player.
                addPlayerXP(getXp(enemy));
            }
        }
    }
    else
    {
        animation(Enemy);
        enemyDamage();
    }

    if (getHealth(player) == 0)
    {
        death(Player);
    }
}

