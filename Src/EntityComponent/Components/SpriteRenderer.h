#pragma once

#ifndef __ENTITYCOMPONENT_SPRITERENDERER
#define __ENTITYCOMPONENT_SPRITERENDERER

#include "Component.h"
#include <string>

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void start() override;
	
	void lateUpdate(const double& dt) override;
};
#endif