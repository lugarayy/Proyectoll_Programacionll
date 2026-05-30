//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_ITEM_H
#define PROYECTOLL_PROGRAMACIONLL_ITEM_H

#include <iostream>
using namespace std;

class Character;

class Item
{
protected:
    int id;
    string name;
public:
    Item(int id, const string &name);
    virtual ~Item();

    int getId() const;
    string getName() const;

    virtual void use(Character& character) = 0;
    virtual string getType() const = 0;

    Item(const Item &item) = delete;
    Item& operator=(const Item &item) = delete;

    friend ostream& operator<<(ostream &os, const Item &item);
};


#endif //PROYECTOLL_PROGRAMACIONLL_ITEM_H