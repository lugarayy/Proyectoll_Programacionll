//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_ENTITY_H
#define PROYECTOLL_PROGRAMACIONLL_ENTITY_H
#include <string>
#include <iostream>

class Entity {
public:
    Entity(int id,const std::string& name) : id(id), name(name) {};
    virtual std::string getName() const { return name; };
    int getId() const { return id;};
    virtual ~Entity() = default;
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity)
    {
        os << "Entity: " << entity.getId() << " - : " << entity.getName();
        return os;
    }
protected:
    int id;
    std::string name;
};


#endif //PROYECTOLL_PROGRAMACIONLL_ENTITY_H