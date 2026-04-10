#pragma once
#include "raylib.h"
#include <algorithm>

inline float GetRandomFloat()
{
	return GetRandomValue(0, 10000) / (float)10000;
}

inline float GetRandomFloat(float max)
{
	return GetRandomFloat() * max;
}

inline float GetRandomFloat(float min, float max)
{
	if (min > max) std::swap(min, max);
	return GetRandomValue(min, max);
}