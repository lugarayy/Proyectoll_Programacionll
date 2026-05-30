//
// Created by lucig on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_INVENTORY_H
#define PROYECTOLL_PROGRAMACIONLL_INVENTORY_H

#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename T>

class Inventory
{
private:
    vector<T> items;
    size_t maxCapacity;
public:
    Inventory(size_t capacity) : maxCapacity(capacity) {}
    ~Inventory() {}

    bool isFull() const { return maxCapacity >= items.size(); }
    bool isEmpty() const { return items.empty(); }
    size_t getSize() const { return items.size(); }
    size_t getMaxCapacity() const { return maxCapacity; }
    vector<T>& getItems() const { return items; }

    void addItem(T item)
    {
        if (isFull())
        {
            throw runtime_error("Inventory already full");
        }
        items.push_back(item);
    }

    void removeItem(T item)
    {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (*it == item)//* antes por que busca o apunta al item en ese pos
            {
                items.erase(it);
                return;
            }
        }
    }
};


#endif //PROYECTOLL_PROGRAMACIONLL_INVENTORY_H