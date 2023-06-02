#pragma once

#ifndef __VROOMVROOM_UIBUTTON_TEXTBOX
#define __VROOMVROOM_UIBUTTON_TEXTBOX

#include "UIButton.h"

#include <string>
#include <vector>

class Text;
class SDL_Color;

class TextBox : public UIButton
{
protected:
    Text* mText;
    string mNameBuffer;
    
    bool mIsWriting;
    int mCharLimit;

    bool lastFramePressed[512];
public:
    TextBox(string btnTextureName, string text, int x, int y , int w, int h, int charLimit);
    TextBox(Texture* btnTexture, Texture* textTexture, int x, int y , int w, int h, int charLimit);

    //Destroy RenderManager map saved image
    ~TextBox();

    /**
    Get info for UITransform, create the Sprite and set the start pos
    */
    void start() override;

    /*
    *Update UITransform info to image
    */
    void update(const double& dt) override;

    void render() override;

    void setText(string text, SDL_Color color);
    string getText();
};

#endif