//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_CHARACTER_H
#define PROYECTOLL_PROGRAMACIONLL_CHARACTER_H
#include "Item.h"
#include "Entity.h"
#include "Inventory.h"

class Character : public Entity {
    public:
    Character();
    Character(std::string name, int health, int oxygen, size_t inventoryCapacity);
    std::string getName() const override;
    void setName(const std::string& name);
    void interact() override;
    void pickUpItem(Item* item);
    void move();
    ~Character() override;
private:
    int health;
    int oxygen;
    Inventory<Item*> inventory;
};


#endif //PROYECTOLL_PROGRAMACIONLL_CHARACTER_H