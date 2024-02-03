

///      <summary>
///      Initializes the entity-related data structures in the forest, 
///      setting up linked lists for living and dead entities.
///      </summary>
void initEntities(void);

///      <summary>
///      Processes the entities in the forest, updating their status, preparing them for ,
///      drawing order, and handling dead entities.
///      </summary>
void doEntities(void);

///      <summary>
///      Moves the given entity by the specified amount in the x and y directions, updating its position.
///      </summary>
void moveEntity(Entity* e, int dx, int dy);

///      <summary>
///      Checks if the specified position is blocked by other entities in the forest
///      </summary>
int	isBlocked(Entity* e, int x, int y);

///      <summary>
///      Adds the given entity to the forest by determining a suitable position based on its type.
///      </summary>
void addEntityToForest(Entity* e);

///      <summary>
///      Removes the given entity from the forest's linked list of entities.
///      </summary>
void removeEntityFromForest(Entity* e);

///      <summary>
///      Checks if the specified position in the forest is occupied by an entity.
///      </summary>
int isOccupied(int x, int y);

///      <summary>
///      Retrieves the entity located at the specified position in the forest.
///      </summary>
Entity* getEntityAt(int x, int y);

///      <summary>
///      Draws the entities stored in the array entsToDraw, 
///      limiting the number of entities to MAX_ENTS_TO_DRAW.
///      It iterates through the array and calls the drawEntity function for each valid entity.
///      </summary>
void drawEntities(void);

///      <summary>
///      Draws the specified entity on the screen, taking into account the camera's position.
///      </summary>
void drawEntity(Entity* e);

///      <summary>
///      Comparator function for qsort to determine the drawing order of entities.
///      It compares two entities based on their types, giving priority to certain entities.
///      </summary>
int drawComparator(const void* a, const void* b);








