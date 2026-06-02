//
// Created by lucig on 29/5/2026.
//

#include "Room.h"
#include "Item.h"
#include "Threat.h"

Room::Room(int id, const string& name, int oxygen, int energy)
: id(id), name(name), oxygen(oxygen), energy(energy) {}

Room::~Room()
{
    for (Item* item : items) delete item;
    for (Threat* threat : threats) delete threat;
}

int Room::getId() const
{
    return id;
}

string Room::getName() const
{
    return name;
}

int Room::getOxygen() const
{
    return oxygen;
}

int Room::getEnergy() const
{
    return energy;
}

void Room::addConnection(Room* room)
{
    connections.push_back(room);
}

vector<Room*> Room::getConnections() const
{
    return connections;
}

void Room::addItem(Item* item)
{
    items.push_back(item);
}

void Room::addThreat(Threat* threat)
{
    threats.push_back(threat);
}

vector<Item*> Room::getItems() const
{
    return items;
}

vector<Threat*> Room::getThreats() const
{
    return threats;
}

void Room::removeItem(Item* item)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (*it == item)
        {
            items.erase(it);
            break;
        }
    }
}

bool Room::operator==(const Room& room) const
{
    return id == room.id;
}

ostream& operator<<(ostream& os, const Room& room)
{
    os << "[Room: " << room.id << "] " << room.name
    << " - Oxygen: " << room.oxygen
    << " - Energy: " << room.energy
    << " - Connections: " << room.connections.size()
    << " - Items: " << room.items.size()
    << " - Threats: " << room.threats.size();
    return os;
}

void Room::clearItems()
{
    items.clear();
}

void Room::clearConnections()
{
    connections.clear();
}
