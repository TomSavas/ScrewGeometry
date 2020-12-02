#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "glm/glm.hpp"

#include "components/icomponent.h"
#include "components/transform.h"

class PlayerController
    : public IComponent
{
public:
    virtual void OnAttach(GameObject *gameObject) override;
    virtual void Update() override;

protected:
    Transform *transform;

    glm::f64vec2 lastMousePos;
    float radToHorizon;
    float radToVertical;

    float moveSpeed;
    float mouseSpeed;
};

#endif