#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"

#include "TriangleMesh.h"

SDL_Window* window;
bool quit = false;

int render(void* ptr){
	
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		
		return -1;
	}
	
	TriangleMesh TMesh(50);

	while(!quit){
		
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		TMesh.draw();
		
		SDL_GL_SwapWindow(window);
		SDL_Delay(1000 / 60);
	}
	
	SDL_GL_DeleteContext(context);
	
	return 0;
}

void input(){
	
	SDL_Event event;
	while(!quit){
		
		SDL_WaitEvent(&event);
		
		if(event.type == SDL_QUIT) quit = true;
		
		else if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
		}
	}
}

int main(int argc, char* argv[]){
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		
		return -1;
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetSwapInterval(1);
	
	window = SDL_CreateWindow("OpenGL 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!window){
		
		return -1;
	}
	
	SDL_Thread* renderThread = SDL_CreateThread(render, "Render Thread", (void *) NULL);
	SDL_DetachThread(renderThread);
	
	input();
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}