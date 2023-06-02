#pragma once

#ifndef __SCENES_COLOR_SELECTION
#define __SCENES_COLOR_SELECTION

#include "Scene.h"

#include <vector>
#include <string>

class ColorSelection : public Scene {
private:
    
public:
    ColorSelection(std::vector<std::string> names, std::vector<int> colors, bool isHost);
    ~ColorSelection() override;
};

#endif