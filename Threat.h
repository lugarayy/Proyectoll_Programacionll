//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_THREAT_H
#define PROYECTOLL_PROGRAMACIONLL_THREAT_H
#include "Entity.h"
#include <iostream>

class Threat : public Entity {
public:
    Threat() { name = "Threat"; }
    virtual void activate() =0;
    ~Threat() override = default;
    void interact() override {
        std::cout << "Threat activated: " << name << " (damage " << damage << ")" << std::endl;
    }
    std::string getName() const override { return name; }
protected:
   int damage = 0;
};


#endif //PROYECTOLL_PROGRAMACIONLL_THREAT_H