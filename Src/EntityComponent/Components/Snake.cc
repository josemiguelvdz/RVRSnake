#include "Snake.h"
#include "SnakePart.h"
#include "../Entity.h"

#include <iostream>

using namespace std;

Snake::Snake(int id, Vector2 position, Vector2 orientation) : mName("snake"), mId(id), 
	mPosition(position * BOX_SIZE), mOrientation(orientation * BOX_SIZE)
{
	mSpeed = 5.0f;
}


Snake::~Snake()
{
}

void Snake::start()
{
    for (int i = 0; i < STARTING_LENGTH; i++)
        mParts.push_back(new SnakePart(mId, mPosition - mOrientation * i, mOrientation));
}

void Snake::update(const double& dt)
{
	for(auto part : mParts)
		part->update(dt, mSpeed);
}

void Snake::render()
{
	auto part = mParts.begin();
	auto nextPart = ++mParts.begin();

	for(int i = 0; i < mParts.size(); i++, part++, nextPart++)
		(*part)->render(nextPart == mParts.end() ? nullptr : *nextPart, i == 0);
}

string Snake::getName()
{
	return mName;
}

void Snake::setName(string name)
{
	mName = name;
}
