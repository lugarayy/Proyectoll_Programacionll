//
// Created by lucig on 29/5/2026.
//

#include "RepairKit.h"
#include "Character.h"

RepairKit::RepairKit(int id, const std::string& name, int restore) : Item(id, name), restore(restore) {}

void RepairKit::use(Character& character)
{
    character.restoreHealth(restore);
}

std::string RepairKit::getType() const
{
    return "Repair Kit";
}

int RepairKit::getRestore() const
{
    return restore;
}

std::string RepairKit::getDescription() const {
    return " (Restores " + std::to_string(restore) + " health)";
}
