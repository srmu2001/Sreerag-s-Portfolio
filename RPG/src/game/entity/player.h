
//SREERAG MURALEEDHARAN


///     <summary>
///     Handles player input and movement logic.
///     </summary>
void doPlayer(void);

///     <summary>
///     Initializes the properties and attributes of an Player entity.
///     </summary>
void initPlayer(Entity* e);


///     <summary>
///     Adds experience points to the player, 
///     potentially leveling up and increasing stats.
///     </summary>
void addPlayerXP(int amount);

int steps;

//      SETTERS

void setClasses(int classes);

void setName(Entity* e, char* name);

void setEntityTexture(Entity* e, char* texturePath);

void setEntityBigTexture(Entity* e, char* bigTexturePath);

void setType(Entity* e, int type);

void setSoundEntity(Entity* e, int sound);

void setSolid(Entity* e, int solid);

void setMonsterData(Entity* e, Monster* m);

void  setDead(Entity* e, int dead);

void setFacing(Entity* e, int facing);

void setItemData(Entity* e, Item* i);

//     GETTERS

int getClasses(void);

int getType(Entity* e);

int getDead(Entity* e);

int getSolid(Entity* e);

char* getName(Entity* e);

int getSoundEntity(Entity* e);

Item* getItemData(Entity* e);

Monster* getMonsterData(Entity* e);

Texture* getEntityTexture(Entity* e);

Texture* getEntityBigTexture(Entity* e);




