//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_REPAIRKIT_H
#define PROYECTOLL_PROGRAMACIONLL_REPAIRKIT_H

#include "Item.h"
//#include "Character.h"

class RepairKit : public Item
{
private:
    int restore;
public:
    RepairKit(int id, const string& name, int restore);
    void use(Character& character) override;
    string getType() const override;
    int getRestore() const;
};


#endif //PROYECTOLL_PROGRAMACIONLL_REPAIRKIT_H