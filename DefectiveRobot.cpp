//
// Created by Jose on 30/5/2026.
//
//damage 15

#include "DefectiveRobot.h"

DefectiveRobot::DefectiveRobot(int id, const std::string& name, int damage) : Threat(id,name,damage){}

void DefectiveRobot::activate(Character &character) {
    character.takeDamage(damage);
}

std::string DefectiveRobot::getType() const
{
    return "Defective Robot";
}
std::string DefectiveRobot::getEffectLog() const {
    return "dealt " + std::to_string(damage) +" damage.";
}
