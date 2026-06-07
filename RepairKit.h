//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_REPAIRKIT_H
#define PROYECTOLL_PROGRAMACIONLL_REPAIRKIT_H
#include <string>
#include "Item.h"

class RepairKit : public Item
{
private:
    int restore;
public:
    RepairKit(int id, const std::string& name, int restore);
    void use(Character& character) override;
    std::string getType() const override;
    int getRestore() const;
    std::string getDescription() const override;
};


#endif //PROYECTOLL_PROGRAMACIONLL_REPAIRKIT_H