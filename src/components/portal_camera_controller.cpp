#include "components/portal_camera_controller.h"

PortalCameraController::PortalCameraController(Transform *player, Transform *owningPortal, Transform *trackedPortal)
    : player(player), owningPortal(owningPortal), trackedPortal(trackedPortal)
{
}

void PortalCameraController::Update() 
{
    if (!trackedPortal)
        return;

    glm::vec3 playerToOwningPortal = owningPortal->position - player->position;
    glm::quat owningToTrackedPortal = owningPortal->rotation * glm::inverse(trackedPortal->rotation);

    owner->GetComponent<Transform>()->rotation = owningToTrackedPortal * player->rotation;
    owner->GetComponent<Transform>()->position = trackedPortal->position - glm::mat3_cast(owningToTrackedPortal) * playerToOwningPortal;

    //owner->GetComponent<Camera>()->SetNearClippingPlane(glm::length(playerToOwningPortal));
}

void PortalCameraController::SetTrackedPortal(Transform *portal)
{
    trackedPortal = portal;
}