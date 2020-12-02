#include "levels/level.h"

Level::~Level() 
{
}

void Level::Load()
{
}

std::vector<Portal*> &Level::Portals()
{
    return portals;
}

const std::unordered_map<std::string, DrawableGameObject*> &Level::Objects() const
{
    return objects;
}

DrawableGameObject *Level::Object(std::string objectName)
{
    if (objects.find(objectName) == objects.end())
        return nullptr;

    return objects.find(objectName)->second;
}

/* static */ Level &Level::DefaultEmptyLevel()
{
    static Level defaultEmptyLevel;

    return defaultEmptyLevel;
}
