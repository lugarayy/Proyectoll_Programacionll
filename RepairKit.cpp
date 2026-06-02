//
// Created by lucig on 29/5/2026.
//

#include "RepairKit.h"
#include "Character.h"

RepairKit::RepairKit(int id, const string& name, int restore) : Item(id, name), restore(restore) {}

void RepairKit::use(Character& character)
{
    character.restoreHealth(restore);
    cout << "Using RepairKit: +" << restore << " health" << endl;
}

string RepairKit::getType() const
{
    return "RepairKit";
}

int RepairKit::getRestore() const
{
    return restore;
}

void RepairKit::interact()
{
    cout << "You found a Repair Kit" << endl;
}
