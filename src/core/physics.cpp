#include "physics.h"
#include "util.h"
#include <iostream>
using namespace std;

// Movement validation and resource adjustments without structures

bool isDirectlyConnected(int fromF, int fromR, int toF, int toR,const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
char& outConnType){
    outConnType = CONN_NONE ;
    // validation 
    if (  fromF > NUM_FLOORS || fromF < 1)
     return false;
    if (  toF > NUM_FLOORS || toF < 1)
     return false;
    if ( fromR > ROOMS_PER_FLOOR || fromR < 1 )
     return false ;
    if ( toR > ROOMS_PER_FLOOR || toR < 1 )
     return false ;
    if ( fromF == toF && fromR == toR )
     return false ;
     // connection between rooms on same floor 
    if ( fromF == toF)
    {
      // rooms are neighbours 
     if ( fromR-toR == 1 || toR - fromR == 1 )
     { int left = 0 ;
        if ( fromR < toR )
         left = fromR ;
        else
         left = toR ;
       
       char gap_type = horizontalConn[fromF-1][left-1];
     }
       



    }
         

                             
            
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
