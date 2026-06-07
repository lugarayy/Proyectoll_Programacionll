//
// Created by lucig on 31/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_WORLDLOADER_H
#define PROYECTOLL_PROGRAMACIONLL_WORLDLOADER_H

#include "Station.h"
#include "OxygenTank.h"
#include <iostream>
using namespace std;

// usando factory method
class WorldLoader
{
private:
    static void loadRooms (const string& file, Station* station);
    static void loadItems (const string& file, Station* station);
    static void loadThreats (const string& file, Station* station);
    static Item* createItem(int id, const string& type,const string& name,int restore,const string& accessLevel);
    static Threat* createThreat(int id, const string& type, const string& name, int damage);
    static void randomizeConnections(Station* station);
public:
    static Station* loadStation(const string& rooms,const string& items,const string& threats);
};


#endif //PROYECTOLL_PROGRAMACIONLL_WORLDLOADER_H