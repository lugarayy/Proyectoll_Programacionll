//
// Created by Jose on 30/5/2026.
//

#include "Character.h"
#include <iostream>
#include <utility>

Character::Character() : Entity(0,"Player"), health(100), oxygen(100), inventory(10), currentRoom(nullptr) {}

Character::Character(std::string name, int health, int oxygen, size_t inventoryCapacity)
    : Entity(0,std::move(name)), health(health), oxygen(oxygen), inventory(inventoryCapacity), currentRoom(nullptr) {}

/*std::string Character::getName() const {
    return name;
}*/

void Character::setName(const std::string& name) {
    this->name = name;
}

void Character::interact() {
    std::cout << "Character interacting: " << name << std::endl;
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

Character::~Character() {}
