#include "Time.h"
#include <chrono>

Time::Time(float targetFrameRate, float timeScale) :
	mTargetFrameRate(targetFrameRate),
	mTimeScale(timeScale), mDeltaTime(0), mCurrentFrameTime(0), mPreviousFrameTime(0)
{
	mTargetDeltaTime = 1 / mTargetFrameRate;

	mCurrentFrameTime = obtainCurrentTime();
	mPreviousFrameTime = mCurrentFrameTime;
}

Time::~Time()
{
}

double Time::update()
{
	mCurrentFrameTime = obtainCurrentTime();
	mDeltaTime = mCurrentFrameTime - mPreviousFrameTime;
	mPreviousFrameTime = mCurrentFrameTime;

	return mDeltaTime;
}

double Time::getDeltaTime()
{
	return mDeltaTime;
}

double Time::timeToNextFrame()
{
	double frameTime = obtainCurrentTime() - mCurrentFrameTime;
	return mTargetDeltaTime - frameTime;
}

long long Time::millisecondsToNextFrame()
{
	return (long long) (timeToNextFrame() * 1000);
}

double Time::getTargetFrameRate()
{
	return mTargetFrameRate;
}

void Time::setTargetFrameRate(float targetFrameRate)
{
	mTargetFrameRate = targetFrameRate;
}

void Time::setTimeScale(float timeScale)
{
	mTimeScale = timeScale;
}

float Time::getTimeScale()
{
	return mTimeScale;
}

double Time::obtainCurrentTime() {
	return std::chrono::duration_cast<std::chrono::duration<double>>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
		* mTimeScale;
}