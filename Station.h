//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_STATION_H
#define PROYECTOLL_PROGRAMACIONLL_STATION_H

#include <iostream>
#include <vector>
#include "Room.h"


class Station
{
private:
    std::string name;
    std::vector<Room*> rooms;
public:
    Station(const std::string& name);
    ~Station();
    void addRoom(Room* room);
    Room* getRoomById(int id) const;
    std::vector<Room*> getRooms() const;
    std::string getName() const;
    void printMap() const;
    //iterador q recorre las salas del juego
    //el iterador ya viene incluido en vector :O
    std::vector<Room*>::iterator begin();
    std::vector<Room*>::iterator end();

    //en vez de usar tostring usamos operadores
    friend std::ostream& operator<<(std::ostream& os, const Station& station);

};


#endif //PROYECTOLL_PROGRAMACIONLL_STATION_H