#include "glm/glm.hpp"

using glm::cross;
using glm::dot;
using glm::normalize;
using glm::vec3;

class Camera {
	
public:

	Camera() {

		position = vec3();
		direction = normalize(vec3());
	}

	Camera(vec3 position, vec3 direction) : position(position), direction(direction){


	}

private:
	
	vec3 position;
	vec3 direction;

	vec3 ux;
	vec3 uy;
};