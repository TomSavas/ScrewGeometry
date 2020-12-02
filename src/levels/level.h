#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <vector>

#include "game_objects/drawable_game_object.h"        

class Portal;

class Level
{
public:
    ~Level();

    virtual void Load();

    virtual std::vector<Portal*> &Portals();
    virtual const std::unordered_map<std::string, DrawableGameObject*> &Objects() const;
    virtual DrawableGameObject *Object(std::string objectName);

    static Level &DefaultEmptyLevel();

protected:
    std::vector<Portal*> portals;
    std::unordered_map<std::string, DrawableGameObject*> objects;
};

#endif
