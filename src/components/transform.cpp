#include "glm/gtx/string_cast.hpp"

#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "components/transform.h"

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale)
{
}

#include <iostream>
glm::mat4 Transform::Model() const
{
    return glm::translate(position) * toMat4(rotation) * glm::scale(glm::mat4(1.f), scale);
}

glm::vec3 Transform::Forward() const
{
    // Excract forward unit vector
    return toMat4(rotation) * glm::vec4(0, 0, 1, 0);
    // Adds in translation..?
    //return toMat4(rotation) * glm::vec4(0, 0, 1, 1);
}

glm::vec3 Transform::Up() const
{
    return toMat4(rotation) * glm::vec4(0, 1, 0, 0);
}

glm::vec3 Transform::Right() const
{
    return toMat4(rotation) * glm::vec4(-1, 0, 0, 0);
}

std::string Transform::DebugString(std::string linePrefix) const
{
    return linePrefix + "Transform:\n" + 
        linePrefix + "\tPosition: " + glm::to_string(position) + "\n" +
        linePrefix + "\tRotation: " + glm::to_string(rotation) + "\n" +
        linePrefix + "\tScale: " + glm::to_string(scale);
}
