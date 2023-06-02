#pragma once

#ifndef __VROOMVROOM_UIBUTTON_JOINGAME_BUTTON
#define __VROOMVROOM_UIBUTTON_JOINGAME_BUTTON

#include "UIButton.h"

#include <string>
#include <vector>

class TextBox;

/**
The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
*/
class JoinGameButton : public UIButton
{
protected:
    TextBox* ipTextBox;
    
public:
    JoinGameButton(string textureName, int x, int y , int w, int h);
    JoinGameButton(Texture* texture, int x, int y , int w, int h);

    //Destroy RenderManager map saved image
    ~JoinGameButton();

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

    void opacityUpdate();
};

#endif