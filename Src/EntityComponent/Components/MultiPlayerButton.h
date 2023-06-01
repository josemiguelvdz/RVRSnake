#pragma once

#ifndef __VROOMVROOM_UIBUTTON_MULTIPLAYER_BUTTON
#define __VROOMVROOM_UIBUTTON_MULTIPLAYER_BUTTON

#include "UIButton.h"

#include <string>
#include <vector>

/**
The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
*/
class MultiPlayerButton : public UIButton
{
protected:

public:
    MultiPlayerButton(string textureName, int x, int y , int w, int h);
    MultiPlayerButton(Texture* texture, int x, int y , int w, int h);

    //Destroy RenderManager map saved image
    ~MultiPlayerButton();

    /**
    Get info for UITransform, create the Sprite and set the start pos
    */
    void start() override;

    /*
    *Update UITransform info to image
    */
    void update(const double& dt) override;

    /*
    * Changes the current scene to the new set scene.
    */
    void execute() override;

    void render() override;
};

#endif