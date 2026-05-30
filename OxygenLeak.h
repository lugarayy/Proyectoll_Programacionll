//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_OXYGENLEAK_H
#define PROYECTOLL_PROGRAMACIONLL_OXYGENLEAK_H
#include "Threat.h"

class OxygenLeak : public Threat{
    public:
    OxygenLeak();
    void activate() override;
    ~OxygenLeak() override;
};


#endif //PROYECTOLL_PROGRAMACIONLL_OXYGENLEAK_H