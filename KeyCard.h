//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_KEYCARD_H
#define PROYECTOLL_PROGRAMACIONLL_KEYCARD_H
#include <string>
#include "Item.h"

class KeyCard : public Item
{
private:
    std::string accessLevel;
public:
    KeyCard(int id, const std::string& name, const std::string& accessLevel);
    void use(Character& character) override;
    std::string getType() const override;
    std::string getAccessLevel() const;
    std::string getDescription() const override;
};


#endif //PROYECTOLL_PROGRAMACIONLL_KEYCARD_H