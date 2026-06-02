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

const string RESET = "\033[0m";
const string ROJO = "\033[31m";
const string VERDE = "\033[32m";
const string AZUL = "\033[34m";

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

        if (currentCharacter != nullptr && currentStation != nullptr) {
            if (currentCharacter->getCurrentRoom() == nullptr) {
                const auto rooms = currentStation->getRooms();
                if (!rooms.empty()) {
                    currentCharacter->move(rooms.front());
                    logEvent("Character moved to room: " + rooms.front()->getName());
                }
            }

            Room* room = currentCharacter->getCurrentRoom();
            if (room != nullptr) {
                // Amenazas
                const auto threats = room->getThreats();
                const int dodgePercent = 30;
                for (Threat* threat : threats) {
                    if (threat == nullptr) {
                        continue;
                    }
                    threat->interact();

                    const int roll = std::rand() % 100;
                    if (roll < dodgePercent) {
                        logEvent("Combat: " + currentCharacter->getName() + " dodged " + threat->getName() + ".");
                        continue;
                    }
                    if (threat->getType() == "Oxygen Leak") {
                        currentCharacter->reduceOxygen(threat->getDamage());
                        logEvent("Combat: " + threat->getName() + " reduced oxygen by " + std::to_string(threat->getDamage()) + ".");
                    }
                    if (threat->getType()== "Defective Robot") {
                        currentCharacter->takeDamage(threat->getDamage());
                        logEvent("Combat: " + threat->getName() + " dealt " + std::to_string(threat->getDamage()) + " damage.");
                    }
                } // fin del for de amenazas

                // Agarrar los items de la habitacion luego de amenazas
                auto roomItems = room->getItems();
                for (Item* item : roomItems) {
                    if (item == nullptr) continue;
                    if (currentCharacter->getInventory().isFull()) break;
                    currentCharacter->pickUpItem(item);
                    room->removeItem(item);
                    if (item->getType() == "KeyCard") {
                        logEvent("Picked up: "+ item->getName() + " (Escape item)");
                    } if (item->getType() == "RepairKit") {
                        logEvent("Picked up: "+ item->getName() + " (Restores HP)");
                    } if (item->getType() == "OxygenTank") {
                        logEvent("Picked up: "+ item->getName() +" (Restores O2)");
                    }
                }

                // Usar items de emergencia para no morir
                if (currentCharacter->getHealth() <= 20) {
                    Inventory<Item*>& inv = currentCharacter->getInventory();
                    for (auto it = inv.begin(); it != inv.end(); ++it) {
                        RepairKit* kit = dynamic_cast<RepairKit*>(*it);
                        if (kit != nullptr) {
                            kit->use(*currentCharacter);
                            inv.removeItem(*it);
                            logEvent("Used Repair Kit to recover HP.");
                            break;
                        }
                    }
                }

                if (currentCharacter->getOxygen() <= 20) {
                    Inventory<Item*>& inv = currentCharacter->getInventory();
                    for (auto it = inv.begin(); it != inv.end(); ++it) {
                        OxygenTank* tank = dynamic_cast<OxygenTank*>(*it);
                        if (tank != nullptr) {
                            tank->use(*currentCharacter);
                            inv.removeItem(*it);
                            logEvent("Used Oxygen Tank to recover O2.");
                            break;
                        }
                    }
                }

                // Verificar la victoria a la hora de conseguir una KeyCard y utilizarla en la habitacion marcada
                if (room->getId() == escapeRoomId) {
                    Inventory<Item*>& inv = currentCharacter->getInventory();
                    for (auto it = inv.begin(); it != inv.end(); ++it) {
                        KeyCard* key = dynamic_cast<KeyCard*>(*it);
                        if (key != nullptr) {
                            logEvent("Character used " + key->getName() + " to escape from " + room->getName() + "!");
                            escaped = true;
                            break;
                        }
                    }
                }

                // Movimiento a otra habitacion si no se gano y vuelve a comenzar
                if (!escaped) {
                    const auto connections = room->getConnections();
                    if (!connections.empty()) {
                        int index = std::rand() % connections.size();
                        currentCharacter->move(connections[index]);
                        logEvent("Moved to: " + connections[index]->getName());
                    }
                }
            }

            printTurnStats();
            currentTurns++;
        }

        if (escaped) {
            logEvent("Character escaped the station successfully!");
            updateSummary(currentTurns, "Character escaped the station!", true);
            return;
        }

        if (!currentCharacter->isAlive()) {
            logEvent("Character has been defeated.");
            updateSummary(currentTurns, "Simulation ended: character defeated", false);
            return;
        }

        if (currentStation->getRooms().empty()) {
            logEvent("No rooms in the station.");
            updateSummary(currentTurns, "Simulation ended: no rooms", false);
            return;
        }

        if (currentTurns >= maxTurns) {
            logEvent("Maximum turns reached.");
            updateSummary(currentTurns, "Simulation ended: max turns reached", false);
            return;
        }
        logEvent("Simulation ended.");
        updateSummary(currentTurns, "Simulation ended", false);
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
    logEvent("\n=== End of Turn " + std::to_string(currentTurns + 1) + " ===");
    logEvent("Room: " + roomInfo +
             " | HP: " + std::to_string(currentCharacter->getHealth()) +
             " | O2: " + std::to_string(currentCharacter->getOxygen()) +
             " | Inventory: " + std::to_string(currentCharacter->getInventory().getSize()) +
             "/" + std::to_string(currentCharacter->getInventory().getMaxCapacity()));
}
