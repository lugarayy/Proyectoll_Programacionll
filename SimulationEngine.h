//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_SIMULATIONENGINE_H
#define PROYECTOLL_PROGRAMACIONLL_SIMULATIONENGINE_H
#include "Station.h"
#include "Character.h"

struct SimulationSummary {
    SimulationSummary() : turnsTaken(0), success(false) {}
    int turnsTaken;
    bool success;
    std::string finalState;
    std::vector<std::string> eventLog;
};

class SimulationEngine {
public:
    SimulationEngine(Station *station, Character *character, int maxTurns, int escapeRoomId);
    void run();
    bool isSimulationOver() const;
    const SimulationSummary& getSummary() const;
    ~SimulationEngine();
private:
    void placeCharacterIfNeeded();
    void processCombat(Room* room);
    void collectItems(Room* room);
    void useEmergencyItems();
    bool checkEscape(Room* room);
    void moveToNextRoom(Room* room);
    bool simulationEnd();
    void updateSummary(int turnsTaken, const std::string& finalState, bool success);
    void logEvent(const std::string& message);
    void printTurnStats();
    Character* currentCharacter;
    Station* currentStation;
    int currentTurns;
    int maxTurns;
    int escapeRoomId;
    bool escaped;
    SimulationSummary summary;
};


#endif //PROYECTOLL_PROGRAMACIONLL_SIMULATIONENGINE_H