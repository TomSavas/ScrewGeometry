#include "glm/glm.hpp"

#include "components/model.h"
#include "game_objects/camera.h"
#include "components/portal_camera_controller.h"
#include "game_objects/portal.h"
#include "renderer/texture.h"

//debug
#include "OBJ_Loader.h"

Portal::Portal(const char *name, GameObject *player, Framebuffer *framebuffer)
    : DrawableGameObject(name, *new ShaderProgram("../src/shaders/default.vert", "../src/shaders/portal.frag")), player(player)
{
    AddComponent<Framebuffer>(framebuffer);

    AddComponent<Model>(Model::Quad(glm::vec3(1.f), *framebuffer->Tex()));

    camera = new DrawableGameObject("portal_camera");
    camera->GetComponent<Transform>()->scale = glm::vec3(0.2f);
    camera->AddComponent<Camera>();
    camera->AddComponent<PortalCameraController>(new PortalCameraController(player->GetComponent<Transform>(),
        GetComponent<Transform>()));

    // debug
    objl::Loader loader;
    loader.LoadFile("../assets/models/cube.obj");
    camera->AddComponent<Model>(new Model(loader.LoadedMeshes[0], Texture::DefaultTexture()));
}

Portal::~Portal()
{
    delete tex;
    delete shader;
    // leaking camera
    // leaking portal camera controller. should really use smart pointers at this point
    delete camera;
}

void Portal::Update() 
{
    camera->Update();
    GameObject::Update();
}

void Portal::AttachPortal(Portal *portal)
{
    attachedPortal = portal;

    camera->GetComponent<PortalCameraController>()->SetTrackedPortal(portal->GetComponent<Transform>());
}

Portal *Portal::AttachedPortal()
{
    return attachedPortal;
}

GameObject *Portal::RemoteCamera() 
{
    return camera;
}

Texture *Portal::Tex()
{
    return GetComponent<Framebuffer>()->Tex();
}