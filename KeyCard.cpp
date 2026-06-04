//
// Created by lucig on 29/5/2026.
//

#include "KeyCard.h"
#include "Character.h"

KeyCard::KeyCard(int id, const string& name, const string& accessLevel) : Item(id, name), accessLevel(accessLevel)
{
}

void KeyCard::use(Character &character) {}
// No hay ningun uso pa esto jujeji, la victoria se decide por tenerla en el inventario y llegar a la habitacion que la necesita

string KeyCard::getType() const
{
   return "KeyCard";
}

string KeyCard::getAccessLevel() const
{
   return accessLevel;
}


