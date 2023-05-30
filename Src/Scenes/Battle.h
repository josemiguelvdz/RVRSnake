#pragma once

#ifndef __SCENES_BATTLE
#define __SCENES_BATTLE

#include "Scene.h"

class Battle : public Scene {
private:
    
public:
    Battle(int snakeNumber);
    ~Battle() override;
};

#endif