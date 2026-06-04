//
// Created by lucig on 29/5/2026.
//

#include "KeyCard.h"
#include "Character.h"

KeyCard::KeyCard(int id, const string& name, const string& accessLevel) : Item(id, name), accessLevel(accessLevel)
{
}

void KeyCard::use(Character &character) {
   Room* currentRoom = character.getCurrentRoom();
   if (currentRoom == nullptr) {
      return;
   }

   const bool isAtEscapeRoom = currentRoom->getId() == 4;
   const bool hasRequiredAccess = accessLevel == "A";

   if (isAtEscapeRoom && hasRequiredAccess) {
      character.grantEscapeAccess();
   }
}

string KeyCard::getType() const {
   return "KeyCard";
}

string KeyCard::getAccessLevel() const
{
   return accessLevel;
}


