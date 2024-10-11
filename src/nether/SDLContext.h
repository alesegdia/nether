#pragma once

#include <stdio.h>
#include <SDL.h>
#include <glad/gl.h>

namespace nether {

	class SDLContext {
	public:
		void Init(int width, int height);
		void EndFrame();
		void Cleanup();

	private:
		SDL_Window* window;
		SDL_GLContext context;
	};

}

// Declare the MessageCallback function
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* msg, const void* data);