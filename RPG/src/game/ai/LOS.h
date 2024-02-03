

///      <summary>
///      Determines if there is a Line of Sight (LOS) between an Entity's current position
///      and a target position in the forest map.
///      Implements Bresenham's Line Algorithm to check for LOS.
///      <para>- src: Pointer to the Entity from which LOS is checked.</para>
///      <para>- x2: Target x-coordinate.</para>
///      <para>- y2: Target y-coordinate..</para>
///      </summary>
int hasLOS(Entity* sourceEntity, int targetX, int targetY);

