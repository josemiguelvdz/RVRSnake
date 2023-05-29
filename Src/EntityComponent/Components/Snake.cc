#include "Snake.h"
#include "SnakePart.h"
#include "../Entity.h"

using namespace std;

Snake::Snake(int id) : mName("snake"), mId(id)
{
}


Snake::~Snake()
{
}

void Snake::start()
{
    for (int i = 0; i < STARTING_LENGTH - 2; i++)
        mParts.push_back(new SnakePart(mId));
}

void Snake::update(const double& dt)
{
	// if (!mStaticObject)
	// 	renderManager().setMeshTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
}

string Snake::getName()
{
	return mName;
}

void Snake::setName(string name)
{
	mName = name;
}
