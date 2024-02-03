

///      <summary>
///      Producing entities
///      </summary>
void initEntityFactory(void);

///      <summary>
///      Function to create an entity and then look for an initFunc with 
///      a name matching the one we passed into the function
///      </summary>
Entity* initEntity(char* name);

///      <summary>
///      Function malloc and memset an entity, and adding it to the dungeon's entity linked list
///      </summary>
Entity* spawnEntity(void);

///      <summary>
///      this function prepares an InitFunc by mallocing and memsetting it, 
///      before then adding it to the list of other initFuncs.
///      <para>- name: Name of the entity type associated with the initialization function.</para>
//       <para>- init: Pointer to the entity initialization function.</para>
///      </summary>
void addInitFunc(char* name, void (*init)(Entity* e));

///      <summary>
///      Retrieves the entity initialization function associated with the given entity type name.
///      It searches the linked list of initialization functions to find the matching entity type.
///      </summary>
InitFunc* getInitFunc(char* name);