//
// Created by lucig on 29/5/2026.
//

#include "KeyCard.h"
#include "Character.h"
#include "Room.h"

KeyCard::KeyCard(int id, const std::string& name, const std::string& accessLevel) : Item(id, name), accessLevel(accessLevel)
{
}

void KeyCard::use(Character &character) {
   if (accessLevel=="A") {
      character.grantEscapeAccess();
   }
}

std::string KeyCard::getType() const {
   return "KeyCard";
}

std::string KeyCard::getAccessLevel() const
{
   return accessLevel;
}

std::string KeyCard::getDescription() const {
   return " (Escape Item)";
}

