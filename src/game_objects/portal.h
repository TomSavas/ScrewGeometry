#ifndef PORTAL_H
#define PORTAL_H

#include "game_objects/drawable_game_object.h"
#include "renderer/texture.h"
#include "renderer/framebuffer.h"

class ShaderProgram;
class Texture;

/**
 * Represents a portal game object. A portal has a quad that displays 
 * the view of a camera that tracks around the attached portal.
 */
class Portal
    : public DrawableGameObject
{
public:
    Portal(const char *name, GameObject *player, Framebuffer *framebuffer);
    ~Portal();

    virtual void Update() override;

    void AttachPortal(Portal *portal);
    Portal *AttachedPortal();

    GameObject *RemoteCamera();
    // TEMP: texture should probably be a component..?
    Texture *Tex();

private:
    Portal *attachedPortal;

    GameObject *player;
    GameObject *camera;

    Texture *tex;
    ShaderProgram *shader;
};

#endif