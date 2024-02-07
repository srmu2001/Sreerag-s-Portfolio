
//SREERAG MURALEEDHARAN


// This is where inputs are initialized

#include "../common.h"
#include "../system.h"
#include "../game.h"

extern App app;

// Handles the SDL_KEYUP event, updating the keyboard state by setting the corresponding key to released.
static void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

// Handles the SDL_KEYUP event, updating the keyboard state by setting the corresponding key to pressed.
static void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
}
	
void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			default:
				break;
		}
	}	
}

void clearInput(void)
{
	SDL_Event event;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}