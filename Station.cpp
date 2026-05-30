//
// Created by lucig on 29/5/2026.
//

#include "Station.h"

Station::Station(const string& name) : name(name) {}

Station::~Station()
{
    for (Room* room : rooms)
        delete room;
}

void Station::addRoom(Room* room)
{
    rooms.push_back(room);
}

Room* Station::getRoomById(int id) const
{
    for (Room* room : rooms)
    {
        if (room->getId() == id)
        {
            return room;
        }
    }
    return nullptr;
}

vector<Room*> Station::getRooms() const
{
    return rooms;
}

string Station::getName() const
{
    return name;
}

vector<Room*>::iterator Station::begin()
{
    return rooms.begin();
}

vector<Room*>::iterator Station::end()
{
    return rooms.end();
}

ostream& operator<<(ostream& os, const Station& station)
{
    os << "Station: " << station.name
    << " - Rooms: " << station.rooms.size();
    return os;
}
