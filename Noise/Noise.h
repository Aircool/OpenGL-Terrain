#pragma once
#define _USE_MATH_DEFINES
#include <cmath> 
#include <cstdlib>

#include "glm/glm.hpp"
#include "../Constants.h"

using glm::vec3;
using glm::dot;

class Noise {

public:

	Noise(int seed);

	void initArrays();
	vec3** Gradient();
	vec3** Perlin(vec3** gradients, int period);
	vec3** FBM();

	float lerp(float x, float y, float weight);
	float fade(float t);

	vec3** getFBM(){

		return _FBM;
	}

private:

	vec3** _FBM;
};