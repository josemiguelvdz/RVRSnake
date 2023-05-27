#pragma once

#ifndef __UTILS_SIMPLE_LERP
#define __UTILS_SIMPLE_LERP

/**
Class SimpleLerp: Allows to interpolate between two numerical values.
*/
class SimpleLerp
{

public:
	/**
	* Returns the linear interpolation between "a" and "b" by a factor of "f".
	*
	* @param a Starting value of the interpolation.
	* @param b Ending value of the interpolation.
	* @param f Factor by which to interpolate between "a" and "b".
	* @return Linear interpolation between "a" and "b" by a factor of "f".
	*/
	static float Lerp(float a, float b, float f);

};

#endif