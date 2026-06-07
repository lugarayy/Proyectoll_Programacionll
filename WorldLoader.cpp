//
// Created by lucig on 31/5/2026.
//

#include "WorldLoader.h"
#include <sstream>
#include <cstdlib>
#include "RepairKit.h"
#include "DefectiveRobot.h"
#include "OxygenLeak.h"
#include <fstream>
#include <stdexcept>
// para rand()

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

    // Las conexiones se generan automaticamente en randomizeConnections()
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
    // NUEVO -> despues de cargar los cuartos del archivo, mezclamos las conexiones
    // para que cada ejecucion del programa tenga un mapa diferente.
    randomizeConnections(station);
    loadItems(items,station);
    loadThreats(threats,station);
    return station;
}

// =====================================================================
// randomizeConnections
// ---------------------------------------------------------------------
// Lo que hace este metodo:
//   - Sobrescribe las conexiones de los cuartos cargadas del archivo rooms.txt
//   - Genera un grafo COMPLETAMENTE aleatorio entre los cuartos
//   - Pero garantiza que TODOS los cuartos sean alcanzables desde cualquiera
//     (sin esto, el cuarto 10 con la KeyCard o el cuarto 4 con la salida
//      podrian quedar aislados y la simulacion fallaria siempre)
//
// Como lo hace (algoritmo):
//   1) Borra todas las conexiones existentes de cada cuarto
//   2) Mezcla aleatoriamente el orden de los cuartos (shuffle Fisher-Yates)
//   3) Construye un "spanning tree aleatorio":
//        cada cuarto (desde el 2do) se conecta a UN cuarto random anterior.
//        Esto garantiza que el grafo es conexo (todos alcanzables).
//   4) Agrega aristas extras random (n/2) para que el mapa no sea solo
//      un camino lineal y haya varias rutas posibles.
//
// IMPORTANTE: las conexiones son bidireccionales (si A->B entonces B->A).
//
// Notas:
//   - rand() debe estar seedeado antes de llamar a este metodo
//     (eso se hace en main.cpp con srand(time(NULL)))
//   - Las conexiones definidas en rooms.txt se vuelven irrelevantes
//     porque este metodo las sobreescribe completamente
// =====================================================================
void WorldLoader::randomizeConnections(Station* station)
{
    vector<Room*> rooms = station->getRooms();
    int n = static_cast<int>(rooms.size());

    // Si hay menos de 2 cuartos, no hay conexiones que hacer
    if (n < 2) return;

    // Paso 1: limpiar las conexiones cargadas del archivo
    for (Room* room : rooms) {
        room->clearConnections();
    }

    // Paso 2: copiar y mezclar el vector de cuartos (Fisher-Yates shuffle)
    // Esto sirve para que el orden en que se construye el spanning tree
    // sea diferente cada vez.
    vector<Room*> shuffled = rooms;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Room* temp = shuffled[i];
        shuffled[i] = shuffled[j];
        shuffled[j] = temp;
    }

    // Paso 3: construir spanning tree aleatorio
    // Para cada cuarto (desde el indice 1) lo conectamos a un cuarto random
    // que este ANTES en el array. Esto garantiza un arbol conexo sin ciclos.
    for (int i = 1; i < n; i++) {
        int parent = rand() % i;
        shuffled[i]->addConnection(shuffled[parent]);
        shuffled[parent]->addConnection(shuffled[i]); // bidireccional
    }

    // Paso 4: agregar aristas extra random para variar el mapa
    // (asi no es solo un arbol lineal, sino que hay caminos alternativos)
    int extraEdges = n / 2;
    for (int e = 0; e < extraEdges; e++) {
        int a = rand() % n;
        int b = rand() % n;
        if (a == b) continue; // un cuarto no se conecta a si mismo

        // Verificar si la conexion ya existe (para no duplicar)
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
