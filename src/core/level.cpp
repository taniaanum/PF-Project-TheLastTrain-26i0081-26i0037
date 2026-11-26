#include "level.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
// Modular implementation using primitive arrays for map parsing and verification

static void placeItem(char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                      int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR],
                      int floor, int room, char symbol) {

    int n = entityCounts[floor-1][room-1];

    if(n >= MAX_ENTITIES_PER_ROOM)
    {
        cerr << "Error: Cannot place more entities in room " << room << " on floor " << floor << endl;
        return;
    }
        roomEntities[floor-1][room-1][n] = symbol;
        entityCounts[floor-1][room-1] = n + 1;
}



bool loadBuildingMap(const char* filename,
                     char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                     char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                     int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){
    for(int f = 0; f < NUM_FLOORS; ++f)
    {
        for(int r = 0; r < ROOMS_PER_FLOOR; ++r)
        {
            entityCounts[f][r] = 0;
            for(int s = 0; s < MAX_ENTITIES_PER_ROOM; ++s)
                roomEntities[f][r][s] = ENT_NONE;
        }
    }
    // Floor 5
    horizontalConn[4][0] = CONN_DOOR;
    horizontalConn[4][1] = CONN_DOOR;
    horizontalConn[4][2] = CONN_WINDOW;

    // Floor 4
    horizontalConn[3][0] = CONN_WINDOW;
    horizontalConn[3][1] = CONN_SOLID_WALL;
    horizontalConn[3][2] = CONN_DOOR;

    // Floor 3
    horizontalConn[2][0] = CONN_LOCKED_DOOR;
    horizontalConn[2][1] = CONN_WINDOW;
    horizontalConn[2][2] = CONN_DOOR;

    // Floor 2
    horizontalConn[1][0] = CONN_DOOR;
    horizontalConn[1][1] = CONN_LIFT1;
    horizontalConn[1][2] = CONN_DOOR;

    // Floor 1
    horizontalConn[0][0] = CONN_WINDOW;
    horizontalConn[0][1] = CONN_LIFT1;
    horizontalConn[0][2] = CONN_DOOR;

    placeItem(roomEntities, entityCounts, 1, 2, ENT_MASTER_KEY);
    placeItem(roomEntities, entityCounts, 1, 4, ENT_ENERGY_PACK);
    placeItem(roomEntities, entityCounts, 2, 3, ENT_EMERGENCY_TOOLKIT);
    placeItem(roomEntities, entityCounts, 3, 2, ENT_CLUE_4);
    placeItem(roomEntities, entityCounts, 3, 2, ENT_FUSE);
    placeItem(roomEntities, entityCounts, 3, 3, ENT_CAT);
    placeItem(roomEntities, entityCounts, 3, 4, ENT_CONTROL_PANEL);
    placeItem(roomEntities, entityCounts, 3, 4, ENT_LIFT_PASS);
    placeItem(roomEntities, entityCounts, 4, 1, ENT_PASSENGER);
    placeItem(roomEntities, entityCounts, 4, 2, ENT_MEDICAL_KIT);
    placeItem(roomEntities, entityCounts, 4, 2, ENT_EMERGENCY_CARD);
    placeItem(roomEntities, entityCounts, 4, 3, ENT_CLUE_2);
    placeItem(roomEntities, entityCounts, 5, 1, ENT_CLUE_7);
    placeItem(roomEntities, entityCounts, 5, 1, ENT_CABINET_TRAIN_KEY);
    placeItem(roomEntities, entityCounts, 5, 3, ENT_CAT_CARRIER);
    placeItem(roomEntities, entityCounts, 5, 4, ENT_OBSERVATION_TOKEN);

    return true;
}

bool loadInitialState(const char* filename,
                      int& playerFloor, int& playerRoom,
                      int& energy, int& time, int& score,
                      char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                      bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft){
    ifstream initialStateFile(filename);
    if (!initialStateFile) {
        return false;
    }

    bool foundEnergy = false, foundTime = false;

    char word[MAX_NAME_LEN];
    while (initialStateFile >> setw(MAX_NAME_LEN) >> word)
    {
        if (stringEquals(word, "INITIAL_ENERGY:"))
        {
            if(initialStateFile >> energy)
                foundEnergy = true;
        }
        else if (stringEquals(word, "INITIAL_TIME:"))
        {
            if(initialStateFile >> time)
                foundTime = true;
        }
        else if (stringEquals(word, "INITIAL_SCORE:"))
            initialStateFile >> score;
    }

    if (!foundEnergy || !foundTime)
        return false;
    if (energy <= 0 || energy > MAX_ENERGY)
        return false;
    if (time <= 0 || time > MAX_TIME)
        return false;

    playerFloor = 1;
    playerRoom = 1;
    inventoryCount = 0;
    emergencyTripsLeft = 0;
    
    for(int i=0; i <MAX_INVENTORY_CAPACITY; ++i)
        inventory[i] = ENT_NONE;

    for(int i=0; i<NUM_OBJECTIVES; ++i)
        objectives[i] = false;
    
    return true;
}

bool validateStartingRoom(int startFloor, int startRoom,
                          const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){
    if (startFloor < 1 || startFloor > NUM_FLOORS)
        return false;
    if (startRoom < 1 || startRoom > ROOMS_PER_FLOOR)
        return false;
    return true;
}

const char* getEntityName(char entitySymbol){
    switch (entitySymbol) {
        case ENT_MASTER_KEY:
            return "Master Key";
        case ENT_ENERGY_PACK:
            return "Energy Pack";
        case ENT_EMERGENCY_TOOLKIT:
            return "Emergency Toolkit";
        case ENT_CLUE_4:
            return "Clue 4";
        case ENT_CLUE_2:
            return "Clue 2";
        case ENT_CLUE_7:
            return "Clue 7";
        case ENT_FUSE:
            return "Fuse";
        case ENT_CAT:
            return "Cat";
        case ENT_CONTROL_PANEL:
            return "Control Panel";
        case ENT_LIFT_PASS:
            return "Lift Pass";
        case ENT_PASSENGER:
            return "Injured Passenger";
        case ENT_MEDICAL_KIT:
            return "Medical Kit";
        case ENT_EMERGENCY_CARD:
            return "Emergency Access Card";
        case ENT_CABINET_TRAIN_KEY:
            return "Cabinet Train Key";
        case ENT_CAT_CARRIER:
            return "Cat Carrier";
        case ENT_OBSERVATION_TOKEN:
            return "Observation Token";
        default:
            return "Unknown";
    }
}