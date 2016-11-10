#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"

#include "TriangleMesh.h"

SDL_Window* window;
SDL_GLContext context;

bool quit = false;
TriangleMesh* TMesh;

int initSDL(){

	if(SDL_Init(SDL_INIT_VIDEO) < 0)	return -1;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetSwapInterval(1);
	
	window = SDL_CreateWindow("OpenGL 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!window)	return -1;

	context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)	return -1;

	return 0;
}

int initResources(){

	TMesh = new TriangleMesh(160, 90);
	return 0;
}

void render(){
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	TMesh->draw();

	SDL_GL_SwapWindow(window);
}

void input(){
	
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		
		if(event.type == SDL_QUIT) quit = true;
		
		else if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
		}
	}
}

void loop(){

	while(!quit){

		render();
		input();
		SDL_Delay(1000/ 60);
	}
}

int main(int argc, char* argv[]){
	
	if(initSDL() < 0) return -1;
	if(initResources() < 0) return -1;

	loop();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}