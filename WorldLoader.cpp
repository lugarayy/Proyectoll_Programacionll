//
// Created by lucig on 31/5/2026.
//

#include "WorldLoader.h"
#include <sstream>
#include <cstdlib>
#include "RepairKit.h"
#include "DefectiveRobot.h"
#include "OxygenLeak.h"
#include "KeyCard.h"
#include <fstream>
#include <stdexcept>

void WorldLoader::loadRooms(const string& file, Station* station)
{
    ifstream fileroom(file);
    if (!fileroom.is_open())
    {
        throw runtime_error("Cannot open file" + file);
    }

    string line;
   while (getline(fileroom,line))
   {
       if (line.empty()||line[0] == '#' ) continue;

       stringstream ss(line);
       string t;
       vector<string> tokens;
       while (getline(ss,t,';'))
       {
           tokens.push_back(t);
       }
       if (tokens.size() < 2)
       {
           throw runtime_error("Invalid room format");
       }

       //agarra las lineas en las que esta
       int id = stoi(tokens[0]);
       string name = tokens[1];

       Room* room = new Room(id,name);
       station->addRoom(room);
   }
    fileroom.close();
}

void WorldLoader::loadItems(const string& file, Station* station)
{
    ifstream fileitem(file);
    if (!fileitem.is_open())
    {
        throw runtime_error("Cannot open file" + file);
    }

    string line;
    while (getline(fileitem,line))
    {
        if (line.empty()||line[0]=='#') continue;
        stringstream ss(line);
        string t;
        vector<string> tokens;
        while (getline(ss,t,';'))
        {
            tokens.push_back(t);
        }

        if (tokens.size() < 5)
        {
            throw runtime_error("Invalid item format");
        }

        int roomid = stoi(tokens[0]);
        int id = stoi(tokens[1]);
        string type = tokens[2];
        string name = tokens[3];
        string last = tokens[4];
        int restore = 0;
        string accessLevel;

        if (type == "KeyCard")
        {
            accessLevel = last;
        }else
        {
            restore = stoi(last);
        }

        Item* item = createItem(id,type,name,restore,accessLevel);
        Room* room = station->getRoomById(roomid);
        if (room != nullptr && item != nullptr)
        {
            room->addItem(item);
        }
    }
    fileitem.close();
}

void WorldLoader::loadThreats(const string& file, Station* station)
{
    ifstream filethreat(file);
    if (!filethreat.is_open())
    {
        throw runtime_error("Cannot open file" + file);
    }

    string line;
    while (getline(filethreat,line))
    {
        if (line.empty()||line[0]=='#') continue;
        stringstream ss(line);
        string t;
        vector<string> tokens;
        while (getline(ss,t,';'))
        {
            tokens.push_back(t);
        }

        if (tokens.size() < 5)
        {
            throw runtime_error("Invalid threat format");
        }

        int roomid = stoi(tokens[0]);
        int id = stoi(tokens[1]);
        string type = tokens[2];
        string name = tokens[3];
        int damage = stoi(tokens[4]);

        Threat* threat = createThreat(id,type,name,damage);
        Room* room = station->getRoomById(roomid);
        if (room != nullptr && threat != nullptr)
        {
            room->addThreat(threat);
        }
    }
    filethreat.close();
}

Item* WorldLoader::createItem(int id, const string& type, const string& name, int restore, const string& accessLevel)
{
    if (type == "OxygenTank")
    {
        return new OxygenTank(id,name,restore);
    }else if (type == "KeyCard")
    {
        return new KeyCard(id,name,accessLevel);
    } else if (type == "RepairKit")
    {
        return new RepairKit(id,name,restore);
    }else
    {
        throw runtime_error("Invalid item type");
    }
}

Threat* WorldLoader::createThreat(int id, const string& type, const string& name, int damage)
{
    if (type == "DefectiveRobot")
    {
        return new DefectiveRobot(id,name,damage);
    }else if (type == "OxygenLeak")
    {
        return new OxygenLeak(id,name,damage);
    }else
    {
        throw runtime_error("Invalid threat type");
    }
}

Station* WorldLoader::loadStation(const string& rooms, const string& items, const string& threats)
{
    Station* station = new Station("Space station");
    loadRooms(rooms,station);
    randomizeConnections(station);
    loadItems(items,station);
    loadThreats(threats,station);
    return station;
}

// =====================================================================
// randomizeConnections
// ---------------------------------------------------------------------
// What this method does:
//   - Overwrites the room connections loaded from the rooms.txt file.
//   - Generates a COMPLETELY random graph between the rooms.
//   - However, it guarantees that ALL rooms are reachable from any other
//     (without this, room 10 with the KeyCard or room 4 with the exit
//      could end up isolated, and the simulation would always fail).
//
// How it does it (algorithm):
//   1) Clears all existing connections for each room.
//   2) Randomly shuffles the order of the rooms (Fisher-Yates shuffle).
//   3) Builds a "random spanning tree":
//        each room (starting from the 2nd) connects to ONE random previous room.
//        This guarantees that the graph is connected (all rooms reachable).
//   4) Adds extra random edges (n/2) so the map is not just a linear
//      path and multiple alternative routes exist.
//
// IMPORTANT: Connections are bidirectional (if A->B, then B->A).
//
// Notes:
//   - rand() must be seeded before calling this method
//     (this is handled in main.cpp using srand(time(NULL))).
//   - The connections defined in rooms.txt become irrelevant
//     because this method completely overwrites them.
// =====================================================================
void WorldLoader::randomizeConnections(Station* station)
{
    vector<Room*> rooms = station->getRooms();
    int n = static_cast<int>(rooms.size());
    if (n < 2) return;
    for (Room* room : rooms) {
        room->clearConnections();
    }
    //(Fisher-Yates shuffle)
    vector<Room*> shuffled = rooms;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Room* temp = shuffled[i];
        shuffled[i] = shuffled[j];
        shuffled[j] = temp;
    }

    for (int i = 1; i < n; i++) {
        int parent = rand() % i;
        shuffled[i]->addConnection(shuffled[parent]);
        shuffled[parent]->addConnection(shuffled[i]);
    }
    int extraEdges = n / 2;
    for (int e = 0; e < extraEdges; e++) {
        int a = rand() % n;
        int b = rand() % n;
        if (a == b) continue;
        bool exists = false;
        for (Room* conn : shuffled[a]->getConnections()) {
            if (conn == shuffled[b]) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            shuffled[a]->addConnection(shuffled[b]);
            shuffled[b]->addConnection(shuffled[a]);
        }
    }
}
