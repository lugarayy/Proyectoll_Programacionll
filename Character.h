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
    Character(std::string name);
    string getName() const override;
    void setName(std::string name) const;
    void interact() const override;
    void pickUpItem(const Item& item);
    void move();
    ~Character() override;
private:
    int health;
    int oxygen;
    Inventory<Item*> inventory;
};


#endif //PROYECTOLL_PROGRAMACIONLL_CHARACTER_H