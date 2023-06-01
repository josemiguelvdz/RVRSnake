#pragma once

#ifndef __VROOMVROOM_UIBUTTON_HOSTGAME_BUTTON
#define __VROOMVROOM_UIBUTTON_HOSTGAME_BUTTON

#include "UIButton.h"

#include <string>
#include <vector>

/**
The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
*/
class HostGameButton : public UIButton
{
protected:
public:
    HostGameButton(string textureName, int x, int y , int w, int h);
    HostGameButton(Texture* texture, int x, int y , int w, int h);

    //Destroy RenderManager map saved image
    ~HostGameButton();

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

    void initClickAnimation() override;
};

#endif