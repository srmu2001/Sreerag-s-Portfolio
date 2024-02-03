
//SREERAG MURALEEDHARAN


//  Map is initialized and draws here

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern Forest forest;

static Texture *tiles[MAX_TILES];

void initMap(void)
{
    loadTiles();
}

void drawMap(void)
{
    int x, y, mx, my;
    MapTile* t;

    // Iterate through the visible portion of the map.
    for (x = 0; x < MAP_RENDER_WIDTH; x++)
    {
        for (y = 0; y < MAP_RENDER_HEIGHT; y++)
        {
            mx = x + forest.camera.x;
            my = y + forest.camera.y;

            // Check if the current position is within the map boundaries.
            if (mx >= 0 && my >= 0 && mx < MAP_WIDTH && my < MAP_HEIGHT)
            {
                // tiles are taken from the 2x2 map matrix
                t = &forest.map[mx][my];

                // Check if the tile is not a hole.
                if (t->tile != TILE_HOLE)
                {
                    // Render the tile using the blit function.
                    blit(tiles[t->tile], (x * MAP_TILE_SIZE) + MAP_RENDER_X, (y * MAP_TILE_SIZE) + MAP_RENDER_Y, 0, SDL_FLIP_NONE);
                }
            }
        }
    }
}

void generateMap(void)
{
    int x, y;
    char* data, * p;

    // Read map data from the "map.data" file.
    data = readFile("res/map/map.data");

    // Initialize the pointer for parsing the data.
    p = data;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            // Set the tile value at the current position based on the parsed integer value.
            forest.map[x][y].tile = atoi(p);

            // Move the pointer to the next data value.
            do { p++; } while (*p != ' ');
        }
    }

    // Free the allocated memory for the data.
    free(data);

    // Set the player's initial position.
    forest.player->x = 3;
    forest.player->y = 3;
}

void loadTiles(void)
{
    int i;
    char filename[MAX_FILENAME_LENGTH];

    for (i = 1; i < MAX_TILES; i++)
    {
        if (i < 2)
        {
            sprintf(filename, "res/assets/forest/Tile.png");
            printf("%d", i);
        }
        else if (i >= 2)
        {
            sprintf(filename, "res/assets/forest/Wall.png");
            printf("%d", i);
        }

        tiles[i] = loadTexture(filename);
    }
}

void loading(void)
{
    Texture* loadings;

    loadings = loadTexture("res/assets/forest/loading.png");
    blit(loadings, 430, 290, 0, SDL_FLIP_NONE);
}
