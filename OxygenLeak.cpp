//
// Created by Jose on 30/5/2026.
//

#include "OxygenLeak.h"

OxygenLeak::OxygenLeak() : Threat() {
    damage = 0;
    name = "Oxygen Leak";
}

void OxygenLeak::activate() {
    damage = 5;
}

OxygenLeak::~OxygenLeak() {
}

void OxygenLeak::interact()  {
    std::cout << "Oxygen Leak interact" << std::endl;
    this->activate();
}

std::string OxygenLeak::getName() const {
    return name;
}
