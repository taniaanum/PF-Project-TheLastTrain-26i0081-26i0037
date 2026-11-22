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

bool handleMoveCommand(int targetFloor, int targetRoom,int& currentFloor, int& currentRoom,int& energy, int& time, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,int& emergencyTripsLeft, bool lift2Operational){
   char path_type = 0 ;

     if (!( isDirectlyConnected(currentFloor, currentRoom, targetFloor, targetRoom, horizontalConn, path_type)))
         {cout << "You cannot move from  F" << currentFloor << "-R" << currentRoom << "  to  F" << targetFloor << "-R" << targetRoom << " No direct connection.\n";
          return false;
          }

     if ( path_type == CONN_LIFT2)
     {
     if(!(canUseLift2(currentFloor, targetFloor, lift2Operational, emergencyTripsLeft)))
        {
          cout << "lift 2 cannot be used as it has no power and no emergency trips left.\n";
         
          return false;
        }
      }
      if (!(canTraverse(targetFloor, targetRoom, path_type, inventory, inventoryCount, emergencyTripsLeft, lift2Operational)))
         {
          
           if (path_type == CONN_LOCKED_DOOR)
          {
            cout << "You cannot move from  F" << currentFloor << "-R" << currentRoom << "  to  F" << targetFloor << "-R" << targetRoom << " as the door is locked and you do not have the Master Key.\n";
          }
           else if (path_type == CONN_LIFT2)
          {
            cout << "You cannot move from  F" << currentFloor << "-R" << currentRoom << "  to  F" << targetFloor << "-R" << targetRoom << " you need the Lift Pass, or the EmergencyAccess Card.\n";
          }
           else
          {
            cout << "You cannot move from  F" << currentFloor << "-R" << currentRoom << "  to  F" << targetFloor << "-R" << targetRoom << " This way is blocked \n";
          }
         
          return false;
         }
      int cost_energy = 0;
      int cost_time = 0;
      if (path_type == CONN_WINDOW)
      {
          cost_energy = COST_MOVE_WINDOW_ENERGY;
            cost_time = COST_MOVE_WINDOW_TIME;
        }
        else if (path_type == CONN_LIFT1 || path_type == CONN_LIFT2)
        {
            cost_energy = COST_MOVE_LIFT_ENERGY;
            cost_time = COST_MOVE_LIFT_TIME;
        }
        else
        {
            cost_energy = COST_MOVE_ORDINARY_ENERGY;
            cost_time = COST_MOVE_ORDINARY_TIME;
        }
      applyResourceDelta(energy, time, cost_energy, cost_time);
      bool normalway = (lift2Operational) && (hasItem(inventory, inventoryCount, ENT_LIFT_PASS));
     if (path_type == CONN_LIFT2 && !normalway)
     {
        emergencyTripsLeft--;
     }
      currentFloor = targetFloor;
      currentRoom = targetRoom;
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



