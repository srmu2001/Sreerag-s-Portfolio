

///      <summary>
///      Initializes the texture linked list.
///      </summary>
void initTextures(void);

///      <summary>
///      Loads an SDL_Texture from a file or retrieves it from the cache.
///      </summary>
Texture* loadTexture(char *filename);

///      <summary>
///      Converts an SDL_Surface to an SDL_Texture.
///      </summary>
Texture* toTexture(SDL_Surface *surface, int destroySurface);

