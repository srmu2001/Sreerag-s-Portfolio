
//SREERAG MURALEEDHARAN


///      <summary>
///      Function to initialize the A* algorithm
///      </summary> 
void initAStar(void);

///      <summary>
///      Function which uses while loop to clear the nodes
///      </summary> 
void resetAStar(void);

///      <summary> 
///      Adds a node to the open list in the A* algorithm.
///	     If a node with the same coordinates already exists in the open list,
///	     updates its values if the new node has a lower cost.
///      If the new node has a cost of -1, indicating an obstacle, it is immediately freed.
///      </summary>
void addNodeToOpenList(Node* node);

///      <summary> 
///      Retrieves the node with the smallest 'f' value from the open list.
///      Ignores nodes marked as closed or with a cost of -1 (obstacles).
///      Returns: Pointer to the smallest node in the open list.
///      </summary>
Node* getSmallestNode(void);

///      <summary> 
///      This function is responsible for searching for a path towards our goal. 
///      As squares in our map are tested, they will be added our node list and processed.
///      Stops when the destination is reached or a limit on node count is reached.
///      <para>- sx, sy: Starting coordinates</para>
///      <para>- ex, ey: Ending coordinates</para>
///      </summary>
void buildRouteMap(int sx, int sy, int ex, int ey);

///      <summary> Checks if a given position(x, y) is blocked,
///      considering both map tiles and entities.
///      </summary>
int isBlocks(int x, int y);

///      <summary>
///      Finds the next move in the A* algorithm based on the destination coordinates (x, y).
///      </summary>
Node* findNextMove(int x, int y);

///      <summary>
///      Generates an A* route for an entity (e) from its current position to the destination (x, y).
///      </summary>
void createAStarRoute(Entity* e, int x, int y, int* dx, int* dy);
