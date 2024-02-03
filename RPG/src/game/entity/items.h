

///      <summary>
///      Function to add items to the Forest 
///      </summary>
void addItems(void);

///      <summary>
///      Initializes an Entity as a health pack item.
///      </summary>
void initHealthPack(Entity* e);

///     <summary>
///     Initializes an Entity as a Armor item.
///     </summary>
void initArmor(Entity* e);

///     <summary>
///     Initializes an Entity as a Weapon item.
///     </summary>
void initWeapon(Entity* e);

///     <summary>
///     Creates and initializes an Item associated with the given Entity.
///     </summary>
Item* createItem(Entity* e);

///     <summary>
///     Handles the interaction between an health pack item entity and another Entity(player)
///     </summary>
void touchPot(Entity* self, Entity* other);

///     <summary>
///     Handles the interaction between an weapon item entity and another Entity(player)
///     </summary>
void touchWeapon(Entity* self, Entity* other);

///     <summary>
///     Handles the interaction between an armor item entity and another Entity(player)
///     </summary>
void touchArmor(Entity* self, Entity* other);

///     <summary>
///     This function is responsible for handling the destruction of an item entity.
///     It generates a message indicating the item picked up, adds it to the HUD,
///     removes the item from the game world, and plays a sound effect.
///     </summary>
void destroyItem(Entity* self);

//      SETTERS 

void setHpPot(Item* i, int HpPot);

//      GETTERS

int getHpPot(Item* i);