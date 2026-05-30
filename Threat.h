//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_THREAT_H
#define PROYECTOLL_PROGRAMACIONLL_THREAT_H
#include "Entity.h"
#include "Room.h"

class Threat : public Entity {
public:
    virtual void activate()=0;
    virtual ~Threat()= default;
    protected:
   int damage;
};


#endif //PROYECTOLL_PROGRAMACIONLL_THREAT_H