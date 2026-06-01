//
// Created by lucig on 31/5/2026.
//

#include "WorldLoader.h"

void WorldLoader::loadRooms(const string& file, Station* station)
{
}

void WorldLoader::loadItems(const string& file, Station* station)
{
}

void WorldLoader::loadThreats(const string& file, Station* station)
{
}

Item* WorldLoader::createItem(int id, const string& type, const string& name, int restore, const string& accessLevel)
{
}

Threat* WorldLoader::creatThreat(int id, const string& type, const string& name, int damage)
{
}

Station* WorldLoader::loadStation(const string& rooms, const string& items, const string& threats)
{
}
