#include "switches.h"
#include "util.h"
#include <iostream>
using namespace std;

bool canUseLift1(int fromFloor, int toFloor){
    return true;
}
bool canUseLift2(int fromFloor, int toFloor, bool lift2Operational, int emergencyTripsLeft){
    return true;
}

bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount){
    return true;
}
bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                             bool objectives[NUM_OBJECTIVES], int& score){
    return true;
}
bool verifyCabinetCode(const char* enteredCode, const bool objectives[NUM_OBJECTIVES]){
    return true;
}


// Door lock mechanics, lifts, and cabinet verification without structures
