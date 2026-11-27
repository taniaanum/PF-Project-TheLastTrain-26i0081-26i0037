#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "level.h"
#include "viewer_iface.h"
#include "util.h"
#include <iostream>
#include<iomanip>
using namespace std;


// helper function1 for run simulation
    static void commands()
     {
        cout << "Available commands:\n";
        cout << "  move <floor> <room> - Move to a specified floor and room.\n";
        cout << "  inspect - (to reveal the hidden clue digits).\n";
        cout << "  collect <item_symbol> - Collect an item from the current room.\n";
        cout << "  use <item_symbol> - Use an item from your inventory.\n";
        cout << "  unlock <code> - Attempt to unlock the cabinet with a code.\n";
        cout << "  board - Board the train (in F5-R2, needs the Train Key)..\n";
        cout << "  save - Save the current game state to a file.\n";
        cout << "  load - Load a game state from a file.\n";
        cout << "  map - Display the ASCII representation of the building.\n";
        cout << "  status - Display the current objectives checklist.\n";
        cout << "  help - Display this list of commands.\n";
        cout << "  quit - Exit the simulation.\n";
      
      }
// helper function 2 receives the item we already collected from the room and removes it from the roomentities so no item can be collected twice
static bool removefromroom(int floor , int room , char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],int&count,char rem_symbol)
{
  int pos = -1 ; //haven't found it yet ;
   for ( int i =0 ; i < count ; i++ )
   {
    if ( roomEntities[floor-1][room-1][i] == rem_symbol)
    {
     pos = i ;
     break;
    }
   }
   if(pos==-1)
   {
    return false ;
   }
    // slide left
   for ( int j = pos ; j < count - 1 ; j++)
   {
    roomEntities[floor-1][room-1][j] = roomEntities[floor-1][room-1][j+1];
   }

   // remove the copied item
    roomEntities[floor-1][room-1][count-1] = ENT_NONE;
    count -- ;

   return true;
   
  }






// Modular simulation loop using primitive variables

void runSimulation(int& playerFloor, int& playerRoom,int& energy, int& time, int& score,char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
 bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft,char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
     int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
                   {
     
       // temporary variables (the real position is only set once the room is valid)
    int chosenfloor = 0;
    int chosenroom = 0;

    cout << "Simulation started. Player enter your coordinates floor and room (e.g., 1 1 for Floor 1, Room 1): ";
    cin >> chosenfloor >> chosenroom;

    // validating starting room
    while (!cin || !validateStartingRoom(chosenfloor, chosenroom, horizontalConn))
    {
        if (cin.eof()) // no input and no chance of future input (the file ended)
        {
            return;
        }

        if (!cin) // letters were typed (cin switched itself off)
        {
            cin.clear();              // switches cin back on
            cin.ignore(1000, '\n');   // throws away the rest of the bad line
            cout << "Please type two numbers.\n";
        }
        else // two numbers were read, but they are not a valid room
        {
            cout << "That is not a valid starting room.\n";
        }

        cout << "Player enter your coordinates floor and room (e.g., 1 1 for Floor 1, Room 1): ";
        cin >> chosenfloor >> chosenroom;
    }

    //  now real game state change
    playerFloor = chosenfloor;
    playerRoom = chosenroom;

    
    // actual simulation loop
    commands();
   bool gameover = false;
    while (!gameover)
    {
    renderDashboard(playerFloor, playerRoom, energy, time, score, inventory, inventoryCount, emergencyTripsLeft);
    renderRoomDetails(playerFloor, playerRoom, roomEntities, entityCounts[playerFloor - 1][playerRoom - 1]);  
    
       
       char command[MAX_NAME_LEN];
        cout <<"Enter command : ";
         cin >> setw(MAX_NAME_LEN) >> command;


       if (!cin) //for invalid input
      break;
      if(stringEquals(command,"quit"))
      break;
      
      else if(stringEquals(command,"help"))
      {
      cout << " help chosen \n";
      commands();
      }

      else if(stringEquals(command,"inspect"))
      {
        handleInspectCommand(playerFloor,playerRoom,energy,time,roomEntities, entityCounts[playerFloor - 1][playerRoom - 1],objectives,score);
    
      }

      else if(stringEquals(command,"map"))
      {
  
      renderAsciiBuilding(playerFloor,playerRoom);
      }

      else if(stringEquals(command,"load"))
      {
      cout << " load chosen \n";
      }

      else if(stringEquals(command,"collect"))
      {
        char symbol;
         if (!(cin >> symbol)) 
         {
           break;
         }
        bool collected =  handleCollectCommand(symbol,playerFloor,playerRoom,energy,time,score,roomEntities,
          entityCounts[playerFloor-1][playerRoom-1],inventory,inventoryCount,objectives);
        if (collected && symbol == ENT_EMERGENCY_CARD) 
        {
         emergencyTripsLeft = EMERGENCY_TRIPS;   

      
      }

      else if(stringEquals(command,"move"))
      {
      cin >> chosenfloor >> chosenroom;
      if (cin.eof()) // no input and no chance of future input (the file ended)
        {
            break;
        }
      if (!cin) // letters were typed (cin switched itself off)
        {
            cin.clear();              // switches cin back on
            cin.ignore(1000, '\n');   // throws away the rest of the bad line
            cout << "Please type two numbers.\n";
        }
        else // two numbers were read, so try the move
        {
          handleMoveCommand(chosenfloor, chosenroom, playerFloor, playerRoom, energy, time, horizontalConn, inventory, inventoryCount, emergencyTripsLeft,objectives[OBJ_LIFT2_ACTIVE]);
        }
      }

      else if(stringEquals(command,"use"))
      {
      cout << " use chosen";
      }

      else if(stringEquals(command,"unlock"))
      {
      cout << " unlock chosen";
      }

      else if(stringEquals(command,"board"))
      {
      cout << " board chosen";
      }

      else if(stringEquals(command,"save"))
      {
      cout << " save chosen";
      }

      else if(stringEquals(command,"status"))
      {
      renderObjectivesChecklist(objectives);
      }

      else
      {
        cin.ignore(10000,'\n');
       cout << "Invalid command. Type 'help' to see the list of available commands.\n";
      }
      
     
     
     
     
     
    }
        
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


    

bool handleInspectCommand(int currentFloor, int currentRoom, int& energy, int& time,const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
int entityCount,bool objectives[NUM_OBJECTIVES], int& score)
    {
      if ( currentFloor <= 0 || currentFloor > NUM_FLOORS || currentRoom <= 0 || currentRoom > ROOMS_PER_FLOOR)
      return false;
      if( entityCount < 0 || entityCount > MAX_ENTITIES_PER_ROOM)
      return false ;
      applyResourceDelta(energy,time,COST_INSPECT_ENERGY, COST_INSPECT_TIME);
      for(int i = 0 ; i <= entityCount-1 ; i++)
      {
        char symbol = roomEntities[currentFloor-1][currentRoom-1][i];
        cout << symbol <<" - " << getEntityName(symbol) << endl;
        if (symbol == ENT_CLUE_4 && !objectives[OBJ_CLUE_4])
        {
          objectives[OBJ_CLUE_4] = true ;
          applyScoreDelta(score,SCORE_CLUE_FOUND);
          cout << "you found clue digit 4  \n";
        }
        if (symbol == ENT_CLUE_2 && !(objectives[OBJ_CLUE_2]))
        {
          objectives[OBJ_CLUE_2] = true ;
          applyScoreDelta(score,SCORE_CLUE_FOUND);
          cout << "you found clue digit 2  \n";
        }
        if (symbol == ENT_CLUE_7 && !objectives[OBJ_CLUE_7])
        {
          objectives[OBJ_CLUE_7] = true ;
          applyScoreDelta(score,SCORE_CLUE_FOUND);
          cout << "you found clue digit 7  \n ";
        }
      }
        if(entityCount==0)
        cout << "nothing hhere \n";
        return true;
      
      

     
    
    
    
    
    
    
    
    
      
    }

bool handleCollectCommand(char itemSymbol, int currentFloor, int currentRoom,int& energy, int& time, int& score,char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
 int& entityCount,char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,bool objectives[NUM_OBJECTIVES])
 {
  bool found = false ;
    if ( currentFloor < 1|| currentFloor > NUM_FLOORS || currentRoom < 1 || currentRoom > ROOMS_PER_FLOOR)
      return false;
    for ( int i = 0 ; i<entityCount ; i++)
    {
    if ( itemSymbol==roomEntities[currentFloor-1][currentRoom-1][i])
    {
    found = true;
    break;
    }
  }

   if (found==false)
  {
    cout <<"the item was not found in the room";
   return false;
  }
  if( itemSymbol == ENT_CAT || itemSymbol == ENT_PASSENGER || itemSymbol == ENT_CONTROL_PANEL ||
       itemSymbol == ENT_CABINET_TRAIN_KEY || itemSymbol == ENT_CLUE_2 || itemSymbol == ENT_CLUE_4 ||  itemSymbol == ENT_CLUE_7)
       {
        cout << "The item is fixed";
        return false;
             
      }
  else if (itemSymbol == ENT_ENERGY_PACK )
    {
      cout <<"the item is an Instant bonus";
      removefromroom(currentFloor,currentRoom,roomEntities,entityCount,itemSymbol);
      applyResourceDelta(energy, time, BONUS_ENERGY_PACK, 0 );
      return true;
    }
  else if (itemSymbol == ENT_EMERGENCY_TOOLKIT )
    {
       cout <<"the item is an Instant bonus";
      removefromroom(currentFloor,currentRoom,roomEntities,entityCount,itemSymbol);
      applyResourceDelta(energy, time, BONUS_EMERGENCY_TOOLKIT, 0 );
      return true;
    }
  else if (itemSymbol == ENT_OBSERVATION_TOKEN )
    {
       cout <<"the item is an Instant bonus";
       removefromroom(currentFloor,currentRoom,roomEntities,entityCount,itemSymbol);
      applyResourceDelta(energy, time, 0, BONUS_OBSERVATION_TOKEN );
      return true;
    }
  else
    {
     if (addItem(inventory,inventoryCount,itemSymbol))
    {
        cout << " The item is collected";
      removefromroom(currentFloor,currentRoom,roomEntities,entityCount, itemSymbol);
      applyResourceDelta(energy,time,COST_ITEM_PICKUP_ENERGY, COST_ITEM_PICKUP_TIME);
      if (itemSymbol== ENT_MASTER_KEY)
      {
        objectives[OBJ_MASTER_KEY]=true;
        applyScoreDelta(score,SCORE_KEY_COLLECT);
      }
      else if(itemSymbol== ENT_FUSE)
      {
        objectives[OBJ_FUSE_COLLECTED]=true;
      }
      else if (itemSymbol== ENT_LIFT_PASS)
      {
        objectives[OBJ_LIFT_PASS]=true;
        applyScoreDelta(score,SCORE_LIFT_PASS);
      }
      else if (itemSymbol== ENT_CAT_CARRIER)
      {
         objectives[OBJ_CAT_CARRIER] = true ;
      }
    }
     else 
       {
        cout <<"no space in the  inventory ";
        return false ;
       }
     
       }
    
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



