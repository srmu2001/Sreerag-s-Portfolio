
// Handles the drawing of textures

#include <SDL_image.h>
#include "../common.h"
#include "../system.h"
#include "../game.h"

extern App app;

void prepareScene(void)
{
	
	SDL_SetRenderDrawColor(app.renderer, 1, 50, 32, 255);
	SDL_RenderClear(app.renderer);

}

void presentScene(void)
{

	SDL_RenderPresent(app.renderer);

}

void blit(Texture*texture, int x, int y, int center, SDL_RendererFlip flip)
{

	SDL_Rect dest;

	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{

		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;

	}

	SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, 0, NULL, flip);

}

void drawRect(int x, int y, int w, int h, int r, int g, int b, int a)
{

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	// Set the blend mode based on the alpha value.
	SDL_SetRenderDrawBlendMode(app.renderer, a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_RenderFillRect(app.renderer, &rect);

}

void drawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a)
{

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawBlendMode(app.renderer, a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_RenderDrawRect(app.renderer, &rect);

}

void fadeIn(SDL_Renderer* renderer, Texture* texture, int duration)
{

	int steps = 255 / duration;

	for (int i = 0; i <= duration; ++i) 
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Set the alpha modulation of the texture to achieve the fade-in effect.
		SDL_SetTextureAlphaMod(texture, i * steps);

		blit(texture, 0, 0, 0, SDL_FLIP_NONE);

		// // Set the texture blend mode to enable blending with the background.
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		SDL_RenderPresent(renderer);
		SDL_Delay(1000 / 60);
	}
}