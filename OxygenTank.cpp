//
// Created by lucig on 29/5/2026.
//

#include "OxygenTank.h"
#include "Character.h"

OxygenTank::OxygenTank(int id, const std::string& name, int restore) : Item(id,name), restore(restore) {}

void OxygenTank::use(Character& character)
{
    character.restoreOxygen(restore);
}

std::string OxygenTank::getType() const
{
    return "Oxygen Tank";
}

int OxygenTank::getRestore() const
{
    return restore;
}

std::string OxygenTank::getDescription() const {
    return " (Restores " + std::to_string(restore) + " oxygen)";
}
