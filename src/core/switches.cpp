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
bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                             bool objectives[NUM_OBJECTIVES], int& score){
    return true;
}
bool verifyCabinetCode(const char* enteredCode, const bool objectives[NUM_OBJECTIVES]){
    return true;
}


// Door lock mechanics, lifts, and cabinet verification without structures
