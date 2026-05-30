//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_ENTITY_H
#define PROYECTOLL_PROGRAMACIONLL_ENTITY_H
#include <string>

class Entity {
public:
    virtual void interact() const=0;
    virtual std::string getName() const=0;
    virtual void setName() const=0;
    virtual ~Entity() = default;
protected:
    std::string name;
};


#endif //PROYECTOLL_PROGRAMACIONLL_ENTITY_H