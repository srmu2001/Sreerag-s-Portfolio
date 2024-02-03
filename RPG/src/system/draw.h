
///      <summary>
///      Presents the rendered scene to the screen by swapping the front and back buffers.
///      </summary>
void prepareScene(void);

///      <summary>
///      Prepares the rendering scene by setting the clear color and clearing the renderer.
///      </summary>
void presentScene(void);

///      <summary>
///      Renders a texture onto the screen at the specified position, with optional centering and flipping.
///      <para>- texture: Pointer to the texture to be rendered.</para>
///      <para>- x, y: Coordinates indicating the position on the screen where the texture will be rendered.</para>
///      <para>- center: Flag indicating whether to center the texture at the specified position.</para>
///      <para>- flip: SDL_RendererFlip flag indicating the flipping (mirroring) of the texture.</para>
///      </summary>
void blit(Texture* texture, int x, int y, int center, SDL_RendererFlip flip);

///      <summary>
///      Draws a filled rectangle on the screen with specified attributes.
///      </summary>
void drawRect(int x, int y, int w, int h, int r, int g, int b, int a);

///      <summary>
///      Draws an outlined rectangle on the screen with specified attributes.
///      </summary>
void drawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a);

///      <summary>
///      Performs a fade-in effect by gradually increasing the alpha (transparency) of a texture.
///      </summary>
void fadeIn(SDL_Renderer* renderer, Texture* texture, int duration);


