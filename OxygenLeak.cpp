//
// Created by Jose on 30/5/2026.
//

#include "OxygenLeak.h"
#include "Character.h"

OxygenLeak::OxygenLeak(int id, const std::string& name, int damage) : Threat(id, name, damage) {}



void OxygenLeak::activate(Character &character)
{
    character.reduceOxygen(damage);
}

std::string OxygenLeak::getType() const
{
    return "Oxygen Leak";
}
std::string OxygenLeak::getEffectLog() const {
    return "reduced oxygen by " + std::to_string(damage) +".";
}

