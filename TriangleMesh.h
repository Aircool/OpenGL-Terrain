#pragma once
#include <vector>

#include "ShaderLoading.h"
#include "glm/glm.hpp"

using glm::vec3;
using glm::mat4;

class TriangleMesh {
	
public:
	
	TriangleMesh(int size) : SIZE(size) {
		
		for(int row = 0; row < SIZE; ++row){
			for(int col = 0; col < SIZE; ++col){

				float x = -1.0f + ((2.0f * col) / (SIZE - 1));
				float y = -1.0f + ((2.0f * row) / (SIZE - 1));

				vertices.push_back(vec3(x, y, 0));
			}
		}

		for(int row = 0; row < SIZE - 1; ++row){
			for(int col = 0; col < SIZE; ++col){

				indices.push_back(row * SIZE + col);
				indices.push_back((row + 1) * SIZE + col);
			}

			indices.push_back(SIZE * SIZE);
		}

		const char* vshader_source = loadShaderSource((char *)"Shaders/TriangleMesh_V.GLSL");
		const char* fshader_source = loadShaderSource((char *)"Shaders/TriangleMesh_F.GLSL");
		_shaders = createShaders(vshader_source, fshader_source);
		if(_shaders <= 0) return;

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(SIZE * SIZE);

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

	void setHeightMap(vec3** map){

		float heightMap[SIZE][SIZE];

		for(int row = 0; row < SIZE; ++row){
			for(int col = 0; col < SIZE; ++col){

				heightMap[row][col] = map[row][col][0];
			}
		}

		glGenTextures(1, &_heightMap);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _heightMap);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SIZE, SIZE, 0, GL_RED, GL_FLOAT, heightMap);
	}

	void draw(mat4 MVP){
		
		glUseProgram(_shaders);
		glBindVertexArray(_vertexArray);
		
		glUniformMatrix4fv(glGetUniformLocation(_shaders, "MVP"), 1, GL_FALSE, &MVP[0][0]);
		glUniform1i(glGetUniformLocation(_shaders, "HeightMap"), 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, (void *) 0);

		glBindVertexArray(0);
		glUseProgram(0);
	}

private:

	GLuint _shaders;
	
	GLuint _vertexArray;
	GLuint _vertexBuffer;
	GLuint _indexBuffer;
	GLuint _heightMap;

	std::vector<vec3> vertices;
	std::vector<unsigned int> indices;

	float** heightMap;

	int SIZE;
};