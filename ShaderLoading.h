#pragma once

#include "GL/glew.h"
#include "GL/gl.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

const char* loadShaderSource(char* filePath);
GLuint createShaders(const char* vshader_source, const char* fshader_source);
int checkCompilation(GLuint _shader);
int checkLinking(GLuint _shaders);