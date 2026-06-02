//
// Created by lucig on 31/5/2026.
//

#include "WorldLoader.h"

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
       if (tokens.size() < 5) // 5 spaces
       {
           throw runtime_error("Invalid room name");
       }

       //agarra las lineas en las que esta
       int id = stoi(tokens[0]);
       string name = tokens[1];
       int oxygen = stoi(tokens[2]);
       int energy = stoi(tokens[3]);
       string connections = tokens[4];

       Room* room = new Room(id,name,oxygen,energy);
       station->addRoom(room);
   }
    fileroom.close();

    //connections,cargar salas
    ifstream fileroom2(file);
    while (getline(fileroom2,line))
    {
        if (line.empty()||line[0] == '#' ) continue;

        stringstream ss(line);
        string t;
        vector<string> tokens;
        while (getline(ss,t,';'))
        {
            tokens.push_back(t);
        }

        int id = stoi(tokens[0]);
        string connections = tokens[4];

        Room* currentroom = station->getRoomById(id);
        stringstream sss(connections);
        string cont;
        while (getline(sss,cont,','))
        {
            int conid = stoi(cont);
            Room* connRoom = station->getRoomById(conid);
            if (connRoom != nullptr)
            {
                currentroom->addConnection(connRoom);
            }
        }
    }
    fileroom2.close();
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
        string accessLevel = "";

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
    loadItems(items,station);
    loadThreats(threats,station);
    return station;
}
