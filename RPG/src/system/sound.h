


///     <summary>
///     Plays a specified sound effect on a specified channel.
///     <para>-id : An integer representing the index of the sound effect in the sounds array.</para>
///     <para>-channel : An integer indicating the channel on which to play the sound effect.</para>
///     </summary>
void playSound(int id, int channel);

///     <summary>
///     Plays the loaded background music.
///     </summary>
void playMusic(int loop);

///     <summary>
///     Loads and sets background music.
///     <para>- Stops any currently playing music.</para>
///     <para>- Frees previously loaded music resources.</para>
///     <para>- Loads and sets the specified music file.</para>
///     </summary>
void loadMusic(char *filename);

///     <summary>
///     Initializes sound-related resources and loads required audio files.
///     </summary>
void initSound(void);
