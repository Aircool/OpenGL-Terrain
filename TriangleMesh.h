#pragma once
#include <vector>

#include "glm/glm.hpp"

using glm::vec2;
using glm::vec3;
using glm::mat4;

class TriangleMesh {
	
public:

	TriangleMesh(vec2 offset){
		
		for(int row = 0; row < MESH_SIZE; ++row){
			for(int col = 0; col < MESH_SIZE; ++col){

				float x = ((1.0f * col) / (MESH_SIZE - 1)) + offset[0];
				float z = ((1.0f * row) / (MESH_SIZE - 1)) + offset[1];

				vertices.push_back(vec3(x, 0.0f, z));
			}
		}

		for(int row = 0; row < MESH_SIZE - 1; ++row){
			for(int col = 0; col < MESH_SIZE; ++col){

				indices.push_back(row * MESH_SIZE + col);
				indices.push_back((row + 1) * MESH_SIZE + col);
			}

			indices.push_back(MESH_SIZE * MESH_SIZE);
		}

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(MESH_SIZE * MESH_SIZE);

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

	void setShaders(GLuint shaders){

		_shaders = shaders;
	}

	void setHeightMap(float* map){

		glGenTextures(1, &_heightMap);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _heightMap);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, NOISE_SIZE, NOISE_SIZE, 0, GL_RED, GL_FLOAT, map);
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
};