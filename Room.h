//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_ROOM_H
#define PROYECTOLL_PROGRAMACIONLL_ROOM_H

#include <iostream>
#include <vector>
using namespace std;

class Item;
class Threat;

class Room
{
private:
    int id;
    string name;
    int oxygen;
    int energy;

    vector<Room*> connections;
    vector<Item*> items;
    vector<Threat*> threats;
public:
    Room(int id, const string& name, int oxygen, int energy);
    ~Room();

    int getId() const;
    string getName() const;
    int getOxygen() const;
    int getEnergy() const;

    void addConnection(Room* room);
    vector<Room*> getConnections() const;

    void addItem(Item* item);
    void addThreat(Threat* threat);
    vector<Item*> getItems() const;
    vector<Threat*> getThreats() const;
    void removeItem(Item* item);

    bool operator==(const Room& room) const;
    friend ostream& operator<<(ostream& os, const Room& room); //en vez de tostring, muestra los datos con operador
    void clearItems();
};


#endif //PROYECTOLL_PROGRAMACIONLL_ROOM_H