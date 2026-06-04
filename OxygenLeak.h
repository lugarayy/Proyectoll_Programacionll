//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_OXYGENLEAK_H
#define PROYECTOLL_PROGRAMACIONLL_OXYGENLEAK_H
#include "Threat.h"
#include <string>

class OxygenLeak : public Threat {
public:
    OxygenLeak(int id, const std::string& name, int damage);
    ~OxygenLeak() = default;
    void activate(Character &character) override;
    std::string getType() const override;
};


#endif //PROYECTOLL_PROGRAMACIONLL_OXYGENLEAK_H