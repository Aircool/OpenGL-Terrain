#include "glm/glm.hpp"

using glm::cross;
using glm::dot;
using glm::normalize;
using glm::vec3;

class Camera {
	
public:

	enum Directions {

		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3,
		FORWARD = 4,
		BACKWARD = 5
	};

	Camera() {

		this->position = vec3(0.0f, 3.0f, -3.0f);
		this->direction = normalize(vec3(0.0f, -1.0f, 1.0f));
		
		calculateBasis();
	}

	Camera(vec3 position, vec3 direction) : position(position), direction(normalize(direction)){

		calculateBasis();
	}

	void move(Directions d){

		float TICK = 2.0f / 60;

		switch(d){

			case UP:		this->position += this->uy * TICK;
				break;
			case DOWN:		this->position -= this->uy * TICK;
				break;
			case LEFT:		this->position += this->ux * TICK;
				break;
			case RIGHT:		this->position -= this->ux * TICK;
				break;
			case FORWARD:	this->position += this->direction * TICK;
				break;
			case BACKWARD:	this->position -= this->direction * TICK;
				break;
		}
	}

	void rotate(Directions d){

		float TICK = 2.0f / 60;

		switch(d){

			case UP:	this->direction += this->uy * TICK;
				break;
			case DOWN:	this->direction -= this->uy * TICK;
				break;
			case LEFT:	this->direction += this->ux * TICK;
				break;
			case RIGHT:	this->direction -= this->ux * TICK;
				break;
		}

		this->direction - normalize(this->direction);
		calculateBasis();
	}

	vec3 getPosition(){

		return this->position;
	}

	vec3 getDirection(){

		return this->direction;
	}

	vec3 getUp(){

		return this->up;
	}

	vec3 getViewPoint(){

		return this->position + (this->direction * VIEW_LENGTH);
	}

private:
	
	void calculateBasis(){

		this->up = vec3(0.0f, 1.0f, 0.0f);
		if(this->direction[0] == this->up[0] && this->direction[1] == this->up[1] && this->direction[2] == this->up[2]) this->up = vec3(0.0f, 0.0f, -1.0f);
	
		this->ux = normalize(cross(this->up, this->direction));
		this->uy = cross(this->direction, this->ux);
	}

	vec3 position;
	vec3 direction;
	vec3 up;

	vec3 ux;
	vec3 uy;

	const float VIEW_LENGTH = 1.0f;
};