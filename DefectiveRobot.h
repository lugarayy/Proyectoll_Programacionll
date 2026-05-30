//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_DEFECTIVEROBOT_H
#define PROYECTOLL_PROGRAMACIONLL_DEFECTIVEROBOT_H
#include "Threat.h"

class DefectiveRobot : public Threat {
    public:
    DefectiveRobot();
    void activate() override;
    ~DefectiveRobot() override;

};


#endif //PROYECTOLL_PROGRAMACIONLL_DEFECTIVEROBOT_H