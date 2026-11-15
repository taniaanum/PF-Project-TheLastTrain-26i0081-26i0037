#include "level.h"
#include "util.h"
#include <iostream>
using namespace std;
// Modular implementation using primitive arrays for map parsing and verification


bool loadBuildingMap(const char* filename,
                     char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                     char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                     int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){
    return true;
                     }

bool loadInitialState(const char* filename,
                      int& playerFloor, int& playerRoom,
                      int& energy, int& time, int& score,
                      char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                      bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft){
    return true;}

bool validateStartingRoom(int startFloor, int startRoom,
                          const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){
    return true;
}

const char* getEntityName(char entitySymbol){
    return "EntityName";
}

