//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_ROOM_H
#define PROYECTOLL_PROGRAMACIONLL_ROOM_H

#include <iostream>
#include <vector>


class Item;
class Threat;

class Room
{
private:
    int id;
    std::string name;
    std::vector<Room*> connections;
    std::vector<Item*> items;
    std::vector<Threat*> threats;
public:
    Room(int id, const std::string& name);
    ~Room();

    int getId() const;
    std::string getName() const;

    void addConnection(Room* room);
    std::vector<Room*> getConnections() const;
    void clearConnections();

    void addItem(Item* item);
    void addThreat(Threat* threat);

    std::vector<Item*> getItems() const;
    std::vector<Threat*> getThreats() const;

    void removeItem(Item* item);

    bool operator==(const Room& room) const;
    friend std::ostream& operator<<(std::ostream& os, const Room& room); //en vez de tostring, muestra los datos con operador

    void clearItems();
};


#endif //PROYECTOLL_PROGRAMACIONLL_ROOM_H