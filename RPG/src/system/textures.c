
//SREERAG MURALEEDHARAN


// Textures are initialized here

#include <SDL_image.h>
#include "../common.h"
#include "../system.h"
#include "../game.h"

extern App app;

static Texture	textureHead;
static Texture *textureTail;
static Texture* getTexture(char* name);

void initTextures(void)
{
    memset(&textureHead, 0, sizeof(Texture));
    textureTail = &textureHead;
}

// Retrieves a texture from the linked list based on its name.
static Texture* getTexture(char* name)
{
    Texture* t;

    for (t = textureHead.next; t != NULL; t = t->next)
    {
        if (strcmp(t->name, name) == 0)
        {
            return t->texture;
        }
    }

    return NULL;
}

Texture* toTexture(SDL_Surface* surface, int destroySurface)
{
    Texture* texture;

    texture = SDL_CreateTextureFromSurface(app.renderer, surface);

    if (destroySurface)
    {
        SDL_FreeSurface(surface);
    }

    return texture;
}

Texture* loadTexture(char* filename)
{
    Texture* texture;

    texture = getTexture(filename);

    if (texture == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s ...", filename);
        texture = IMG_LoadTexture(app.renderer, filename);
    }

    return texture;
}