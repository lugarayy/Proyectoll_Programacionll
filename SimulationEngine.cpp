//
// Created by Jose on 30/5/2026.
//

#include "SimulationEngine.h"
#include <cmath>
#include "Threat.h"
#include "OxygenTank.h"
#include "RepairKit.h"
#include "KeyCard.h"
#include <cstdlib>
#include <ctime>
#include <string>

SimulationEngine::SimulationEngine(Station* station, Character* character, int maxTurns, int escapeRoomId)
    : currentCharacter(character), currentStation(station), currentTurns(0), maxTurns(maxTurns),
      escapeRoomId(escapeRoomId), escaped(false) {
    updateSummary(currentTurns, "Simulation initialized", false);
}

void SimulationEngine::run() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    while (!isSimulationOver()) {
        logEvent("Turn " + std::to_string(currentTurns + 1) + " begins.");
        placeCharacterIfNeeded();
        Room* room = currentCharacter->getCurrentRoom();
        processCombat(room);
        if (simulationEnd()) {
            logEvent("Simulation ended.");
            break;
        }
        collectItems(room);
        useEmergencyItems();
        if (checkEscape(room)) break;
        moveToNextRoom(room);
        printTurnStats();
        currentTurns++;

    }
}

bool SimulationEngine::isSimulationOver() const {
    if (currentCharacter == nullptr) return true;
    if (!currentCharacter->isAlive()) return true;
    if (currentStation == nullptr) return true;
    if (currentTurns >= maxTurns) return true;
    if (currentStation->getRooms().empty()) return true;
    if (escaped) return true;
    return false;
}

SimulationEngine::~SimulationEngine() {}

const SimulationSummary& SimulationEngine::getSummary() const {
    return summary;
}

void SimulationEngine::updateSummary(int turnsTaken, const std::string& finalState, bool success) {
    summary.turnsTaken = turnsTaken;
    summary.success = success;
    summary.finalState = finalState;
}

void SimulationEngine::logEvent(const std::string& message) {
    Logger::getInstance().log(message);
    summary.eventLog.push_back(message);
}

void SimulationEngine::printTurnStats() {
    if (currentCharacter == nullptr) return;
    Room* room = currentCharacter->getCurrentRoom();
    std::string roomInfo = "N/A";
    if (room != nullptr) {
        roomInfo = room->getName() + " (ID:" + std::to_string(room->getId()) + ")";
    }
    logEvent("=== End of Turn " + std::to_string(currentTurns + 1) + " ===\n");
    logEvent("Room: " + roomInfo +
             " | HP: " + std::to_string(currentCharacter->getHealth()) +
             " | O2: " + std::to_string(currentCharacter->getOxygen()) +
             " | Inventory: " + std::to_string(currentCharacter->getInventory().getSize()) +
             "/" + std::to_string(currentCharacter->getInventory().getMaxCapacity()));
}

void SimulationEngine::placeCharacterIfNeeded() {
    if (currentCharacter != nullptr && currentStation != nullptr) {
        if (currentCharacter->getCurrentRoom() == nullptr) {
            const auto rooms = currentStation->getRooms();
            if (!rooms.empty()) {
                int start = std::rand() % rooms.size();
                while (rooms[start]->getId() == escapeRoomId) {
                    start = std::rand() % rooms.size();
                }
                currentCharacter->move(rooms[start]);
                logEvent("Character moved to room: " + rooms[start]->getName());
            }
        }
    }
}

    void SimulationEngine::processCombat(Room *room) {
        if (room != nullptr) {
            // Amenazas
            const auto threats = room->getThreats();
            const int dodgePercent = 30;
            for (Threat* threat : threats) {
                if (threat == nullptr) {
                    continue;
                }
                const int roll = std::rand() % 100;
                if (roll < dodgePercent) {
                    logEvent("Combat: " + currentCharacter->getName() + " dodged " + threat->getName() + ".");
                    continue;
                }
                if (threat->getType() == "Oxygen Leak") {
                    threat->activate(*currentCharacter);
                    logEvent("Combat: " + threat->getName() + " reduced oxygen by " + std::to_string(threat->getDamage()) + ".");
                }
                if (threat->getType()== "Defective Robot") {
                   threat->activate(*currentCharacter);
                    logEvent("Combat: " + threat->getName() + " dealt " + std::to_string(threat->getDamage()) + " damage.");
                }
            }
        }
    }

void SimulationEngine::collectItems(Room *room) {
    auto roomItems = room->getItems();
    for (Item* item : roomItems) {
        if (item == nullptr) continue;
        if (currentCharacter->getInventory().isFull()) break;
        currentCharacter->pickUpItem(item);
        room->removeItem(item);
            logEvent("Picked up: "+ item->getName() + item->getDescription());
    }
}

void SimulationEngine::useEmergencyItems() {
    if (currentCharacter->getHealth() <= 20)
        currentCharacter->tryUseHealthItem();
    if (currentCharacter->getOxygen() <= 20)
        currentCharacter->tryUseOxygenItem();


}

bool SimulationEngine::checkEscape(Room *room) {
    if (room->getId() == escapeRoomId) {
        if (escaped = currentCharacter->tryUseKeyCard(escapeRoomId)) {
            return true;
        }
    }
    return false;
}

void SimulationEngine::moveToNextRoom(Room *room) {
    if (!escaped) {
        const auto connections = room->getConnections();
        if (!connections.empty()) {
            int index = std::rand() % connections.size();
            currentCharacter->move(connections[index]);
            logEvent("Moved to: " + connections[index]->getName());
        }
    }
}

bool SimulationEngine::simulationEnd() {
    if (escaped) {
        logEvent("Character escaped the station successfully!");
        updateSummary(currentTurns, "Character escaped the station!", true);
        return true;
    }

    if (!currentCharacter->isAlive()) {
        if (currentCharacter->getOxygen() <= 0) {
            logEvent("Character died due to lack of oxygen.");
            updateSummary(currentTurns+1, "Character died due to lack of oxygen.", false); //+1 para que no aparezca turno 0 en la simulacion
        } else {
            logEvent("Character died due to health reaching zero.");
            updateSummary(currentTurns+1, "Character died due to health reaching zero.", false);
        }
        return true;
    }

    if (currentStation->getRooms().empty()) {
        logEvent("No rooms in the station.");
        updateSummary(currentTurns, "Simulation ended: no rooms", false);
        return true;
    }

    if (currentTurns >= maxTurns) {
        logEvent("Maximum turns reached.");
        updateSummary(currentTurns, "Simulation ended: max turns reached", false);
        return true;
    }
    return false;
}
