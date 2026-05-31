//
// Created by lucig on 29/5/2026.
//

#include "KeyCard.h"
#include "Character.h"

KeyCard::KeyCard(int id, const string& name, const string& accessLevel) : Item(id, name), accessLevel(accessLevel)
{
}

void KeyCard::use(Character& character)
{
   // character.addKeyCard(accessLevel);
   cout  << "Using KeyCard: Unlocking " << accessLevel << " to the room" << endl;

}

string KeyCard::getType() const
{
   return "KeyCard";
}

string KeyCard::getAccessLevel() const
{
   return accessLevel;
}

void KeyCard::interact()
{
   cout << "You found a keyCard" << endl;
}
