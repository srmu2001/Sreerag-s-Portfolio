
//SREERAG MURALEEDHARAN


// MAIN function resides here

#include "main.h"
#include "common.h"
#include "system.h"
#include "game.h"


App		app;
Forest forest;
Game	game;
FightScene fightscene;

static int	fps;
static long nextFPS;
int	paused;

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

///     <summary>
///     Main logic function responsible for handling game logic.
///     Temporarily stores the original delta time, sets it to 1, calls the logic delegate function, and updates the delta time accordingly.
///     The loop ensures that logic is executed multiple times for large delta times, preventing potential issues with large time steps.
///     The loop exits once the delta time is less than or equal to 1, allowing the remaining logic to be executed.
///     Ensures consistent logic execution regardless of the actual delta time.
///     </summary>
static void logic(void);

///    <summary>
///    Calculates and updates frames per second (FPS) information.
///    </summary>
static void doFPS(void);

//********************************************* STATIC FUNCTION DEFINITION *****************************************************

int main(int argc, char* argv[])
{
    long then;

    memset(&app, 0, sizeof(App));

    initSDL();

    atexit(cleanup);

    initGameSystem();

    initTitle();

    nextFPS = SDL_GetTicks() + 1000;

    while (1)
    {
        then = SDL_GetTicks();

        prepareScene();

        doInput();

        logic();

        app.delegate.draw();

        presentScene();

        SDL_Delay(1);

        app.deltaTime = LOGIC_RATE * (SDL_GetTicks() - then);

        doFPS();
    }

    return 0;
}

static void logic(void)
{
    double tmpDelta;

    while (app.deltaTime > 1)
    {
        tmpDelta = app.deltaTime;

        app.deltaTime = 1;

        app.delegate.logic();

        app.deltaTime = (tmpDelta - 1);
    }

    app.delegate.logic();
}

static void doFPS(void)
{
    fps++;

    // Check if the current SDL ticks exceed the nextFPS threshold.
    if (SDL_GetTicks() >= nextFPS)
    {
        // Update app.dev.fps with the calculated frames per second.
        app.dev.fps = fps;

        // Reset the frames per second counter to zero.
        fps = 0;

        // Set the nextFPS for the next one-second interval.
        nextFPS = SDL_GetTicks() + 1000;
    }
}
