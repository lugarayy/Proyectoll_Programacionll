//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_THREAT_H
#define PROYECTOLL_PROGRAMACIONLL_THREAT_H
#include "Entity.h"
#include <iostream>

class Threat : public Entity {
public:
    Threat(int id, const std::string& name, int damage) : Entity(id,name), damage(damage) {}
    virtual ~Threat() = default;

    virtual void activate() = 0;
    virtual std::string getType() const = 0;

    void interact() override {
        std::cout << "Threat activated: " << name << " (damage " << damage << ")" << std::endl;
    }

    int getDamage() const { return damage; }

protected:
   int damage;
};


#endif //PROYECTOLL_PROGRAMACIONLL_THREAT_H