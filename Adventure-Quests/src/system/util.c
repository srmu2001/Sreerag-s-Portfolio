
//SREERAG MURALEEDHARAN

// Game utility functions resides here

#include "../common.h"
#include "../system.h"
#include "../game.h"

int getDistance(int x1, int y1, int x2, int y2)
{
	int x, y;

	// Calculate the differences in x and y coordinates
	x = x2 - x1;
	y = y2 - y1;

	// Calculate and return the Euclidean distance
	return sqrt(x * x + y * y);
}

char *readFile(char *filename)
{
	char *buffer;
	long  length;
	FILE *file;

	// Open the file in binary mode
	file = fopen(filename, "rb");

	// Check if the file exists
	if (file == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "No such file '%s'", filename);
		exit(1);
	}

	// Determine the length of the file
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allocate memory for the buffer
	buffer = malloc(length);
	memset(buffer, 0, length);

	// Read the content of the file into the buffer
	fread(buffer, 1, length, file);

	// Close the file
	fclose(file);

	return buffer;
}

