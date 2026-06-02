//
// Created by Jose on 30/5/2026.
//

#include "OxygenLeak.h"

OxygenLeak::OxygenLeak(int id, const std::string& name, int damage) : Threat(id, name, damage) {}

void OxygenLeak::interact()
{
    // Silencioso: SimulationEngine maneja el logging vía logEvent()
    this->activate();
}

void OxygenLeak::activate()
{
    // Silencioso: SimulationEngine maneja el logging vía logEvent()
}

std::string OxygenLeak::getType() const
{
    return "Oxygen Leak";
}

