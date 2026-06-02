//
// Created by Jose on 30/5/2026.
//
//damage 15

#include "DefectiveRobot.h"

DefectiveRobot::DefectiveRobot(int id, const std::string& name, int damage) : Threat(id,name,damage){}

void DefectiveRobot::activate()
{
    // Silencioso: SimulationEngine maneja el logging vía logEvent()
}

void DefectiveRobot::interact()
{
    this->activate();
}

std::string DefectiveRobot::getType() const
{
    return "Defective Robot";
}
