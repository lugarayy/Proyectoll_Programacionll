//
// Created by lucig on 31/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_WORLDLOADER_H
#define PROYECTOLL_PROGRAMACIONLL_WORLDLOADER_H

#include "Station.h"
#include "OxygenTank.h"
#include "RepairKit.h"
#include "KeyCard.h"
#include "DefectiveRobot.h"
#include "OxygenLeak.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
using namespace std;

// usando factory method
// el formato podria ser Lu -> (separado por ';'):
//   rooms.txt:   id;name;oxygen;energy;connectedRoomId1,connectedRoomId2,...
//   items.txt:   roomId;itemId;type;name;restore_or_accessLevel
//                types: OxygenTank (restore=int), RepairKit (restore=int), KeyCard (accessLevel=string)
//   threats.txt: roomId;threatId;type;name;damage
//                types: DefectiveRobot, OxygenLeak
class WorldLoader
{
private:
    static void loadRooms (const string& file, Station* station);
    static void loadItems (const string& file, Station* station);
    static void loadThreats (const string& file, Station* station);

    static Item* createItem(int id, const string& type,const string& name,int restore,const string& accessLevel);
    static Threat* createThreat(int id, const string& type, const string& name, int damage);
public:
    static Station* loadStation(const string& rooms,const string& items,const string& threats);
};


#endif //PROYECTOLL_PROGRAMACIONLL_WORLDLOADER_H