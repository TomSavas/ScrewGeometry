//#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "game_objects/camera.h"

Camera::Camera(glm::vec3 up, float verticalFOV,
        float aspectRatio)
    : verticalFOV(verticalFOV), aspectRatio(aspectRatio),
      nearClippingPlane(0.1f), farClippingPlane(100000.f),
      up(up)
{
    projection = glm::perspective(glm::radians(verticalFOV), aspectRatio, nearClippingPlane, farClippingPlane);
}

float Camera::VerticalFOV() const
{
    return verticalFOV;
}

void Camera::SetVerticalFOV(float radians) 
{
    verticalFOV = radians;
    projection = glm::perspective(verticalFOV, aspectRatio, nearClippingPlane, farClippingPlane);
}

float Camera::AspectRatio() const 
{
    return aspectRatio;
}

void Camera::SetAspectRatio(float ratio)
{
    aspectRatio = ratio;
    projection = glm::perspective(verticalFOV, aspectRatio, nearClippingPlane, farClippingPlane);
}

float Camera::NearClippingPlane() const
{
    return nearClippingPlane;
}

void Camera::SetNearClippingPlane(float distanceFromCamera)
{
    nearClippingPlane = distanceFromCamera;
    projection = glm::perspective(verticalFOV, aspectRatio, nearClippingPlane, farClippingPlane);
}

float Camera::FarClippingPlane() const 
{
    return farClippingPlane;
}

void Camera::SetFarClippingPlane(float distanceFromCamera)
{
    farClippingPlane = distanceFromCamera;
    projection = glm::perspective(verticalFOV, aspectRatio, nearClippingPlane, farClippingPlane);
}

glm::mat4 Camera::MVP(const glm::mat4 &model)
{
    return Projection() * View() * model;
}

const glm::mat4 &Camera::View() 
{
    //view = glm::lookAt(GetComponent<Transform>()->position, GetComponent<Transform>()->position + GetComponent<Transform>()->Forward(), up);
    //view = glm::translate(glm::toMat4(glm::quatLookAt(glm::normalize(GetComponent<Transform>()->Forward()), up)), -GetComponent<Transform>()->position);
    //view = glm::lookAt(GetComponent<Transform>()->position, glm::vec3(0, 0, 0), up);
    //view = glm::translate(glm::toMat4(GetComponent<Transform>()->rotation), -GetComponent<Transform>()->position);
    //view = glm::translate(GetComponent<Transform>()->position) * glm::toMat4(GetComponent<Transform>()->rotation) ;
    //view = GetComponent<Transform>()->Model();
    //view = glm::identity<glm::mat4>();
    Transform *t = owner->GetComponent<Transform>();

    view = glm::lookAt(t->position, t->position + t->Forward(), up);
    //view = glm::toMat4(GetComponent<Transform>()->rotation) * glm::translate(GetComponent<Transform>()->position);
    return view;
}

const glm::mat4 &Camera::Projection() const
{
    return projection;
}
