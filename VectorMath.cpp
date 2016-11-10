#include "VectorMath.h"

Vec3 operator*(float scalar, Vec3 V){
	
	return Vec3(V[0] * scalar, V[1] * scalar, V[2] * scalar);
}