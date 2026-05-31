//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_DEFECTIVEROBOT_H
#define PROYECTOLL_PROGRAMACIONLL_DEFECTIVEROBOT_H
#include "Threat.h"

class DefectiveRobot : public Threat {
public:
    DefectiveRobot(int id, const std::string& name, int damage);
    ~DefectiveRobot() = default;

    void activate() override;
    void interact() override;
    std::string getType() const override;

};


#endif //PROYECTOLL_PROGRAMACIONLL_DEFECTIVEROBOT_H