//
// Created by lucig on 29/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_KEYCARD_H
#define PROYECTOLL_PROGRAMACIONLL_KEYCARD_H

#include "Item.h"

class KeyCard : public Item
{
private:
    string accessLevel;
public:
    KeyCard(int id, const string& name, const string& accessLevel);
    void use(Character& character) override;
    string getType() const override;
    string getAccessLevel() const;
};


#endif //PROYECTOLL_PROGRAMACIONLL_KEYCARD_H