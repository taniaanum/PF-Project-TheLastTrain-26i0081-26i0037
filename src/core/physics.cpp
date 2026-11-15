#include "physics.h"
#include "util.h"
#include <iostream>
using namespace std;
// Movement validation and resource adjustments without structures

bool isDirectlyConnected(int fromF, int fromR, int toF, int toR,
                         const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                         char& outConnType){
                            return true;
                         }

bool canTraverse(int targetFloor, int targetRoom, char connType,
                 const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                 int emergencyTripsLeft, bool lift2Operational){
                        return true;
                 }

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime){


}
void applyScoreDelta(int& score, int deltaScore){


}

bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol){
    return true;
}
bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    return true;
}
bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    return true;
}
