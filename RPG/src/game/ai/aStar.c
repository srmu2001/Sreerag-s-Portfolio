

// This is where we'll be doing our A* pathfinding

#include "../../common.h"
#include "../../system.h"
#include "../../game.h"

extern Forest forest;

static Node	   nodeHead;
static Node*   nodeTail;
static Entity* owner;

void initAStar(void)
{
	
	// Using memset to set the memory of nodeHead to zero
	memset(&nodeHead, 0, sizeof(Node));
	nodeTail = &nodeHead;

}

void resetAStar(void)
{
	Node*  n;

	while (nodeHead.next != NULL)
	{

		n = nodeHead.next;
		nodeHead.next = n->next;
		free(n);

	}
	// Resetting nodeTail to point to nodeHead, as the linked list is now empty.
	nodeTail = &nodeHead;
}

void addNodeToOpenList(Node *node)
{
	Node*  n;
	// Checking if the node has a valid cost (not an obstacle).
	if (node->f != -1)
	{
		
		for (n = nodeHead.next; n != NULL; n = n->next)
		{
			// Checking if a node with the same coordinates already exists in the open list.
			if (n->x == node->x && n->y == node->y)
			{
				// If the new node has a lower cost, update the existing node's values.
				if (node->f < n->f)
				{
					n->f = node->f;
					n->g = node->g;
					n->h = node->h;
					n->closed = 0;
					n->parent = node->parent;
				}

				free(node);
				return;
			}
		}
		// If no matching node is found, add the new node to the end of the open list.
		nodeTail->next = node;
		nodeTail = node;
	}

    else
	{
        free(node);
	}
}

Node* getSmallestNode(void)
{
	Node*  smallest, *n;
	smallest = n = NULL;

	for (n = nodeHead.next; n != NULL; n = n->next)
	{
		// Check if the node is not closed, has a valid cost, and has a smaller 'f' value.
		if (!n->closed && n->f != -1 && (smallest == NULL || n->f < smallest->f))
		{
			smallest = n;
		}
	}
	return smallest; 
}

void buildRouteMap(int sx, int sy, int ex, int ey)
{
	
	Node*  start;
	Node*  currentNode;
	Node*  newNode;

	int x, y, count;

	// Allocate and initialize the start node at the starting coordinates.
	start = malloc(sizeof(Node));
	memset(start, 0, sizeof(Node));
	start->x = sx;
	start->y = sy;
	addNodeToOpenList(start);

	currentNode = start;
	count = 0;

	// Infinite loop for A* algorithm execution.
	while (1)
	{
		// Nested loops to explore neighboring cells.
		for (y = -1; y <= 1; y++)
		{
			for (x = -1; x <= 1; x++)
			{
				// Skip the center cell (current node)
				if (x == 0 && y == 0)
				{
					continue;
				}
				    // Checking if the neighboring cell is within valid map bounds.
				    if (currentNode->x + x < 0 || currentNode->y + y < 0 || currentNode->x + x >= MAP_WIDTH || currentNode->y + y >= MAP_HEIGHT)
				    {
					     continue;
				    }

			    // Allocating and initializing a new node for the neighboring cell.
				newNode = malloc(sizeof(Node));
				memset(newNode, 0, sizeof(Node));

				newNode->x = currentNode->x + x;
				newNode->y = currentNode->y + y;

				// Checking if the cell is not blocked.
				if (!isBlocks(newNode->x, newNode->y))
				{

					if (x != 0 && y != 0)
					{
						// Calculating the cost of movement (g value) based on diagonal or straight movement.
						newNode->g = currentNode->g + 14;
					}
					else
					{
						newNode->g = currentNode->g + 10;
					}
					// Calculate the heuristic (h value) and total cost (f value).
					newNode->h = 10 * (abs(newNode->x - ex) + abs(newNode->y - ey));
					newNode->f = newNode->g + newNode->h;
				}
				else
				{
					// If the cell is blocked, set cost values to -1.
					newNode->f = -1;
					newNode->g = -1;
					newNode->h = -1;
				}

				newNode->parent = currentNode;
				addNodeToOpenList(newNode);

				// Check if the node count limit is reached.
				if (++count >= MAP_HEIGHT * MAP_WIDTH)
				{
					return;
				}
			}
		}
		currentNode = getSmallestNode();

		if (!currentNode)
		{
			break;
		}
		currentNode->closed = 1;

		// Break the loop if the destination is reached.
		if (currentNode->x == ex && currentNode->y == ey)
		{
			break;
		}
	}
}

int isBlocks(int x, int y)
{
	Entity *e;

	if (forest.map[x][y].tile == TILE_HOLE || forest.map[x][y].tile >= TILE_WALL)
	{
		return 1;
	}

	e = getEntityAt(x, y);

	if (e != NULL && e != owner && e->solid)
	{
		return 1;
	}

	return 0;
}

Node *findNextMove(int x, int y)
{
	Node *n;

	for (n = nodeHead.next; n != NULL; n = n->next)
	{
		if (n->x == x && n->y == y)
		{
			return n->parent;
		}
	}
	return NULL;
}

void createAStarRoute(Entity *e, int x, int y, int *dx, int *dy)
{
	
	Node *n;
	owner = e;
	*dx = 0;
	*dy = 0;

	resetAStar();
	buildRouteMap(x, y, e->x, e->y);

	n = findNextMove(e->x, e->y);

	// If a valid next move is found, calculate the movement direction.
	if (n != NULL)
	{
		*dx = n->x - e->x;
		*dy = n->y - e->y;
	}
}
