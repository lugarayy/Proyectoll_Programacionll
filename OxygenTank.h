//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_OXYGENTANK_H
#define PROYECTOLL_PROGRAMACIONLL_OXYGENTANK_H

#include "Item.h"

class OxygenTank : public Item
{
private:
    int restore;
public:
    OxygenTank(int id, const string& name, int restore);
    void use(Character& character) override;
    string getType() const override;
    int getRestore() const;
    void interact() override;
};


#endif //PROYECTOLL_PROGRAMACIONLL_OXYGENTANK_H