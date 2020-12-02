#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>

class GameObject;

class IComponent
{
public:
    virtual ~IComponent() {}

    virtual void OnAttach(GameObject *gameObject) { owner = gameObject; }
    virtual void OnRemove() {}
    virtual void Update() {}
    virtual void Draw() {}

    virtual std::string DebugString(std::string linePrefix = std::string("")) const { return std::string("NO DEBUG STRING"); }

protected:
    GameObject *owner;
};

#endif
