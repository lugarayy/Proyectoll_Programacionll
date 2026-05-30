//
// Created by Jose on 30/5/2026.
//

#include "DefectiveRobot.h"

DefectiveRobot::DefectiveRobot() : Threat() {
    name = "Defective Robot";
    damage = 0;
}

void DefectiveRobot::activate() {
     damage = 15;
}

DefectiveRobot::~DefectiveRobot() {
}
