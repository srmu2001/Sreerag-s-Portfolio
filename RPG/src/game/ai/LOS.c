
// This is where Line of Sight (LOS) gets defined

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"


extern Forest forest;
extern Entity *player;

static int hasSolid[MAP_WIDTH][MAP_HEIGHT];

int hasLOS(Entity* sourceEntity, int targetX, int targetY)
{
    // Get the source entity's current position.
    int currentX = sourceEntity->x;
    int currentY = sourceEntity->y;

    // Calculate the differences in x and y coordinates.
    int deltaX = abs(targetX - currentX);
    int deltaY = abs(targetY - currentY);

    // Determine the direction of movement along x and y axes.
    int directionX = (currentX < targetX) ? 1 : -1;
    int directionY = (currentY < targetY) ? 1 : -1;

    // Initialize the error term.
    int error = deltaX - deltaY;

    // Bresenham's Line Algorithm for line of sight calculation.
    while (1)
    {
        int error2 = 2 * error;

        // Adjust x coordinate based on error term and direction.
        if (error2 > -deltaY)
        {
            error -= deltaY;
            currentX += directionX;
        }

        // Adjust y coordinate based on error term and direction.
        if (error2 < deltaX)
        {
            error += deltaX;
            currentY += directionY;
        }

        // Check if the current position matches the target position.
        if (currentX == targetX && currentY == targetY)
        {
            return 1; // Line of sight is clear.
        }

        // Check for obstacles (walls, holes, and solid entities) in the path.
        if (forest.map[currentX][currentY].tile == TILE_WALL || hasSolid[currentX][currentY] || forest.map[currentX][currentY].tile == TILE_HOLE)
        {
            return 0; // Line of sight is obstructed.
        }
    }

    return 0; // Default: Line of sight is obstructed.
}