#include "levels/level2.h"

#include <utility>

#include "GLFW/glfw3.h"

#include "OBJ_Loader.h"

#include "game_objects/camera.h"
#include "game_objects/portal.h"
#include "components/model.h"
#include "components/transform.h"
#include "components/player_controller.h"
#include "components/portal_camera_controller.h"
#include "game.h"

#include "renderer/single_color_texture.h"
#include "renderer/framebuffer.h"
#include "renderer/renderbuffer.h"

Framebuffer *RenderTarget(glm::ivec2 size)
{
    Framebuffer *fb = new Framebuffer();
    fb->Bind();

    Texture *tex = new Texture(size);
    tex->Load();
    tex->Bind();
    fb->SetRenderTexture(tex);

    Renderbuffer *depthStencilTarget = new Renderbuffer(size, GL_DEPTH24_STENCIL8);
    depthStencilTarget->Bind();
    fb->SetDepthStencilTarget(depthStencilTarget);
    fb->CheckComplete();
    fb->Unbind();

    return fb;
}

Level2::~Level2()
{
}

void Level2::Load() 
{
    objl::Loader loader;

    loader.LoadFile("../assets/models/cube.obj");

    Texture *orangeTexture = new Texture("../assets/textures/dev_orange_256.jpeg", true, glm::vec2(10.f, 10.f));
    //Texture *orangeTexture = new SingleColorTexture(255, 0, 0);
    Texture *greyTexture = new Texture("../assets/textures/dev_grey_256.jpeg", true, glm::vec2(10.f, 10.f));

    Model orangeCubeModel(loader.LoadedMeshes[0], *orangeTexture);
    Model greyCubeModel(loader.LoadedMeshes[0], *greyTexture);

    // light
    unsigned char lightColor[3] = { 255, 255, 255 };
    Texture *lightTexture = new SingleColorTexture(lightColor[0], lightColor[1], lightColor[2]);

    DrawableGameObject *light = new DrawableGameObject("light");
    light->GetComponent<Transform>()->position = glm::vec3(0.f, 3.f, 0.f);
    light->GetComponent<Transform>()->scale = glm::vec3(0.25f);
    light->AddComponent<Model>(Model(loader.LoadedMeshes[0], *lightTexture));
    //light->AddComponent<PointLight>(PointLight(lightColor[0], lightColor[1], lightColor[2]));
    objects.insert(std::make_pair(light->Name(), light));

    // ground
    DrawableGameObject *ground = new DrawableGameObject("ground");
    ground->GetComponent<Transform>()->scale = glm::vec3(10, 0.01f, 10);
    ground->AddComponent<Model>(greyCubeModel);
    objects.insert(std::make_pair(ground->Name(), ground));

    // tunnel
    DrawableGameObject *leftWall = new DrawableGameObject("leftTunnelWall");
    leftWall->GetComponent<Transform>()->position.x = 5.f;
    leftWall->GetComponent<Transform>()->position.y = 1.f;
    leftWall->GetComponent<Transform>()->scale = glm::vec3(0.25f, 1.f, 5.f);
    leftWall->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(leftWall->Name(), leftWall));

    DrawableGameObject *rightWall = new DrawableGameObject("rightTunnelWall");
    rightWall->GetComponent<Transform>()->position.x = 3.f;
    rightWall->GetComponent<Transform>()->position.y = 1.f;
    rightWall->GetComponent<Transform>()->scale = glm::vec3(0.25f, 1.f, 5.f);
    rightWall->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(rightWall->Name(), rightWall));

    DrawableGameObject *topWall = new DrawableGameObject("topTunnelWall");
    topWall->GetComponent<Transform>()->position.x = 4.f;
    topWall->GetComponent<Transform>()->position.y = 1.75f;
    topWall->GetComponent<Transform>()->scale = glm::vec3(.75f, 0.25f, 5.f);
    topWall->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(topWall->Name(), topWall));

    // doorway
    DrawableGameObject *leftBeam = new DrawableGameObject("leftDoorwayBeam");
    leftBeam->GetComponent<Transform>()->position = glm::vec3(-5.f, 1.f, -3.f);
    leftBeam->GetComponent<Transform>()->scale = glm::vec3(0.25f, 1.f, 0.25f);
    leftBeam->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(leftBeam->Name(), leftBeam));

    DrawableGameObject *rightBeam = new DrawableGameObject("rightDoorwayBeam");
    rightBeam->GetComponent<Transform>()->position = glm::vec3(-3.f, 1.f, -3.f);
    rightBeam->GetComponent<Transform>()->scale = glm::vec3(0.25f, 1.f, 0.25f);
    rightBeam->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(rightBeam->Name(), rightBeam));

    DrawableGameObject *topBeam = new DrawableGameObject("topDoorwayBeam");
    topBeam->GetComponent<Transform>()->position = glm::vec3(-4.f, 1.75f, -3.f);
    topBeam->GetComponent<Transform>()->scale = glm::vec3(.75f, 0.25f, 0.25f);
    topBeam->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(topBeam->Name(), topBeam));

        //Framebuffer *fb = new Framebuffer();
        //fb->Bind();

        //glm::ivec2 renderTargetSize(800, 600);
        //Texture *renderTarget = new Texture(renderTargetSize);
        //renderTarget->Load();
        //fb->SetRenderTexture(renderTarget);

        //Renderbuffer *depthStencilTarget = new Renderbuffer(renderTargetSize, GL_DEPTH24_STENCIL8);
        //depthStencilTarget->Bind();
        //fb->SetDepthStencilTarget(depthStencilTarget);
        //fb->CheckComplete();
        //fb->Unbind();

    //ShaderProgram *portalShader = new ShaderProgram("../src/shaders/default.vert", "../src/shaders/portal.frag");
    //DrawableGameObject *doorwayPortal = new DrawableGameObject("doorwayPortal", *portalShader);
    //doorwayPortal->GetComponent<Transform>()->position = glm::vec3(-4.f, .75f, -3.f);
    //doorwayPortal->GetComponent<Transform>()->scale = glm::vec3(1.5f, 1.5f, 1.f);
    //doorwayPortal->AddComponent<Framebuffer>(fb);
    //doorwayPortal->AddComponent<Model>(Model::Quad(glm::vec3(1), *renderTarget));
    //    //doorwayPortal->AddComponent<Model>(Model::Quad(glm::vec3(1), Texture::DefaultTexture()));
    //objects.insert(std::make_pair(doorwayPortal->Name(), doorwayPortal));

    // portal
    DrawableGameObject *targetPortalLeftBeam = new DrawableGameObject("targetPortalLeftBeam");
    targetPortalLeftBeam->GetComponent<Transform>()->position = glm::vec3(-5.f, 1.f, 5.f);
    targetPortalLeftBeam->GetComponent<Transform>()->scale = glm::vec3(0.25f, 1.f, 0.25f);
    targetPortalLeftBeam->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(targetPortalLeftBeam->Name(), targetPortalLeftBeam));

    DrawableGameObject *targetPortalRightBeam = new DrawableGameObject("targetPortalRightBeam");
    targetPortalRightBeam->GetComponent<Transform>()->position = glm::vec3(-3.f, 1.f, 5.f);
    targetPortalRightBeam->GetComponent<Transform>()->scale = glm::vec3(0.25f, 1.f, 0.25f);
    targetPortalRightBeam->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(targetPortalRightBeam->Name(), targetPortalRightBeam));

    DrawableGameObject *targetPortalTopBeam = new DrawableGameObject("targetPortalTopBeam");
    targetPortalTopBeam->GetComponent<Transform>()->position = glm::vec3(-4.f, 1.75f, 5.f);
    targetPortalTopBeam->GetComponent<Transform>()->scale = glm::vec3(.75f, 0.25f, 0.25f);
    targetPortalTopBeam->AddComponent<Model>(orangeCubeModel);
    objects.insert(std::make_pair(targetPortalTopBeam->Name(), targetPortalTopBeam));

    //DrawableGameObject *portalTarget = new DrawableGameObject("portalTarget");
    //portalTarget->GetComponent<Transform>()->position = glm::vec3(-4.f, .75f, 5.f);
    //portalTarget->GetComponent<Transform>()->scale = glm::vec3(1.5f, 1.5f, 1.f);
    //portalTarget->AddComponent<Model>(Model::Quad(glm::vec3(1), *(new SingleColorTexture(0, 255, 0))));
    //    //doorwayPortal->AddComponent<Model>(Model::Quad(glm::vec3(1), Texture::DefaultTexture()));
    //objects.insert(std::make_pair(portalTarget->Name(), portalTarget));

    DrawableGameObject *player = new DrawableGameObject("player");
    player->GetComponent<Transform>()->position = glm::vec3(2.f, 1.f, 0);
    player->GetComponent<Transform>()->scale = glm::vec3(0.3f, 1.f, 0.3f);
    player->AddComponent<PlayerController>();
    player->AddComponent<Model>(new Model(loader.LoadedMeshes[0], SingleColorTexture::DefaultTexture()));
    player->AddComponent<Camera>(new Camera());

    //DrawableGameObject *portalCamera = new DrawableGameObject("portalCamera");
    //portalCamera->GetComponent<Transform>()->position = glm::vec3(2.f, 1.f, 0);
    //portalCamera->GetComponent<Transform>()->scale = glm::vec3(0.1f);
    //portalCamera->AddComponent<Model>(new Model(loader.LoadedMeshes[0], SingleColorTexture::DefaultTexture()));
    //portalCamera->AddComponent<Camera>(new Camera());
    //portalCamera->AddComponent<PortalCameraController>(new PortalCameraController(player->GetComponent<Transform>(), doorwayPortal->GetComponent<Transform>(), portalTarget->GetComponent<Transform>()->position));
    //objects.insert(std::make_pair(portalCamera->Name(), portalCamera));

    // portals
    Portal *portal0 = new Portal("portal0", player, RenderTarget(glm::ivec2(800, 600)));
    portal0->GetComponent<Transform>()->position = glm::vec3(2.749f, .75f, 3.f);
    portal0->GetComponent<Transform>()->scale = glm::vec3(1.5f, 1.5f, 1.f);
    portal0->GetComponent<Transform>()->rotation = glm::quat_cast(glm::eulerAngleY(-glm::pi<float>() / 2.f));
    //portal0->AddComponent<Framebuffer>(fb);
    Portal *portal1 = new Portal("portal1", player, RenderTarget(glm::ivec2(800, 600)));
    portal1->GetComponent<Transform>()->position = glm::vec3(-4.f, .75f, -3.f);
    portal1->GetComponent<Transform>()->scale = glm::vec3(1.5f, 1.5f, 1.f);
    //portal1->AddComponent<Framebuffer>(fb);

    //objects.insert(std::make_pair("portalCamera1", reinterpret_cast<DrawableGameObject*>(portal1->RemoteCamera())));
    //objects.insert(std::make_pair("portalCamera0", reinterpret_cast<DrawableGameObject*>(portal0->RemoteCamera())));

    portal0->AttachPortal(portal1);
    portal1->AttachPortal(portal0);

    objects.insert(std::make_pair(portal0->Name(), portal0));
    objects.insert(std::make_pair(portal1->Name(), portal1));

    portals.push_back(portal0);
    portals.push_back(portal1);

    // TODO: update player after the portals, otherwise we have stuttering
    objects.insert(std::make_pair(player->Name(), player));
}