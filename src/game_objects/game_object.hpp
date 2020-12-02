#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cassert>
#include <typeinfo>
#include <unordered_map>

#include "components/icomponent.h"
#include "components/transform.h"

class GameObject
{
public:
    GameObject(const char *name);

    template<typename TComponent>
    TComponent *AddComponent()
    {
        return AddComponent<TComponent>(TComponent());
    }

    template<typename TComponent>
    TComponent *AddComponent(TComponent component)
    {
        static const char* componentKey = typeid(TComponent).name();

        assert(("Multiple components of the same type are not allowed.",
                components.find(componentKey) == components.end()));

        TComponent *componentPtr = (TComponent*) malloc(sizeof(TComponent));
        // std::move?
        memcpy(componentPtr, &component, sizeof(TComponent));
        components[componentKey] = componentPtr;

        componentPtr->OnAttach(this);

        return static_cast<TComponent*>(components[componentKey]);
    }

    template<typename TComponent>
    TComponent *AddComponent(TComponent *component)
    {
        static const char* componentKey = typeid(TComponent).name();

        assert(("Multiple components of the same type are not allowed.",
                components.find(componentKey) == components.end()));

        components[componentKey] = component;
        component->OnAttach(this);

        return component;
    }

    template<typename TComponent>
    bool RemoveComponent()
    {
        return components.erase(typeid(TComponent).name()) != 0;
    }

    template<typename TComponent>
    TComponent *GetComponent()
    {
        if (components.find(typeid(TComponent).name()) == components.end())
            return nullptr;

        return static_cast<TComponent*>(components[typeid(TComponent).name()]);
    }

    virtual void Update();

    const char *Name() const;

    std::string DebugString(std::string linePrefix = "") const;

protected:
    const char *name;
    std::unordered_map<const char*, IComponent*> components;
};

#endif
