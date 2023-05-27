#include "SimpleLerp.h"

float SimpleLerp::Lerp(float a, float b, float f)
{
	return a + f * (b - a);
}