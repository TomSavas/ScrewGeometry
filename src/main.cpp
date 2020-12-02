#include <stdio.h>

#include "glm/gtx/string_cast.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "window.h"
#include "components/transform.h"
#include "components/model.h"
#include "components/player_controller.h"
#include "game.h"
#include "game_objects/camera.h"
#include "game_objects/portal.h"
#include "levels/level1.h"
#include "levels/level2.h"
#include "renderer/framebuffer.h"
#include "renderer/icamera.h"
#include "renderer/single_color_texture.h"
#include "renderer/vertex_array.h"
#include "shaders/shader.h"
#include "shaders/shader_program.h"

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

#include "stb_image.h"

std::string str(const char *string)
{
    return std::string(string);
}

void handleInput(GLFWwindow *window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float verts[] = 
{
     // position         // tex uvs       // colors 
     0.5f,  0.5f, 0.0f,  1.f, 1.f,  1.f, 0.f, 0.f, // top right
     0.5f, -0.5f, 0.0f,  1.f, 0.f,  0.f, 1.f, 0.f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.f, 0.f,  0.f, 0.f, 1.f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.f, 1.f,  1.f, 1.f, 1.f // top left
};
/*
float verts[] = 
{
     // position         // colors       // tex uvs 
     0.5f,  0.0f, -0.5f,  1.f, 0.f, 0.f,  1.f, 1.f, // top right
     0.5f,  0.0f, 0.0f,  0.f, 1.f, 0.f,  1.f, 0.f, // bottom right
     0.0f,  0.0f, 0.0f,  0.f, 0.f, 1.f,  0.f, 0.f, // bottom left
     0.0f,  0.0f, -0.5f,  1.f, 1.f, 1.f,  0.f, 1.f  // top left
};
*/

static float unitCubeVertices[] = 
{
    // position          // tex uvs 
    -0.5f, -0.5f,  0.5f, 0.f, 0.f, // bot left   front wall
    -0.5f,  0.5f,  0.5f, 0.f, 1.f, // top left   front wall
     0.5f,  0.5f,  0.5f, 1.f, 1.f, // top right   front wall
     0.5f, -0.5f,  0.5f, 1.f, 0.f, // bot right   front wall

     0.5f, -0.5f,  0.5f, 0.f, 0.f, // bot left   right wall
     0.5f,  0.5f,  0.5f, 0.f, 1.f, // top left   right wall
     0.5f,  0.5f, -0.5f, 1.f, 1.f, // top right   right wall
     0.5f, -0.5f, -0.5f, 1.f, 0.f, // bot right   right wall

     0.5f, -0.5f, -0.5f, 0.f, 0.f, // bot left   back wall
     0.5f,  0.5f, -0.5f, 0.f, 1.f, // top left   back wall
    -0.5f,  0.5f, -0.5f, 1.f, 1.f, // top right   back wall
    -0.5f, -0.5f, -0.5f, 1.f, 0.f, // bot right   back wall

    -0.5f, -0.5f, -0.5f, 0.f, 0.f, // bot left   left wall
    -0.5f,  0.5f, -0.5f, 0.f, 1.f, // top left   left wall
    -0.5f,  0.5f,  0.5f, 1.f, 1.f, // top right   left wall
    -0.5f, -0.5f,  0.5f, 1.f, 0.f, // bot right   left wall

    -0.5f,  0.5f,  0.5f, 0.f, 0.f, // bot left   top wall
    -0.5f,  0.5f, -0.5f, 0.f, 1.f, // top left   top wall
     0.5f,  0.5f, -0.5f, 1.f, 1.f, // top right   top wall
     0.5f,  0.5f,  0.5f, 1.f, 0.f, // bot right   top wall

    -0.5f,  0.5f,  0.5f, 0.f, 0.f, // bot left   bot wall
    -0.5f,  0.5f, -0.5f, 0.f, 1.f, // top left   bot wall
     0.5f,  0.5f, -0.5f, 1.f, 1.f, // top right   bot wall
     0.5f,  0.5f,  0.5f, 1.f, 0.f, // bot right   bot wall
};

static unsigned int unitCubeIndices[] 
{
    0, 1, 3, // front wall
    1, 2, 3,

    4, 5, 7, // right wall
    5, 6, 7,

    8, 9, 11, // back wall
    9, 10, 11,

    12, 13, 15, // left wall
    13, 14, 15,

    16, 17, 19, // top wall
    17, 18, 19,

    20, 21, 23, // bot wall
    21, 22, 23
};

unsigned int groundIndices[] = 
{
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void Render(Camera *camera, Transform *cameraTransform, glm::vec3 lightPos, bool forPortals = false) 
{
    for (auto &nameWithObject : Game::GetGame().level->Objects())
    {
        std::string name;
        DrawableGameObject *obj;

        std::tie(name, obj) = nameWithObject;

        bool isPortal = false;
        for (Portal *portal : Game::GetGame().level->Portals())
        {                
            if (portal == obj)
            {
                isPortal = true;
            }
        }

#if 0
        if (forPortals && isPortal)
            continue;
#endif

        ShaderProgram *shader;
        if (forPortals && isPortal)
        {                    
            Portal *p = (Portal *)obj;
            //DrawableGameObject *portalCamera = (DrawableGameObject *)(p->RemoteCamera());
            shader = &p->GetShader();

            //const Texture &tex = portalCamera->GetComponent<Model>()->Tex();
            const Texture &tex = p->GetComponent<Model>()->Tex();
            tex.Activate(GL_TEXTURE0);
        }
        else 
        {
            shader = &obj->GetShader();
            const Texture &tex = obj->GetComponent<Model>()->Tex();
            tex.Activate(GL_TEXTURE0);
        }

        //ShaderProgram *shader = &obj->GetShader();

        shader->Use();
        shader->SetUniform("light_pos", lightPos);
        shader->SetUniform("camera_pos", cameraTransform->position);

        shader->SetMVP(camera->MVP(obj->GetComponent<Transform>()->Model()));
        shader->SetUniform("model", obj->GetComponent<Transform>()->Model());
        shader->SetUniform("model_inverse_transpose", glm::transpose(glm::inverse(obj->GetComponent<Transform>()->Model())));
        shader->SetUniform("tex_scale", obj->GetComponent<Model>()->Tex().Scale());

        const VertexArray &vao = obj->GetComponent<Model>()->VAO();
        vao.Bind();

        glDrawElements(GL_TRIANGLES, vao.GetIndexCount(), GL_UNSIGNED_INT, 0);
    }
}

void ClippingPlaneEquation(GLdouble *equation, glm::vec3 normal, glm::vec3 point)
{
    equation[0] = normal.x;
    equation[1] = normal.y;
    equation[2] = normal.z;

    equation[3] = glm::dot(normal, point);
}

int main() 
{
    if (!glfwInit()) {
        fprintf(stderr, "Failed initializing glfw\n");

        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Game::GetGame().window = new Window("Screw Geometry", DEFAULT_WIDTH, DEFAULT_HEIGHT);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed initializing glad\n");
        glfwTerminate();

        return -1;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    GLFWwindow *glfwWindow = Game::GetGame().window->GlfwWindow();
    float lastTime = (float) glfwGetTime();

    Game::GetGame().level = new Level2();
    //Level1 level;
    Game::GetGame().level->Load();

    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    //unsigned int textureColorbuffer;
    //glGenTextures(1, &textureColorbuffer);
    //glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

    Portal *p = reinterpret_cast<Portal*>(Game::GetGame().level->Object("portal1"));

    unsigned int textureColorbuffer = p->Tex()->Id();
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
                                                                                                  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");

    unsigned int otherFramebuffer;
    glGenFramebuffers(1, &otherFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, otherFramebuffer);

    // create a color attachment texture
    //unsigned int textureColorbuffer;
    //glGenTextures(1, &textureColorbuffer);
    //glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

    Portal *op = reinterpret_cast<Portal*>(Game::GetGame().level->Object("portal0"));

    unsigned int otherTextureColorbuffer = op->Tex()->Id();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, otherTextureColorbuffer, 0);

    unsigned int otherRbo;
    glGenRenderbuffers(1, &otherRbo);
    glBindRenderbuffer(GL_RENDERBUFFER, otherRbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); 
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, otherRbo); 
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glm::vec3 baseLightPosition = Game::GetGame().level->Object("light")->GetComponent<Transform>()->position;

    DrawableGameObject *player = Game::GetGame().level->Object("player");
    DrawableGameObject *portal0 = Game::GetGame().level->Object("portal0");
    DrawableGameObject *portal1 = Game::GetGame().level->Object("portal1");

    Texture *portalTex = new Texture("../assets/textures/portal_512.png", true);
    GLdouble *planeEquation = (GLdouble *)malloc(sizeof(GLdouble) * 4);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        float currentTime = (float) glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        handleInput(glfwWindow);

        //logic
        for (auto &it : Game::GetGame().level->Objects())
        {
            it.second->Update();
        }
            
        GameObject *light = Game::GetGame().level->Object("light");
        Transform *lightTransform = light->GetComponent<Transform>();
        lightTransform->position = baseLightPosition + glm::vec3(glm::sin(lastTime * 2.5), 0.f, glm::cos(lastTime * 2.5));
        glm::vec3 lightPos = lightTransform->position;

        // render portals
        #define PORTAL_RECURSE_LEVEL 2
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0xFF);
        for (int i = 0; i < PORTAL_RECURSE_LEVEL; i++)
        {                
            for (auto &portal : Game::GetGame().level->Portals())
            {                    
                Framebuffer *fb = portal->GetComponent<Framebuffer>();
                Portal *attachedPortal = portal->AttachedPortal();
                Camera *portalCamera = portal->RemoteCamera()->GetComponent<Camera>();

                if (!attachedPortal)
                    continue;

                fb->Bind();
                glClearColor(1.f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

                // render portal and set stencil values to one for portal
                // We don't need depth info
                glDepthMask(GL_FALSE);
                // nor color 
                glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

                glStencilFunc(GL_ALWAYS, 1, 0xFF);
                glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

                Transform *attachedPortalTransform = attachedPortal->GetComponent<Transform>();
                Model *attachedPortalModel = attachedPortal->GetComponent<Model>();
                ShaderProgram &shader = attachedPortal->GetShader();

                shader.Use();
                shader.SetUniform("light_pos", lightPos);
                shader.SetUniform("camera_pos", portal->RemoteCamera()->GetComponent<Transform>());
                shader.SetMVP(portalCamera->MVP(attachedPortalTransform->Model()));
                shader.SetUniform("model", attachedPortalTransform->Model());
                shader.SetUniform("model_inverse_transpose", glm::transpose(glm::inverse(attachedPortalTransform->Model())));
                shader.SetUniform("tex_scale", attachedPortalModel->Tex().Scale());

                const VertexArray &vao = attachedPortalModel->VAO();
                vao.Bind();

                //portal->GetComponent<Model>()->Tex().Activate(GL_TEXTURE0);
                portal->RemoteCamera()->GetComponent<Model>()->Tex().Activate(GL_TEXTURE0);

                glDisable(GL_CULL_FACE);
                glDrawElements(GL_TRIANGLES, vao.GetIndexCount(), GL_UNSIGNED_INT, 0);
                glEnable(GL_CULL_FACE);

                // Create a clipping plane where the texture is
                //ClippingPlaneEquation(planeEquation, -attachedPortalTransform->Forward(), attachedPortalTransform->position);
                //glClipPlane(GL_CLIP_PLANE0, planeEquation);

                // render where stencil values are 1
                glDepthMask(GL_TRUE);
                glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
                glStencilFunc(GL_EQUAL, 1, 0xFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

                Render(portalCamera, portal->RemoteCamera()->GetComponent<Transform>(), lightPos, true);
            }
        }

        ClippingPlaneEquation(planeEquation, glm::vec3(0, 0 , -1), glm::vec3(0, 0, 0));
        glClipPlane(GL_CLIP_PLANE0, planeEquation);

        // usual rendering 
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glDisable(GL_STENCIL_TEST);
        Render(player->GetComponent<Camera>(), player->GetComponent<Transform>(), lightPos);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}