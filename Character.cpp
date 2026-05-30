//
// Created by Jose on 30/5/2026.
//

#include "Character.h"
#include <iostream>
#include <utility>

Character::Character() : Entity(), health(100), oxygen(100), inventory(10) {
    name = "Player";
}

Character::Character(std::string name, int health, int oxygen, size_t inventoryCapacity)
    : Entity(), health(health), oxygen(oxygen), inventory(inventoryCapacity) {
    this->name = std::move(name);
}

std::string Character::getName() const {
    return name;
}

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
        std::cout << "Picked up: " << item->getName() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Cannot pick up " << item->getName() << ": " << e.what() << std::endl;
    }
}

void Character::move() {
    std::cout << name << " moved." << std::endl;
}

Character::~Character() {
}
