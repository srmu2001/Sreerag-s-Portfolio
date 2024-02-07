
//SREERAG MURALEEDHARAN

// Handles the combat Mechanism

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern App     app;
extern Forest forest;
extern FightScene fightscene;

extern Monster* player, * enemy;
extern Entity* Player, * Enemy;

int type;

void playerDamage()
{
    // Limiting the damage value to 0 so that the enemy's HP won't go below 0
    setHealth(enemy, MAX(getHealth(enemy) - (getAttack(player) - getDefense(enemy)), 0));

    type = HUD_MSG_BAD;
    addHudMessage(type, "Enemy hit ");
    SDL_Delay(1000);
}

void enemyDamage()
{
    // Limiting the damage value to 0 so that the enemy's HP won't go below 0
    setHealth(player, MAX(getHealth(player) - (getAttack(enemy) - getDefense(player)), 0));

    type = HUD_MSG_BAD;
    addHudMessage(type, "Player hit");
    SDL_Delay(1000);
}

void fullHP()
{
    type = HUD_MSG_GOOD;
    addHudMessage(type, "MAX HP");
    playSound(SND_ERROR, 0);
}

void noPots()
{
    type = HUD_MSG_BAD;
    addHudMessage(type, "No HP pots");
    playSound(SND_ERROR, 0);
}

void usePots()
{
    player->pots--;

    // Limiting the amount of HP gained from HP potion to player's maxHP
    setHealth(player, MIN(getHealth(player) + 50, getMaxHealth(player)));

    type = HUD_MSG_GOOD;
    addHudMessage(type, "HP pot used");
    playSound(SND_HPPOT, 0);
    SDL_Delay(1000);
}

void death(Entity* e)
{
    e->dead = 1;

    if (getType(e) == ET_PLAYER)
    {
        playSound(SND_PLAYERDEATH, 0);
        addHudMessage(type, "Player DEAD");
        SDL_Delay(150);
        animation(Player);
        SDL_Delay(1000);

        initEnding(2);
    }
    else if (getType(Enemy) == ET_MONSTERKING)
    {
        playSound(SND_WIN, 0);
        addHudMessage(type, "BOSS DEAD");
        SDL_Delay(1000);
        forest.orcKing->dead = 1;
        animation(Enemy);
        SDL_Delay(1500);

        initEnding(1);
    }
    else if (getType(Enemy) == ET_MONSTER)
    {
        playSound(SND_ORCDEATH, 0);
        addHudMessage(type, "Enemy DEAD");
        forest.attackingEntity->dead = 1;
        animation(Enemy);
        SDL_Delay(1500);

        initForestView(1);

        paused = 0;
    }
}
