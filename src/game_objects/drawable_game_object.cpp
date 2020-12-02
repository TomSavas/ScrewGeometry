#include "drawable_game_object.h"

#include "components/transform.h"

DrawableGameObject::DrawableGameObject(const char *name, ShaderProgram &shaderProgram)
    : GameObject(name), shaderProgram(shaderProgram)
{
    AddComponent<Transform>(Transform());
}

ShaderProgram &DrawableGameObject::GetShader()
{
    return shaderProgram;
}

void DrawableGameObject::SetShader(ShaderProgram &shader)
{
    shaderProgram = shader;
}
