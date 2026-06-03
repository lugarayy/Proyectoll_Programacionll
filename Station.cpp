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

void Station::printMap() const //Se anniadio mapita
{
    std::cout << "\n========== STATION MAP ==========" << std::endl;
    std::cout << "Station: " << name << " (" << rooms.size() << " rooms)" << std::endl;
    std::cout << "================================\n" << std::endl;

    for (const Room* room : rooms) {
        if (room == nullptr) continue;

        //std::cout << "[Room " << room->getId() << "] " << room->getName() << std::endl;
        //std::cout << "  Oxygen: " << room->getOxygen() << " | Energy: " << room->getEnergy() << std::endl;
        //std::cout << "  Items: " << room->getItems().size() << " | Threats: " << room->getThreats().size() << std::endl;

        std::cout << *room<<std::endl; //operator<< room

        const auto connections = room->getConnections();
        if (!connections.empty()) {
            std::cout << "  Connections: ";
            for (size_t i = 0; i < connections.size(); ++i) {
                std::cout << connections[i]->getId();
                if (i < connections.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "================================\n" << std::endl;
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
