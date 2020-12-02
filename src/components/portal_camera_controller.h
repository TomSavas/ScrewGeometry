#ifndef PORTAL_CAMERA_CONTROLLER
#define PORTAL_CAMERA_CONTROLLER

#include "glm/glm.hpp"

#include "game_objects/camera.h"

class Camera;
class GameObject;
class Transform;

/**
 * Tracks player movement around a pair portal
 */
class PortalCameraController
    : public IComponent
{
public:
    PortalCameraController(Transform *player, Transform *owningPortal, Transform *trackedPortal = nullptr);

    virtual void Update() override;

    void SetTrackedPortal(Transform *portal);

private:
    Transform *player;

    // The portal that camera's view will be rendered to
    Transform *owningPortal;
    // The portal camera is revolving around
    Transform *trackedPortal;
};

#endif