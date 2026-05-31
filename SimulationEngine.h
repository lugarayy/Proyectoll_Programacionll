//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_SIMULATIONENGINE_H
#define PROYECTOLL_PROGRAMACIONLL_SIMULATIONENGINE_H
#include "Logger.h"
#include "Station.h"
#include "Character.h"

struct SimulationSummary {
    SimulationSummary() : turnsTaken(0), success(false) {}
    int turnsTaken;
    bool success;
    std::string finalState;
};

class SimulationEngine {
public:
    SimulationEngine(Station* station, Character* character, int maxTurns);
    void run();
    bool isSimulationOver() const;
    const SimulationSummary& getSummary() const;
    ~SimulationEngine();
private:
    void updateSummary(int turnsTaken, const std::string& finalState, bool success);
    Character* currentCharacter;
    Station* currentStation;
    int currentTurns;
    int maxTurns;
    SimulationSummary summary;
};


#endif //PROYECTOLL_PROGRAMACIONLL_SIMULATIONENGINE_H