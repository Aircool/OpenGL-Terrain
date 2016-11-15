#version 330 core

in float height;
out vec4 color;

void main(){
	
	color = mix(vec4(0.0, 1.0, 0.0, 1.0), vec4(1.0, 0.0, 0.0, 1.0), height);
}