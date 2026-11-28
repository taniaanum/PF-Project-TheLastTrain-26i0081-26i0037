#include "viewer_iface.h"
#include "util.h"
#include <iostream>
#include "level.h"
using namespace std;
// Terminal UI and dashboard rendering using primitive parameters


void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score,
                     const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                     int emergencyTripsLeft)
{
    cout << "Location: F" << playerFloor << "-R" << playerRoom << endl;
    cout << "Energy: " << energy << "/" << MAX_ENERGY << "   Time: " << time << "/" << MAX_TIME << "   Score: " << score << endl;

    if (inventoryCount == 0) 
        cout << "Inventory: empty" << endl;
    else
    {
        cout << "Inventory: ";
        for (int i = 0; i < inventoryCount; ++i) 
            cout << " [" << inventory[i] << "] " << getEntityName(inventory[i]);
        cout << endl;
    }

    cout << "Emergency Trips Left: " << emergencyTripsLeft << endl;
}

void renderRoomDetails(int floor, int room,
                       const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                       int entityCount)
{
    if(floor < 1 || floor > NUM_FLOORS)
    {
        cout << "Invalid floor" << endl;
        return;
    }
    if(room < 1 || room > ROOMS_PER_FLOOR)
    {
        cout << "Invalid room" << endl;
        return;
    }

    int shown=0;
    for(int i=0; i<entityCount; i++)
    {
        char symbol = roomEntities[floor-1][room-1][i];
        if(symbol == ENT_CLUE_4 || symbol == ENT_CLUE_2 || symbol == ENT_CLUE_7)
            continue;
        cout << "  [" << symbol << "] " << getEntityName(symbol) << endl;
        shown++;
    }

    if(shown == 0)
        cout << " Nothing in plain sight" << endl;
}

void renderAsciiBuilding(int playerFloor, int playerRoom)
{
    for(int f=NUM_FLOORS; f>=1; f--)
    {
        for(int r=1; r<=ROOMS_PER_FLOOR; r++)
        {
            if(f == playerFloor && r == playerRoom)
                cout << "*F" << f << "-R" << r << "*  ";
            else
                cout << " F" << f << "-R" << r << "   ";
        }
        cout << endl;
    }
}
void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES])
{
    const char* objectiveLabels[NUM_OBJECTIVES] = {
"Master Key collected",
        "Clue digit 4 found",
        "Clue digit 2 found",
        "Clue digit 7 found",
        "Cabinet unlocked",
        "Train Key acquired",
        "Fuse collected",
        "Fuse installed",
        "Lift Pass collected",
        "Lift 2 activated",
        "Passenger rescued",
        "Cat Carrier collected",
        "Cat secured",
        "Train prepared",
        "Mission won",
        "Mission failed"
    };

    for(int i = 0; i < NUM_OBJECTIVES; ++i)
        cout  << (objectives[i] ? "[x] " : "[ ] ")  << objectiveLabels[i] << endl;
}
