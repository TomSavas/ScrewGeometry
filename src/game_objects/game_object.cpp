#include "game_objects/game_object.hpp"        

GameObject::GameObject(const char *name) 
    : name(name)
{
}

void GameObject::Update()
{
    for(auto &it : components)
        if (dynamic_cast<IComponent*>(it.second))
            it.second->Update();
}

const char *GameObject::Name() const
{
    return name;
}

std::string GameObject::DebugString(std::string linePrefix) const
{
    std::string debugString = linePrefix + name + ":\n";

    for (auto &it : components)
        debugString += it.second->DebugString(linePrefix + "\t") + "\n";

    return debugString;
}
