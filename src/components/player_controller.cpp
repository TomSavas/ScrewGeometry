#include "components/player_controller.h"

#include "game.h"
#include "game_objects/game_object.hpp"
#include "components/transform.h"
#include "glm/gtx/string_cast.hpp"

void PlayerController::OnAttach(GameObject *gameObject)
{
    //glfwSetInputMode(Game::GetGame().window->GlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    transform = gameObject->GetComponent<Transform>();

    moveSpeed = 0.1f;
    mouseSpeed = 0.005f;
    radToVertical = 0.f;
    radToHorizon = 0.f;
}


void PlayerController::Update()
{
    static Window *window = Game::GetGame().window;

    if (glfwGetKey(window->GlfwWindow(), GLFW_KEY_W))   
        transform->position += glm::normalize(transform->Forward()) * moveSpeed;
    if(glfwGetKey(window->GlfwWindow(), GLFW_KEY_S))   
        transform->position -= glm::normalize(transform->Forward()) * moveSpeed;
    if(glfwGetKey(window->GlfwWindow(), GLFW_KEY_D))   
        transform->position += glm::normalize(transform->Right()) * moveSpeed;
    if(glfwGetKey(window->GlfwWindow(), GLFW_KEY_A))   
        transform->position -= glm::normalize(transform->Right()) * moveSpeed;
    //if(glfwGetKey(window->GlfwWindow(), GLFW_KEY_SPACE))   
    //    transform->position += glm::normalize(transform->Up()) * moveSpeed;
    //if(glfwGetKey(window->GlfwWindow(), GLFW_KEY_LEFT_SHIFT))   
    //    transform->position -= glm::normalize(transform->Up()) * moveSpeed;
    transform->position.y = 1.f;

    glm::f64vec2 mousePos;
    glfwGetCursorPos(window->GlfwWindow(), &mousePos.x, &mousePos.y);
    glm::f64vec2 mousePosDif = mousePos - lastMousePos;
    lastMousePos = mousePos;

    radToVertical += mousePosDif.x * mouseSpeed;
    while(radToVertical > glm::pi<float>() * 2)
        radToVertical -= glm::pi<float>() * 2;
    while(radToVertical < -glm::pi<float>() * 2)
        radToVertical += glm::pi<float>() * 2;

    radToHorizon += mousePosDif.y * mouseSpeed;
    radToHorizon = std::min(std::max(radToHorizon, -glm::pi<float>() / 2 + 0.01f), glm::pi<float>() / 2 - 0.01f);

    transform->rotation = glm::quat(glm::vec3(radToHorizon, -radToVertical, 0.f));

    // simulate gravity
    //transform->position.y -= 0.1f;
    //if (transform->position.y < 0.5f)
    //    transform->position.y = 0.5f;
}