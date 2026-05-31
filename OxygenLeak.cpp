//
// Created by Jose on 30/5/2026.
//

#include "OxygenLeak.h"

OxygenLeak::OxygenLeak(int id, const std::string& name, int damage) : Threat(id, name, damage) {}

void OxygenLeak::interact()
{

    std::cout << "Oxygen leak interact" << std::endl;
    this->activate();
}

void OxygenLeak::activate()
{
    std::cout << name << " is leaking oxygen, Damage:" << damage << std::endl;
}

std::string OxygenLeak::getType() const
{
    return "Oxygen leak";
}

