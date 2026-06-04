//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_ITEM_H
#define PROYECTOLL_PROGRAMACIONLL_ITEM_H

#include <iostream>

#include "Entity.h"
using namespace std;

class Character;

class Item : public Entity
{
public:
    Item(int id, const string &name) : Entity(id, name) {}
    ~Item()override=default;
    virtual std::string getDescription() const = 0;
    virtual void use(Character& character) = 0;

    string getType() const override { return "Item"; }

    Item(const Item &item) = delete;
    Item& operator=(const Item &item) = delete;

    friend ostream& operator<<(ostream &os, const Item &item)
    {
        os << "Item: " << item.id << " - " << item.name;
        return os;
    }

};


#endif //PROYECTOLL_PROGRAMACIONLL_ITEM_H