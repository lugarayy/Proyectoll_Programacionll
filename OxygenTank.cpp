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
    return "OxygenTank";
}

int OxygenTank::getRestore() const
{
    return restore;
}

