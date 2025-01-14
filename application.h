/*
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "entity.h"
#include "mesh.h"
#include "shader.h"

class Application
{
public:

	// Window

	SDL_Window* window;
	int window_width;
	int window_height;

	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame
	Vector2 orbit_start_mouse_position;
	bool is_orbiting;
	bool orbit;


	sUniformData uniformData;

	Shader* entity_shader;
	Shader* shader;
	Shader* gouraud;
	Shader* phong;
	Texture* texture_c;
	Texture* texture_n;
	Texture* texture_s;
	Entity* entity;
	Entity* entity_gou;
	Light* light;
	Light* light2;
	Light* light3;
	Material* material;
	
	Mesh* mesh;
	Matrix44 modelMatrix;
	Camera camera;
	int opt;
	int option;

	
	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);
	

	// CPU Global framebuffer
	Image framebuffer;
	FloatImage zbuffer;
	Image texturelee;
	Image texturenull;
	Image textureanna;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init(void);
	void Render(void);
	void Update(float dt);

	float tecla = -1;


	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport(0, 0, width, height);
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 GetWindowSize()
	{
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		return Vector2(float(w), float(h));
	}
};