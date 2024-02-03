
//  Sound system is initalized here

#include <SDL_mixer.h>
#include "../common.h"
#include "../system.h"
#include "../game.h"

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

///     <summary>
///     Saves all sound effects in "sounds" array
///     </summary>
static void loadSounds(void);

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSound(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);
	loadSounds();
	music = NULL;
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
	sounds[SND_BUTTON] = Mix_LoadWAV("res/sys/sound/button_sound.ogg");
	sounds[SND_WALK] = Mix_LoadWAV("res/sys/sound/walking_sound.ogg");
	sounds[SND_WARRIORHIT] = Mix_LoadWAV("res/sys/sound/warrior_hit_sound.ogg");
	sounds[SND_MAGEHIT] = Mix_LoadWAV("res/sys/sound/mage_ability_sound.ogg");
	sounds[SND_ORCDEATH] = Mix_LoadWAV("res/sys/sound/orcdeath_sound.ogg");
	sounds[SND_ERROR] = Mix_LoadWAV("res/sys/sound/error_sound.ogg");
	sounds[SND_ITEM] = Mix_LoadWAV("res/sys/sound/item_pickup_sound.ogg");
	sounds[SND_LVLUP] = Mix_LoadWAV("res/sys/sound/lvlup_sound.ogg");
	sounds[SND_PLAYERDEATH] = Mix_LoadWAV("res/sys/sound/player_death_sound.ogg");
	sounds[SND_WIN] = Mix_LoadWAV("res/sys/sound/win_sound.ogg");
	sounds[SND_HPPOT] = Mix_LoadWAV("res/sys/sound/hppot_sound.ogg");
	sounds[SND_RUNNING] = Mix_LoadWAV("res/sys/sound/running_sound.ogg");
}
