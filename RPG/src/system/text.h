
//SREERAG MURALEEDHARAN


///      <summary>
///      Initializes different fonts for the game.
///      </summary>
void initFonts(void);

///      <summary>
///      Creates an SDL_Texture from the provided text using a specified font type.
///      </summary>
SDL_Texture* getTextTexture(char* text, int type);

///      <summary>
///      Creates an SDL_Texture from the provided text using a specified font type.
///      </summary>
SDL_Texture* getBigTextTexture(char* text, int type);

///      <summary>
///      Creates an SDL_Texture from the provided text using a specified font type.
///      </summary>
SDL_Texture* getSmallTextTexture(char* text, int type);

///      <summary>
///      Draws text on the screen at the specified position with the given color.
///      </summary>
void drawText(char* text, int x, int y, int r, int g, int b);

///      <summary>
///      Draws text on the screen at the specified position with the given color.
///      </summary>
void drawBigText(char* text, int x, int y, int r, int g, int b);

///      <summary>
///      Draws text on the screen at the specified position with the given color.
///      </summary>
void drawSmallText(char* text, int x, int y, int r, int g, int b);
