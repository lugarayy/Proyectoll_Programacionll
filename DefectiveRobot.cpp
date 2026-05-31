//
// Created by Jose on 30/5/2026.
//
//damage 15

#include "DefectiveRobot.h"

DefectiveRobot::DefectiveRobot(int id, const std::string& name, int damage) : Threat(id,name,damage){}

void DefectiveRobot::activate()
{
    std::cout << "Attacking, Damage: " << damage << std::endl;
}

void DefectiveRobot::interact()
{
    std::cout << "Defective Robot interact" << std::endl;
    this->activate();
}

std::string DefectiveRobot::getType() const
{
    return "Defective Robot";
}
