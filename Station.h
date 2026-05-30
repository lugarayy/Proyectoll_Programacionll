//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_STATION_H
#define PROYECTOLL_PROGRAMACIONLL_STATION_H

#include <iostream>
#include <vector>
#include "Room.h"
using namespace std;

class Station
{
private:
    string name;
    vector<Room*> rooms;
public:
    Station(const string& name);
    ~Station();

    void addRoom(Room* room);
    Room* getRoomById(int id) const;

    vector<Room*> getRooms() const;
    string getName() const;

    //iterador q recorre las salas del juego
    //el iterador ya viene incluido en vector :O
    vector<Room*>::iterator begin();
    vector<Room*>::iterator end();

    //en vez de usar tostring usamos operadores
    friend ostream& operator<<(ostream& os, const Station& station);

};


#endif //PROYECTOLL_PROGRAMACIONLL_STATION_H