#ifndef DRAWABLE_GAME_OBJECT
#define DRAWABLE_GAME_OBJECT

#include "game_objects/game_object.hpp"
#include "shaders/shader_program.h"

class DrawableGameObject 
    : public GameObject
{
public:
    DrawableGameObject(const char *name,
        ShaderProgram &shaderProgram = ShaderProgram::DefaultShader());

    DrawableGameObject(DrawableGameObject &&drawableGameObject) = default;

    ShaderProgram &GetShader();
    void SetShader(ShaderProgram &shader);

private:
    ShaderProgram& shaderProgram;
};

#endif
