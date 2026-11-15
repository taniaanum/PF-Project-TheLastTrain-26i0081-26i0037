#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "viewer_iface.h"
#include "util.h"
#include <iostream>
using namespace std;

// Modular simulation loop using primitive variables

void runSimulation(int& playerFloor, int& playerRoom,
                   int& energy, int& time, int& score,
                   char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                   bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft,
                   char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                   char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                   int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
                   {

                   }

bool handleMoveCommand(int targetFloor, int targetRoom,
                       int& currentFloor, int& currentRoom,
                       int& energy, int& time,
                       const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                       const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                       int& emergencyTripsLeft, bool lift2Operational){
                        return true;
                       }

bool handleInspectCommand(int currentFloor, int currentRoom,
                          int& energy, int& time,
                          const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                          int entityCount,
                          bool objectives[NUM_OBJECTIVES], int& score)
                          {
                            return true;
                          }

bool handleCollectCommand(char itemSymbol, int currentFloor, int currentRoom,
                          int& energy, int& time, int& score,
                          char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                          int& entityCount,
                          char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                          bool objectives[NUM_OBJECTIVES]){
                            return true;
                          }

bool handleUseCommand(char itemSymbol, int currentFloor, int currentRoom,
                      int& energy, int& time, int& score,
                      char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                      bool objectives[NUM_OBJECTIVES]){
    return true;
}

bool handleUnlockCabinetCommand(const char* code, int currentFloor, int currentRoom,
                                bool objectives[NUM_OBJECTIVES], int& score,
                                char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                                int& entityCount){
    return true;
}

bool checkEndConditions(int energy, int time, const bool objectives[NUM_OBJECTIVES]){
    return true;
}



