//
// Created by Jose on 30/5/2026.
//

#include "SimulationEngine.h"
#include "Threat.h"
#include <cstdlib>
#include <ctime>
#include <string>

SimulationEngine::SimulationEngine(Station* station, Character* character, int maxTurns)
    : currentCharacter(character), currentStation(station), currentTurns(0), maxTurns(maxTurns) {
    updateSummary(currentTurns, "Simulation initialized", false);
}

void SimulationEngine::run() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    while (!isSimulationOver()) {
        Logger::getInstance().log("Turn " + std::to_string(currentTurns + 1) + " begins.");

        if (currentCharacter != nullptr && currentStation != nullptr) {
            if (currentCharacter->getCurrentRoom() == nullptr) {
                const auto rooms = currentStation->getRooms();
                if (!rooms.empty()) {
                    currentCharacter->move(rooms.front());
                    Logger::getInstance().log("Character moved to room: " + rooms.front()->getName());
                }
            }

            Room* room = currentCharacter->getCurrentRoom();
            if (room != nullptr) {
                const auto threats = room->getThreats();
                const int dodgePercent = 30;
                for (Threat* threat : threats) {
                    if (threat == nullptr) {
                        continue;
                    }
                    threat->interact();
                    threat->activate();

                    const int roll = std::rand() % 100;
                    if (roll < dodgePercent) {
                        Logger::getInstance().log("Combat: " + currentCharacter->getName() + " dodged " + threat->getName() + ".");
                        continue;
                    }

                    currentCharacter->takeDamage(threat->getDamage());
                    Logger::getInstance().log("Combat: " + threat->getName() + " dealt " + std::to_string(threat->getDamage()) + " damage.");
                }
            }
        }

        currentTurns++;
    }

    if (currentCharacter == nullptr) {
        updateSummary(currentTurns, "Simulation ended: no character", false);
        return;
    }

    if (!currentCharacter->isAlive()) {
        updateSummary(currentTurns, "Simulation ended: character defeated", false);
        return;
    }

    if (currentStation == nullptr) {
        updateSummary(currentTurns, "Simulation ended: no station", false);
        return;
    }

    if (currentStation->getRooms().empty()) {
        updateSummary(currentTurns, "Simulation ended: no rooms", false);
        return;
    }

    if (currentTurns >= maxTurns) {
        updateSummary(currentTurns, "Simulation ended: max turns reached", true);
        return;
    }

    updateSummary(currentTurns, "Simulation ended", false);
}

bool SimulationEngine::isSimulationOver() const {
    if (currentCharacter == nullptr) {
        return true;
    }

    if (!currentCharacter->isAlive()) {
        return true;
    }

    if (currentStation == nullptr) {
        return true;
    }

    if (currentTurns >= maxTurns) {
        return true;
    }

    if (currentStation->getRooms().empty()) {
        return true;
    }

    return false;
}

SimulationEngine::~SimulationEngine() {
}

const SimulationSummary& SimulationEngine::getSummary() const {
    return summary;
}

void SimulationEngine::updateSummary(int turnsTaken, const std::string& finalState, bool success) {
    summary.turnsTaken = turnsTaken;
    summary.success = success;
    summary.finalState = finalState;
}
