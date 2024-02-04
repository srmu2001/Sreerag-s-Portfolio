

//SREERAG MURALEEDHARAN


typedef struct Entity	  Entity;
typedef struct Texture	  Texture;
typedef struct InitFunc	  InitFunc;
typedef struct Node		  Node;
typedef struct Classes	  Classes;


struct Texture
{
	char		 name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect	 rect;
	int			 rotated;
	Texture		*next;
};

struct Node
{
	int	  x;
	int	  y;
	int	  g;
	int	  f;
	int	  h;
	int	  closed;
	Node *parent;
	Node *next;
};

struct Entity
{
	int	 type;
	char name[MAX_NAME_LENGTH];
	int	 x;
	int	 y;
	int	 dead;
	int	 solid;
	int	 facing;
	int  sound;

	void (*data);
	void (*animations)(Entity* e);
	void (*effect)(Entity* r, int a);
	void (*touch)(Entity* self, Entity* other);
	

	Texture* texture;
	Texture* bigTexture;
	Texture* animation[7];
	Texture* effects[7];
	Texture* sEffects[7];

	Entity	   *next;
};

typedef struct
{
	int		  hp, maxHP;
	int		  attack;
	int		  defense;
	int		  alert;
	int		  visRange;
	int       pots;
	int       level;
	int       xp;
	int       requiredXP;

	SDL_Point patrolDest;
} Monster;

struct InitFunc
{
	char name[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

typedef struct
{
	int hppot;
	int armor;
	int weapon;
	
} Item;

 struct Classes
{
	int classes;
	void (*setClasses)(int classes);
	int (*getClasses)(void);

};

typedef struct
{
	int tile;

} MapTile;

typedef struct
{
	int	 type;
	char text[MAX_DESCRIPTION_LENGTH];
} HudMessage;

typedef struct
{
	HudMessage messages[NUM_HUD_MESSAGES];
} Game;

typedef struct
{
	int		  entityId;
	Entity	  entityHead, *entityTail;
	Entity	  deadHead, *deadTail;
	Entity   *player, *currentEntity, *attackingEntity, *orcKing;
	MapTile	  map[MAP_WIDTH][MAP_HEIGHT];
	SDL_Point camera;
	double	  animationTimer;

} Forest;

typedef struct
{
	Texture* background;
	Texture* textbox;

} FightScene;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;

	double		  deltaTime;
	double		  fontScale;
	SDL_Renderer *renderer;
	SDL_Window   *window;
	int			  keyboard[MAX_KEYBOARD_KEYS];

	struct
	{
		int fps;
	} dev;

} App;
