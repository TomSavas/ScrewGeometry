#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "components/icomponent.h"

class Transform 
    : public IComponent
{
public:
    Transform(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
        glm::quat quat = glm::quat_cast(glm::orientate4(glm::vec3(0.0, 0.0, 0.0))),
        glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0));

    glm::mat4 Model() const;

    glm::vec3 Forward() const;
    glm::vec3 Up() const;
    glm::vec3 Right() const;

    virtual std::string DebugString(std::string linePrefix = std::string("")) const override;

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
};

#endif
