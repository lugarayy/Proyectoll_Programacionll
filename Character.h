//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_CHARACTER_H
#define PROYECTOLL_PROGRAMACIONLL_CHARACTER_H
#include "Item.h"
#include "Entity.h"
#include "Inventory.h"
#include "Room.h"
#include <string>

class Character : public Entity {
    public:
    Character();
    Character(std::string name, int health, int oxygen, size_t inventoryCapacity);
    void setName(const std::string& name);
    void pickUpItem(Item* item);
    void move(Room* nextRoom);
    void takeDamage(int damage);
    void reduceOxygen(int damage);
    void restoreOxygen(int oxygen);
    void restoreHealth(int health);
    void grantEscapeAccess();
    bool canEscape() const;
    std::string getType() const override;
    bool isAlive() const;
    Room* getCurrentRoom() const;
    Inventory<Item*>& getInventory();
    int getHealth() const;
    int getOxygen() const;
    ~Character() override;
    std::string tryUseHealthItem();
    std::string tryUseOxygenItem();
    bool tryUseKeyCard(int escapeRoomId);

private:
    int health;
    int oxygen;
    bool escapeAccessGranted;
    Inventory<Item*> inventory;
    Room* currentRoom;

};


#endif //PROYECTOLL_PROGRAMACIONLL_CHARACTER_H