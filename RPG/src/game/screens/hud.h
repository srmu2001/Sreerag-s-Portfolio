
///      <summary>
///      This function is responsible for initializing the HUD by resetting the timer used
///      for displaying informational messages.
///      </summary>
void initHud(void);

///      <summary>
///      This function is called during each frame update to manage the HUD state.
///      It decreases the infoMessageTimer by deltaTime to control the duration of displayed messages.
///      </summary>
void doHud(void);

///      <summary>
///      This function adds a new message to the HUD, updating the infoMessageTimer to display 
///      the message for a specific duration.It also shifts existing messages to make room for 
///      the new message
///      </summary>
void addHudMessage(int type, char* text);

///      <summary>
///      This function is responsible for drawing the HUD by calling the drawMessages function.
///      It serves as an abstraction layer for the specific drawing logic of messages.
///      </summary>
void drawHud(void);

///      <summary>
///      This function iterates through the array of HUD messages and draws each message on the screen.
///      The colors of the messages are determined based on their types.
///      </summary>
void drawMessages(void);

///     <summary>
///     This function is responsible for rendering the top bar of the FightScene screen,
///     including player and enemy health information.
///     </summary>
void drawTopBar();
