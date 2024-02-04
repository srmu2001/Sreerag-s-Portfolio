
//SREERAG MURALEEDHARAN


///       <summary>
///       This function calculates the damage inflicted by the player on the enemy
///       by subtracting the enemy's defense from the player's attack.If the resulting
///       damage is negative, it is set to 0. The enemy's health is then updated accordingly.
///       </summary>
void playerDamage();

///       <summary>
///       This function calculates the damage inflicted by the enemy on the player
///       by subtracting the player's defense from the enemy's attack.If the resulting 
///       damage is negative, it is set to 0. The player's health is then updated accordingly.
///       </summary>
void enemyDamage();

///      <summary>
///      This function sets the HUD message type to good and displays a message
///      indicating that the player's health has reached its maximum value.
///      Additionally, it plays a sound effect(SND_ERROR) for auditory feedback.
///      </summary>
void fullHP();

///      <summary>
///      This function sets the HUD message type to bad and displays a message
///      indicating that the player has no HP potions left.
///      Additionally, it plays a sound effect(SND_ERROR) for auditory feedback.
///      </summary>
void noPots();

///      <summary>
///      This function decrements the player's potion count, increases the player's
///      health by a fixed amount(50), and limits the health gain to the player's maxHP.
///      </summary>
void usePots();

///      <summary>
///      The death function marks an entity as dead and executes different actions based on the type of the entity
///      </summary>
void death(Entity* e);
