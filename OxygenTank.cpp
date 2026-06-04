//
// Created by lucig on 29/5/2026.
//

#include "OxygenTank.h"
#include "Character.h"

OxygenTank::OxygenTank(int id, const string& name, int restore) : Item(id,name), restore(restore) {}

void OxygenTank::use(Character& character)
{
    character.restoreOxygen(restore);
}

string OxygenTank::getType() const
{
    return "Oxygen Tank";
}

int OxygenTank::getRestore() const
{
    return restore;
}

string OxygenTank::getDescription() const {
    return " (Restores " + std::to_string(restore) + " oxygen)";
}
