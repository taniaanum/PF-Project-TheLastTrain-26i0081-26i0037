#include "logger.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
// File persistence for savegame.txt and game_summary.txt using primitive variables
// Function 1: save the whole game to a text file
bool saveGameStateToFile(const char* filename,
                         int playerFloor, int playerRoom,
                         int energy, int time, int score,
                         const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                         const bool objectives[NUM_OBJECTIVES], int emergencyTripsLeft,
                         const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                         const int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
{
    // Chunk 1: open the file and check it opened
    ofstream saveFile(filename);
    if (!saveFile.is_open())
    {
        cout << "Error: Could not open " << filename << " for writing.\n";
        return false;
    }

    // Chunk 2: tag, position, resources, trips
    saveFile << "LASTTRAIN_SAVE" << endl;
    saveFile << playerFloor << " " << playerRoom << endl;
    saveFile << energy << " " << time << " " << score << endl;
    saveFile << emergencyTripsLeft << endl;

    // Chunk 3: inventory (count, then each symbol after a space)
    saveFile << inventoryCount;
    for (int i = 0; i < inventoryCount; ++i)   
        saveFile << " " << inventory[i];
    saveFile << endl;

    // Chunk 4: the 16 objective flags
    for (int i = 0; i < NUM_OBJECTIVES; i++)
        saveFile << (objectives[i] ? "1" : "0") << " ";
    saveFile << endl;

    // Chunk 5: the 20 rooms (count, then symbols after a space)
    for (int f = 0; f < NUM_FLOORS; f++)
    {
        for (int r = 0; r < ROOMS_PER_FLOOR; r++)
        {
            saveFile << entityCounts[f][r];
            for (int s = 0; s < entityCounts[f][r]; s++)
                saveFile << " " << roomEntities[f][r][s];
            saveFile << endl;
        }
    }

    return true;
}

// Function 2: load the game from a text file
// Reads into temporaries first; the real game changes only if the whole file is valid.
bool loadGameStateFromFile(const char* filename,
                           int& playerFloor, int& playerRoom,
                           int& energy, int& time, int& score,
                           char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                           bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft,
                           char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                           int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
{
    // Chunk 1: open the file, check the tag word
    ifstream loadFile(filename);
    if(!loadFile)
    {
        cout << "No valid saved game found." << endl;
        return false;
    }
    char tag[MAX_NAME_LEN];
    if(!(loadFile >> setw(MAX_NAME_LEN) >> tag))
        return false;

    if(!stringEquals(tag, "LASTTRAIN_SAVE"))                                
        return false;

    // Chunk 2: temporaries and the seven numbers
    int tFloor=0, tRoom=0, tEnergy=0, tTime=0, tScore=0, tInventoryCount=0, tEmergencyTripsLeft=0;
    char tInventory[MAX_INVENTORY_CAPACITY];
    bool tObjectives[NUM_OBJECTIVES];
    char tRoomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM];
    int tEntityCounts[NUM_FLOORS][ROOMS_PER_FLOOR];

    if(!(loadFile >> tFloor >> tRoom >> tEnergy >> tTime >> tScore >> tEmergencyTripsLeft >> tInventoryCount))
        return false;

    // Chunk 3: range checks
    if(tFloor < 1 || tFloor > NUM_FLOORS)
        return false;
    if(tRoom < 1 || tRoom > ROOMS_PER_FLOOR)
        return false;
    if(tEnergy < 0 || tEnergy > MAX_ENERGY)
        return false;
    if(tTime < 0 || tTime > MAX_TIME)
        return false;
    if(tScore < 0)
        return false;
    if(tEmergencyTripsLeft < 0 || tEmergencyTripsLeft > EMERGENCY_TRIPS)
        return false;
    if(tInventoryCount < 0 || tInventoryCount > MAX_INVENTORY_CAPACITY)
        return false;

    // Chunk 4: inventory symbols
    for(int i=0; i<MAX_INVENTORY_CAPACITY; i++)
        tInventory[i] = ENT_NONE;
    for(int i=0; i<tInventoryCount; i++)
    {
        if(!(loadFile >> tInventory[i]))
            return false;
    }

    // Chunk 5: the 16 objective flags
    for(int i=0; i<NUM_OBJECTIVES; i++)
    {
        int flag=0;
        if(!(loadFile >> flag))
            return false;
        if(flag != 0 && flag != 1)
            return false;
        tObjectives[i] = (flag == 1);
    }

    // Chunk 6: the 20 rooms (count, then symbols after a space)
    for(int f=0; f<NUM_FLOORS; f++)
    {
        for(int r=0; r<ROOMS_PER_FLOOR; r++)
        {
            int count=0;
            if(!(loadFile >> count))
                return false;
            if(count < 0 || count > MAX_ENTITIES_PER_ROOM)
                return false;
            tEntityCounts[f][r] = count;
            for(int s=0; s<MAX_ENTITIES_PER_ROOM; s++)
                tRoomEntities[f][r][s] = ENT_NONE;
            for(int s=0; s<count; s++)
            {
                if(!(loadFile >> tRoomEntities[f][r][s]))
                    return false;
            }
        }
    }

    // Chunk 7: everything is valid, copy into the real game
    playerFloor = tFloor;
    playerRoom = tRoom;
    energy = tEnergy;
    time = tTime;
    score = tScore;
    emergencyTripsLeft = tEmergencyTripsLeft;
    inventoryCount = tInventoryCount;
    for(int i=0; i<MAX_INVENTORY_CAPACITY; i++)
        inventory[i] = tInventory[i];
    for(int i=0; i<NUM_OBJECTIVES; i++)
        objectives[i] = tObjectives[i];
    for(int f=0; f<NUM_FLOORS; f++)
    {
        for(int r=0; r<ROOMS_PER_FLOOR; r++)
        {
            entityCounts[f][r] = tEntityCounts[f][r];
            for(int s=0; s<MAX_ENTITIES_PER_ROOM; s++)
                roomEntities[f][r][s] = tRoomEntities[f][r][s];
        }
    }
    return true;                        
}

// Function 3: write the final report (game_summary.txt)
void writeGameSummaryReport(const char* filename,
                            int score, int remainingEnergy, int remainingTime,
                            const bool objectives[NUM_OBJECTIVES], bool victory)
{
    // Chunk 1: open the file
    ofstream summaryFile(filename);
    if (!summaryFile.is_open())
    {
        cout << "Error: Could not write " << filename << endl;
        return;
    }

    // Chunk 2: title, result, reason
    summaryFile << "THE LAST TRAIN - GAME SUMMARY" << endl;
    if (victory)
    {
        summaryFile << "Result: VICTORY" << endl;
        summaryFile << "Reason: The train was boarded with the passenger and the cat" << endl;
    }
    else
    {
        summaryFile << "Result: DEFEAT" << endl;
        if(remainingEnergy <= 0)
            summaryFile << "Reason: Energy ran out" << endl;
        else if(remainingTime <= 0)
            summaryFile << "Reason: Time ran out" << endl;
        else
            summaryFile << "Reason: The train left without everyone" << endl;
    }

    // Chunk 3: score, energy, time
    summaryFile << "Final Score: " << score << endl;
    summaryFile << "Energy left: " << remainingEnergy << endl;
    summaryFile << "Time left: " << remainingTime << endl;

    // Chunk 4: the 16 objectives with YES or NO
    const char* objectiveNames[NUM_OBJECTIVES] = 
    {
        "Master Key Collected",
        "Clue 4 Collected",
        "Clue 2 Collected",
        "Clue 7 Collected",
        "Cabinet Unlocked",
        "Train Key Collected",
        "Fuse Collected",
        "Fuse Installed",
        "Lift Pass Collected",
        "Lift 2 Activated",
        "Passenger Rescued",
        "Cat Carrier Collected",
        "Cat Secured in Carrier",
        "Train Prepared for Departure",
        "Mission Won",
        "Mission Failed"
    };
    
    summaryFile << "Objectives:" << endl;
    for (int i = 0; i < NUM_OBJECTIVES; ++i)
        summaryFile << " - " << objectiveNames[i] << ": " << (objectives[i] ? "YES" : "NO") << endl;

    // Chunk 5: the session audit
    const int objectiveScores[NUM_OBJECTIVES] = 
    {
        SCORE_KEY_COLLECT,
        SCORE_CLUE_FOUND,
        SCORE_CLUE_FOUND,
        SCORE_CLUE_FOUND,
        SCORE_CABINET_UNLOCK,
        SCORE_TRAIN_KEY,
        0,
        SCORE_INSTALL_FUSE,
        SCORE_LIFT_PASS,
        0,
        SCORE_RESCUE_PASSENGER,
        0,
        SCORE_SECURE_CAT,
        SCORE_PREPARE_TRAIN,
        SCORE_MISSION_VICTORY,
        0
    };

    int recomputedScore = 0;
    int completed=0;
    for (int i = 0; i < NUM_OBJECTIVES; ++i)
    {
        if (objectives[i])
        {
            recomputedScore += objectiveScores[i];
            if(i < 14)
                completed++;
        }
    }

    summaryFile << "Session Audit: " << endl;
    summaryFile << "Objectives Completed: " << completed << " of 14" << endl;
    summaryFile << "Recomputed Score: " << recomputedScore << endl;
    if(recomputedScore == score)
        summaryFile << "Score check: MATCH" << endl;
    else
        summaryFile << "Score check: MISMATCH" << endl;

}