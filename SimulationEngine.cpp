//
// Created by Jose on 30/5/2026.
//

#include "SimulationEngine.h"
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
                    //threat->activate();

                    const int roll = std::rand() % 100;
                    if (roll < dodgePercent) {
                        logEvent("Combat: " + currentCharacter->getName() + " dodged " + threat->getName() + ".");
                        continue;
                    }

                    currentCharacter->takeDamage(threat->getDamage());
                    logEvent("Combat: " + threat->getName() + " dealt " + std::to_string(threat->getDamage()) + " damage.");
                }

                // Agarrar los items de la habitacion luego de amenazas
                auto roomItems = room->getItems();
                for (Item* item : roomItems) {
                    if (item == nullptr) continue;
                    if (currentCharacter->getInventory().isFull()) break;
                    currentCharacter->pickUpItem(item);
                    room->removeItem(item);
                    logEvent("Picked up: " + item->getName());
                }

                // Usar items de emergencia para no morir
                if (currentCharacter->getHealth() <= 20) {
                    Inventory<Item*>& inv = currentCharacter->getInventory();
                    for (auto it = inv.begin(); it != inv.end(); ++it) {
                        RepairKit* kit = dynamic_cast<RepairKit*>(*it);
                        if (kit != nullptr) {
                            kit->use(*currentCharacter);
                            inv.removeItem(*it);
                            logEvent("Used RepairKit in emergency.");
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
                            logEvent("Used OxygenTank in emergency.");
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
        }

        currentTurns++;
    }

    if (escaped) {
        updateSummary(currentTurns, "Character escaped the station!", true);
        return;
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
        updateSummary(currentTurns, "Simulation ended: max turns reached", false);
        return;
    }

    updateSummary(currentTurns, "Simulation ended", false);
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
