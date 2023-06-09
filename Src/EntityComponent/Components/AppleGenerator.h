#pragma once

#ifndef __ENTITYCOMPONENT_APPLE_GENERATOR
#define __ENTITYCOMPONENT_APPLE_GENERATOR

#include "Component.h"
#include "../../Utils/Vector2.h"
#include <string>
#include <vector>

using namespace std;

class Timer;

struct Apple {
    int posX;
    int posY;

	bool eaten;
};

class AppleGenerator : public Component
{
	std::string mName;

	int mAppleWidth;
	int mAppleHeight;
    int mMaxAppleNumber;

    vector<Apple> mApples;
    float mTimeToRespawn;

    Timer* mAppleTimer = nullptr;

public:
	AppleGenerator();
	~AppleGenerator();
	void start() override;
	void update(const double& dt) override;
	void render() override;

	void generateApple(Vector2 position);

	vector<Apple>& getApples();
};
#endif