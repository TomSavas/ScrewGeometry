#include "levels/level1.h"

#include <utility>

#include "OBJ_Loader.h"

#include "components/model.h"
#include "components/transform.h"


Level1::~Level1()
{
}

void Level1::Load() 
{
    /*
    objl::Loader loader;

    loader.LoadFile("../assets/models/cube.obj");

    Model cubeModel(loader.LoadedMeshes[0]);

    DrawableGameObject *ground = new DrawableGameObject("ground", *this);
    ground->GetComponent<Transform>()->position.y = -0.5f;
    ground->GetComponent<Transform>()->scale = glm::vec3(10, 0.01f, 10);
    ground->AddComponent<Model>(cubeModel);
    objects.insert(std::make_pair(ground->Name(), ground));

    DrawableGameObject *closeRightCube = new DrawableGameObject("closeRightCube", *this);
    closeRightCube->GetComponent<Transform>()->position = glm::vec3(2, 0, 0);
    closeRightCube->GetComponent<Transform>()->scale = glm::vec3(.25f);
    closeRightCube->AddComponent<Model>(cubeModel);
    objects.insert(std::make_pair(closeRightCube->Name(), closeRightCube));

    DrawableGameObject *closeLeftCube = new DrawableGameObject("closeLeftCube", *this);
    closeLeftCube->GetComponent<Transform>()->position = glm::vec3(-2, 0, 0);
    closeLeftCube->GetComponent<Transform>()->scale = glm::vec3(.25f);
    closeLeftCube->AddComponent<Model>(cubeModel);
    objects.insert(std::make_pair(closeLeftCube->Name(), closeLeftCube));

    DrawableGameObject *farRightCube = new DrawableGameObject("farRightCube", *this);
    farRightCube->GetComponent<Transform>()->position = glm::vec3(2, 0, -2);
    farRightCube->GetComponent<Transform>()->scale = glm::vec3(.25f);
    farRightCube->AddComponent<Model>(cubeModel);
    objects.insert(std::make_pair(farRightCube->Name(), farRightCube));

    DrawableGameObject *farLeftCube = new DrawableGameObject("farLeftCube", *this);
    farLeftCube->GetComponent<Transform>()->position = glm::vec3(-2, 0, -2);
    farLeftCube->GetComponent<Transform>()->scale = glm::vec3(.25f);
    farLeftCube->AddComponent<Model>(cubeModel);
    objects.insert(std::make_pair(farLeftCube->Name(), farLeftCube));

    DrawableGameObject *furtherLeftCube = new DrawableGameObject("furtherLeftCube", *this);
    furtherLeftCube->GetComponent<Transform>()->position = glm::vec3(-2, 0, -4);
    furtherLeftCube->GetComponent<Transform>()->scale = glm::vec3(.25f);
    furtherLeftCube->AddComponent<Model>(cubeModel);
    objects.insert(std::make_pair(furtherLeftCube->Name(), furtherLeftCube));

    DrawableGameObject *furthestLeftCube = new DrawableGameObject("furthestLeftCube", *this);
    furthestLeftCube->GetComponent<Transform>()->position = glm::vec3(-2, 0, -10);
    furthestLeftCube->GetComponent<Transform>()->scale = glm::vec3(.25f);
    furthestLeftCube->AddComponent<Model>(cubeModel);
    objects.insert(std::make_pair(furthestLeftCube->Name(), furthestLeftCube));
    */
}