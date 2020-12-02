#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/constants.hpp"

#include "components/icomponent.h"
#include "renderer/icamera.h"
#include "game_objects/game_object.hpp"
#include "levels/level.h"

class Camera 
    : public IComponent
    //: public GameObject, public ICamera
{
public:
    Camera(glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float verticalFOV = 45.f,
            float aspectRatio = 4.f/3.f);

/*
    virtual ~Camera() {}

    virtual float VerticalFOV() const override;
    virtual void SetVerticalFOV(float radians) override;

    virtual float AspectRatio() const override;
    virtual void SetAspectRatio(float aspectRatio) override;

    virtual float NearClippingPlane() const override;
    virtual void SetNearClippingPlane(float distanceFromCamera) override;
    virtual float FarClippingPlane() const override;
    virtual void SetFarClippingPlane(float distanceFromCamera) override;

    virtual glm::mat4 MVP(const glm::mat4 &model) override;
    virtual const glm::mat4 &View() override;
    virtual const glm::mat4 &Projection() const override;
*/

    ~Camera() {}

    float VerticalFOV() const;
    void SetVerticalFOV(float radians);

    float AspectRatio() const;
    void SetAspectRatio(float aspectRatio);

    float NearClippingPlane() const;
    void SetNearClippingPlane(float distanceFromCamera);
    float FarClippingPlane() const;
    void SetFarClippingPlane(float distanceFromCamera);

    glm::mat4 MVP(const glm::mat4 &model);
    const glm::mat4 &View();
    const glm::mat4 &Projection() const;

protected:
    const char *name;

    float verticalFOV;
    float aspectRatio;

    float nearClippingPlane;
    float farClippingPlane;

    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 up;
};

#endif
