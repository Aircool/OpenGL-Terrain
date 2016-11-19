#version 330 core

in vec3 position;
out float height;

uniform mat4 MVP;
uniform sampler2D HeightMap;
 
void main(){

	height = texture(HeightMap, vec2(position.x, position.y)).r;
	gl_Position = MVP * vec4(position.x, position.y, position.z + height, 1.0);
}