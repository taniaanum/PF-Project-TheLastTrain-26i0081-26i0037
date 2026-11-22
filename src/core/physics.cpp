#include "physics.h"
#include "util.h"
#include "switches.h"
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
         if ( gap_type == CONN_WINDOW || gap_type == CONN_DOOR || gap_type == CONN_LOCKED_DOOR )
            {
            
                outConnType = gap_type ;
                return true ;
            }
        
     }
       return false ;
    }
    // stairs
    int lower = 0 ;
    int upper = 0 ;
    if ( fromF > toF)
    { lower = toF ;
      upper = fromF ;
    }
    if ( fromF < toF )
      { lower = fromF ;
        upper = toF ;
      }
    if (fromR == 1 && toR==1)
     {

      if ((lower == 1 && upper == 2 ) || (lower == 2 && upper == 3) || (lower == 4 && upper == 5))
      {
        outConnType = CONN_STAIRS;
          return true ;
     }
    return false ;
     }
     // lift 1 
     if ( (fromR == 2 && toR==2) || (fromR == 3 && toR==3) || (fromR == 2 && toR== 3) || (fromR == 3 && toR== 2) )
       if ( canUseLift1(fromF,toF) )
        {
            outConnType = CONN_LIFT1 ;
            return true ;
        }
         
     // lift 2
   if (fromR == 4 && toR == 4 && (fromF == 2 || fromF == 4 || fromF == 5) && (toF == 2 || toF == 4 || toF == 5))
        {
             outConnType = CONN_LIFT2 ;
                return true ;
        }
        
     return false;
}
                             
            
                         

bool canTraverse(int targetFloor, int targetRoom, char connType,
                 const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                 int emergencyTripsLeft, bool lift2Operational){
                        return true;
                 }


void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime)
{
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
