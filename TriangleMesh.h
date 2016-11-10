#pragma once
#include <iostream>
#include <vector>

#include "ShaderLoading.h"
#include "VectorMath.h"

class TriangleMesh {
	
public:
	
	TriangleMesh(int width, int height){
		
		for(int row = 0; row < height; ++row){
			for(int col = 0; col < width; ++col){

				float x = -1.0f + ((2.0f * col) / (width - 1));
				float y = -1.0f + ((2.0f * row) / (height - 1));

				vertices.push_back(Vec3(x, y, 0));
			}
		}

		for(int row = 0; row < height - 1; ++row){
			for(int col = 0; col < width; ++col){

				indices.push_back(row * width + col);
				indices.push_back((row + 1) * width + col);
			}

			indices.push_back(width * height);
		}

		const char* vshader_source = loadShaderSource((char *)"Shaders/TriangleMesh_V.GLSL");
		const char* fshader_source = loadShaderSource((char *)"Shaders/TriangleMesh_F.GLSL");
		_shaders = createShaders(vshader_source, fshader_source);
		if(_shaders <= 0) return;

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(width * height);

		glGenVertexArrays(1, &_vertexArray);
		glGenBuffers(1, &_vertexBuffer);
		glGenBuffers(1, &_indexBuffer);	

		glBindVertexArray(_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer)
;			glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
			glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void draw(){
		
		glUseProgram(_shaders);
		glBindVertexArray(_vertexArray);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, (void *) 0);

		glBindVertexArray(0);
		glUseProgram(0);
	}

private:

	GLuint _shaders;
	
	GLuint _vertexArray;
	GLuint _vertexBuffer;
	GLuint _indexBuffer;

	std::vector<Vec3> vertices;
	std::vector<unsigned int> indices;
};