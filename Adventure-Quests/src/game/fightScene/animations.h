
//SREERAG MURALEEDHARAN


///      <summary>
///      Loads a images for an entity's animation or effects.
///      <param>- str   : Base path for the image files.</param>
///      <para>- e     : Pointer to the entity for which the animation frames are loaded.</para>
///      <para>- i     : Type indicator (0 for animation, 1 for effects, 2 for special effects).</para>
///      <para>- count : Current frame count, starting from 0.</para>
///      <para>- frames: Total number of frames to load.</para>
///      </summary>
void loadAnimation(char str[], Entity* e, int i, int count, int frames);

///      <summary>
///      Manages the animation sequence for a given entity, including attack animations and effects.
///      </summary>
void animation(Entity* e);

///      <summary>
///      Manages visual effects for a given entity, such as attack or special effects.
///      </summary>
void effects(Entity* r, int a);

///      <summary>
///      Function to draw it, and present the renderer.
///      </summary>
void refreshDraw();
