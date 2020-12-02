#ifndef ICAMERA_H
#define ICAMERA_H

#include "glm/glm.hpp"

//#include "compoents/transform.h"

class ICamera
{
public:
    virtual ~ICamera() {}
    
    virtual float VerticalFOV() const = 0;
    virtual void SetVerticalFOV(float radians) = 0;

    virtual float AspectRatio() const = 0;
    virtual void SetAspectRatio(float aspectRatio) = 0;

    virtual float NearClippingPlane() const = 0;
    virtual void SetNearClippingPlane(float distanceFromCamera) = 0;
    virtual float FarClippingPlane() const = 0;
    virtual void SetFarClippingPlane(float distanceFromCamera) = 0;

    virtual glm::mat4 MVP(const glm::mat4 &model) = 0;
    virtual const glm::mat4 &View() = 0;
    virtual const glm::mat4 &Projection() const = 0;
};

#endif
