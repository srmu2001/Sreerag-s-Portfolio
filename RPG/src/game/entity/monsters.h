
//SREERAG MURALEEDHARAN


///      <summary>
///      Initializes the properties and attributes of an Orc entity.
///      </summary>
void initOrc(Entity *e);

///      <summary>
///      Adds monsters to the forest envirnoment
///      </summary>
void addMonsters(void);

///      <summary>
///      Moves to the next active monster entity in the turn order.
///      </summary>
void nextMonster(void);

///     <summary>
///     Handles the logic for monster entities during the game loop.
///     </summary>
void doMonsters(void);

///     <summary>
///     Initializes the properties and attributes of an Orc King entity.
///     </summary>
void initOrcKing(Entity* e);

///     <summary>
///     Implements the decision - making process for a monster entity 
///     when its in the forest environment.
///     </summary>
void think(Entity* e);

///     <summary>
///     Checks if the player is within the monster's visibility range and has line of sight.
///     </summary>
void lookForPlayer(Entity* e, Monster* m);

///     <summary>
//      Moves the monster towards the player using A* pathfinding.
///     </summary>
void moveToPlayer(Entity* e, Monster* m);

///     <summary>
//      Controls the patrol behavior of the monster.
///     </summary>
void patrol(Entity* e, Monster* m);

///     <summary>
///     Creates a monster - specific data structure for an entity.
///     </summary>
Monster* createMonster(Entity* e);


//      SETTERS

void setHealth(Monster* m, int hp);

void setMaxHealth(Monster* m, int maxHp);

void setDefense(Monster* m, int defense);

void setAttack(Monster* m, int attack);

void setVisRange(Monster* m, int visRange);

void setXp(Monster* m, int xp);

void setAlert(Monster* m, int alert);

void setRequiredXP(Monster* m, int requiredXP);

void setLevel(Monster* m, int level);

void setPlayerPots(Monster* m, int pots);


//      GETTERS

int getHealth(Monster* m);

int getMaxHealth(Monster* m);

int getDefense(Monster* m);

int getAttack(Monster* m);

int getVisRange(Monster* m);

int getXp(Monster* m);

int getAlert(Monster* m);

int getPlayerPots(Monster* m);

int getLevel(Monster* m);

int getRequiredXP(Monster* m);



