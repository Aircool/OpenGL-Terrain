#include "ShaderLoading.h"

const char* loadShaderSource(char* filePath){

	std::ifstream fileStream(filePath);
	std::string shader_string((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

	const char* shader_cstr = shader_string.c_str();
	return shader_cstr;
}

GLuint createShaders(const char* vshader_source, const char* fshader_source){

	GLuint _vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint _fshader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(_vshader, 1, &(vshader_source), NULL);
	glShaderSource(_fshader, 1, &(fshader_source), NULL);
	
	glCompileShader(_vshader);
	glCompileShader(_fshader);
	
	if(checkCompilation(_vshader, "VShader") < 0) return -1;
	if(checkCompilation(_fshader, "FShader") < 0) return -1;

	GLint _shaders = glCreateProgram();
	glAttachShader(_shaders, _vshader);
	glAttachShader(_shaders, _fshader);
	glLinkProgram(_shaders);
	if(checkLinking(_shaders) < 0) return -1;

	glDeleteShader(_vshader);
	glDeleteShader(_fshader);

	return _shaders;
}

int checkCompilation(GLuint _shader, const char* shaderName){

	GLint result;
	GLchar infolog[512];
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &result);

	if(!result){
		
		glGetShaderInfoLog(_shader, 512, NULL, infolog);
		std::cout << shaderName << " COMPILATION ERROR: " << infolog << std::endl;
		return -1;
	}

	return 0;
}

int checkLinking(GLuint _shaders){

	GLint result;
	GLchar infolog[512];
	glGetProgramiv(_shaders, GL_LINK_STATUS, &result);

	if(!result){
		
		glGetProgramInfoLog(_shaders, 512, NULL, infolog);
		std::cout << "SHADER LINKING ERROR: " << infolog << std::endl;
		return -1;
	}

	return 0;
}