//
// Created by lucig on 29/5/2026.
//

#include "KeyCard.h"

KeyCard::KeyCard(int id, const string& name, const string& accessLevel) : Item(id, name), accessLevel(accessLevel)
{
}

void KeyCard::use(Character& character)
{
   // character.addKeyCard(accessLevel);
   cout  << "Using KeyCard: +" << accessLevel << " oxygen" << endl;

}

string KeyCard::getType() const
{
   return "KeyCard";
}

string KeyCard::getAccessLevel() const
{
   return accessLevel;
}
