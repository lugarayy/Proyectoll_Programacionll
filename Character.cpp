//
// Created by Jose on 30/5/2026.
//

#include "Character.h"
#include <iostream>
#include <utility>

Character::Character() : Entity(0,"Player"), health(100), oxygen(100), escapeAccessGranted(false), inventory(10), currentRoom(nullptr) {}

Character::Character(std::string name, int health, int oxygen, size_t inventoryCapacity)
    : Entity(0,std::move(name)), health(health), oxygen(oxygen), escapeAccessGranted(false), inventory(inventoryCapacity), currentRoom(nullptr) {}

std::string Character::getType() const {
    return "Character";
}

void Character::setName(const std::string& name) {
    this->name = name;
}

void Character::pickUpItem(Item* item) {
    if (item == nullptr) {
        std::cout << "Cannot pick up item: null pointer" << std::endl;
        return;
    }

    try {
        inventory.addItem(item);
    } catch (const std::runtime_error& e) {
        std::cout << "Cannot pick up " << item->getName() << ": " << e.what() << std::endl;
    }
}

void Character::move(Room* nextRoom) {
    currentRoom = nextRoom;
}

void Character::takeDamage(int damage) {
    if (damage<0) return;
    health -= damage;
}
void Character::reduceOxygen(int damage) {
    if (damage<0) return;
    oxygen -= damage;
}

void Character::restoreOxygen(int oxygenRestore) {
    if (oxygenRestore<0) return;
    oxygen += oxygenRestore;
}

void Character::restoreHealth(int healthRestore) {
    if (healthRestore<0) return;
    health += healthRestore;
}

void Character::grantEscapeAccess() {
    escapeAccessGranted = true;
}

bool Character::canEscape() const {
    return escapeAccessGranted;
}

bool Character::isAlive() const {
    if (health <= 0 || oxygen <= 0) {
        return false;
    }
    return true;
}

Room* Character::getCurrentRoom() const {
    return currentRoom;
}

Inventory<Item*>& Character::getInventory() {
    return inventory;
}

int Character::getHealth() const {
    return health;
}

int Character::getOxygen() const {
    return oxygen;
}

bool Character::tryUseHealthItem() {
    for (size_t i = 0; i < inventory.getSize(); ++i) {
        Item* item = inventory.getItems()[i];
        if (item != nullptr&& item->getType() == "Repair Kit") {
            item->use(*this);
            inventory.removeItem(item);
            return true;
        }
    }
    return false;
}

bool Character::tryUseOxygenItem() {
    for (size_t i = 0; i < inventory.getSize(); ++i) {
        Item* item = inventory.getItems()[i];
        if (item != nullptr && item->getType() == "Oxygen Tank") {
            item->use(*this);
            inventory.removeItem(item);
            return true;
        }
    }
    return false;
}

bool Character::tryUseKeyCard(int escapeRoomId) {
    if (currentRoom==nullptr || currentRoom->getId() != escapeRoomId) return false;
    for (size_t i = 0; i < inventory.getSize(); ++i) {
        Item* item = inventory.getItems()[i];
        if (item != nullptr && item->getType() == "KeyCard") {
            item->use(*this);
            inventory.removeItem(item);
            return canEscape();
        }
    }
    return false;
}

Character::~Character() {}
