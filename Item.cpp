//
// Created by lucig on 29/5/2026.
//

#include "Item.h"

Item::Item(int id, const string& name) : id(id),name(name){}

Item::~Item() {}

int Item::getId() const
{
    return id;
}

string Item::getName() const
{
    return name;
}

ostream& operator<<(ostream& os, const Item& item)
{
    os << "ITEM: " << item.name << " - id: " << item.getId();
    return os;
}
