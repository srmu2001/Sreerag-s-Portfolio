

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define FPS		   60.0
#define LOGIC_RATE (FPS / 1000)


#define MAX_NAME_LENGTH		   32
#define MAX_DESCRIPTION_LENGTH 256
#define MAX_LINE_LENGTH		   1024
#define MAX_FILENAME_LENGTH	   1024

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16

#define MAX_TILES 4

#define MAP_TILE_SIZE 48

#define MAP_WIDTH  34
#define MAP_HEIGHT 34

#define NUM_HUD_MESSAGES 5

#define MAP_RENDER_WIDTH  35
#define MAP_RENDER_HEIGHT 35

#define MAP_RENDER_X ((SCREEN_WIDTH - (MAP_RENDER_WIDTH * MAP_TILE_SIZE)) / 2)
#define MAP_RENDER_Y ((SCREEN_HEIGHT - (MAP_RENDER_HEIGHT * MAP_TILE_SIZE)) / 2)

#define TILE_HOLE	0
#define TILE_GROUND 1
#define TILE_WALL	2

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	NONE,
	WARRIOR,
	MAGE
	
};

enum
{
	ET_UKNOWN,
	ET_PLAYER,
	ET_MONSTER,
	ET_ITEM,
	ET_MONSTERKING
};

enum
{
	FACING_RIGHT,
	FACING_LEFT
};

enum
{
	HUD_MSG_NORMAL,
	HUD_MSG_GOOD,
	HUD_MSG_BAD,
	HUD_MSG_GREEN
};
enum
{
	GOOD_ENDING,
	BAD_ENDING
};
enum
{
	SND_BUTTON,
	SND_WALK,
	SND_WARRIORHIT,
	SND_MAGEHIT,
	SND_ORCDEATH,
	SND_ERROR,
	SND_ITEM,
	SND_LVLUP,
	SND_PLAYERDEATH,
	SND_WIN,
	SND_HPPOT,
	SND_RUNNING,
	SND_MAX
};