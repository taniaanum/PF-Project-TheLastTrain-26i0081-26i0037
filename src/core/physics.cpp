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
deltaEnergy = clampInt(deltaEnergy, 0 , MAX_ENERGY);
deltaTime = clampInt(deltaTime, 0 , MAX_TIME);
energy += deltaEnergy;
time += deltaTime;  

}
void applyScoreDelta(int& score, int deltaScore){
score += deltaScore;

}


bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol){
    for(int i=0; i<inventoryCount; i++){
        if(inventory[i]==itemSymbol) return true;
    }
    return false;
}


bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    if (inventoryCount >= MAX_INVENTORY_CAPACITY) return false;
    inventory[inventoryCount] = itemSymbol;
    inventoryCount++;
    return true;
}




bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol)
{
    int pos = -1;
     for(int i=0; i<inventoryCount; i++){
        if(inventory[i]==itemSymbol) 
        pos = i;
        break;
    }
   if(pos==-1) return false;
    for(int i=pos; i<inventoryCount-1; i++){
        inventory[i] = inventory[i+1];
    }
    inventoryCount--;
    return true;
}
