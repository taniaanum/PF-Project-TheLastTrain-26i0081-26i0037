#include "switches.h"
#include "util.h"
#include "physics.h"
#include <iostream>
using namespace std;

bool canUseLift1(int fromFloor, int toFloor){
    if (fromFloor==1 && toFloor==2) return true;
    if (fromFloor==2 && toFloor==1) return true;
    return false;
}
bool canUseLift2(int fromFloor, int toFloor, bool lift2Operational, int emergencyTripsLeft){
    if(lift2Operational || emergencyTripsLeft>0) 
     {
        if (fromFloor==2 && toFloor==4) return true;
        if (fromFloor==4 && toFloor==2) return true;
        if (fromFloor==2 && toFloor==5) return true;
        if (fromFloor==5 && toFloor==2) return true;
        if (fromFloor==4 && toFloor==5) return true;
        if (fromFloor==5 && toFloor==4) return true;

     }
    return false;
}

bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount){
   
   if(hasItem(inventory, inventoryCount, ENT_MASTER_KEY))
    return true;
    return false ; 
   
   
   
}
bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,bool objectives[NUM_OBJECTIVES], int& score)
{
 
    
    if(!(hasItem(inventory,inventoryCount,ENT_FUSE)))
    {
    cout <<"the fuse is not in the inventory \n";
   return false;
    }

 if (objectives[OBJ_FUSE_INSTALLED])
 {
    cout << "fuse is already installed \n";
    return false;
 }
  removeItem(inventory,inventoryCount,ENT_FUSE);
  objectives[OBJ_FUSE_INSTALLED]=true;
  objectives[OBJ_LIFT2_ACTIVE]=true;
  applyScoreDelta(score,SCORE_INSTALL_FUSE);
  return true ;
}


bool verifyCabinetCode(const char* enteredCode, const bool objectives[NUM_OBJECTIVES])
{
    if(!(objectives[OBJ_CLUE_2] && objectives[OBJ_CLUE_4] &&objectives[OBJ_CLUE_7]))
    {
        cout<<"The clues were not found \n";
        return false;
    }

    else if ( !(stringEquals(enteredCode,"427")))
       {
        cout << "The code is incorrect";
        return false;
       }
    else 
    return true ;
    
}


// Door lock mechanics, lifts, and cabinet verification without structures
