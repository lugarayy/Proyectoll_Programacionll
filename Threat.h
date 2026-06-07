//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_THREAT_H
#define PROYECTOLL_PROGRAMACIONLL_THREAT_H
#include "Entity.h"
#include <iostream>
class Character;

class Threat : public Entity {
public:
    Threat(int id, const std::string& name, int damage) : Entity(id,name), damage(damage) {}
    ~Threat() override=default;
    virtual void activate(Character &character) = 0;
    std::string getType() const override {return "Threat";}
    int getDamage() const { return damage; }
    virtual std::string getEffectLog() const=0;
protected:
   int damage;
};


#endif //PROYECTOLL_PROGRAMACIONLL_THREAT_H