#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Constants.h"
#include "ShaderLoading.h"
#include "TriangleMesh.h"
#include "Noise.h"

SDL_Window* window;
SDL_GLContext context;
bool quit = false;

std::vector<TriangleMesh*> TMeshes;
Noise* noise;

float cam_X = 0.0f;
float cam_Y = 0.0f;
float cam_Z = 0.0f;
float dir_X = 0.0f;
float dir_Y = -2.0f;
float dir_Z = -4.0f;

int initSDL(){

	if(SDL_Init(SDL_INIT_VIDEO) < 0)	return -1;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetSwapInterval(1);
	
	window = SDL_CreateWindow("OpenGL 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if(!window)	return -1;

	context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)	return -1;

	return 0;
}

int initResources(int seed){
	
	noise = new Noise(seed);
	float* FBM = new float[NOISE_SIZE * NOISE_SIZE];

	for(int y = 0; y < NOISE_SIZE; ++y){
		for(int x = 0; x < NOISE_SIZE; ++x){

			float relX = ((float) x) / NOISE_SIZE;
			float relY = ((float) y) / NOISE_SIZE;
			FBM[y * NOISE_SIZE + x] = noise->FBM(relX, relY);
		}
	}

	const char* vshader_source = loadShaderSource((char *)"Shaders/TriangleMesh_V.GLSL");
	const char* fshader_source = loadShaderSource((char *)"Shaders/TriangleMesh_F.GLSL");
	GLuint shaders = createShaders(vshader_source, fshader_source);
	if(shaders <= 0) return -1;
	
	for(int y = -2; y <= 1; ++y){
		for(int x = -2; x <= 1; ++x){

			TriangleMesh* TMesh = new TriangleMesh(vec2(x, y));
			TMesh->setShaders(shaders);
			TMesh->setHeightMap(FBM);
			TMeshes.push_back(TMesh);
		}
	}

	return 0;
}

void render(){

	mat4 Model(1.0f);

	vec3 cam(0 + cam_X, 2.0 + cam_Y, 4.0 + cam_Z);
	vec3 pt = cam + (vec3(dir_X, dir_Y, dir_Z) * 0.01f);

	mat4 View = glm::lookAt(cam, pt, vec3(0, 0, 1));
	mat4 Projection = glm::perspective(glm::radians(90.0f), ((float) WINDOW_WIDTH) / ((float) WINDOW_HEIGHT), 0.1f, 10.0f);
	mat4 MVP = Projection * View * Model;
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for(int i = 0; i < TMeshes.size(); i++){
		TMeshes[i]->draw(MVP);
	}

	SDL_GL_SwapWindow(window);
}

void input(){
	
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		
		if(event.type == SDL_QUIT) quit = true;
		
		else if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
			else {

				const unsigned char* kb_state = SDL_GetKeyboardState(NULL);
				float tick = 1.0f / 60;

				if(kb_state[SDL_SCANCODE_W])		cam_Y += tick;
				if(kb_state[SDL_SCANCODE_S])		cam_Y -= tick;
				if(kb_state[SDL_SCANCODE_A])		cam_X -= tick;
				if(kb_state[SDL_SCANCODE_D])		cam_X += tick;
				if(kb_state[SDL_SCANCODE_SPACE])	cam_Z -= tick;
				if(kb_state[SDL_SCANCODE_LCTRL])	cam_Z += tick;   

				if(kb_state[SDL_SCANCODE_UP])		dir_Y += tick;
				if(kb_state[SDL_SCANCODE_DOWN])		dir_Y -= tick;
				if(kb_state[SDL_SCANCODE_LEFT])		dir_X -= tick; 
				if(kb_state[SDL_SCANCODE_RIGHT])	dir_X += tick;
			}
		}
	}
}

void loop(){

	while(!quit){

		render();
		input();
		SDL_Delay(1000 / 60);
	}
}

int main(int argc, char* argv[]){
	
	if(initSDL() < 0) return -1;
	if(initResources(atoi(argv[1])) < 0) return -1;

	loop();
		
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}