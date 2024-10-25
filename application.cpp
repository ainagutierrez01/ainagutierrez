#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

#include <SDL.h>
#include <SDL_filesystem.h>
#include <SDL_messagebox.h>




Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);

	this->zbuffer = FloatImage(framebuffer.width, framebuffer.height);
	zbuffer.Fill(FLT_MAX);

	option = 1;

	opt = 1;

	uniformData.option = (0, 0, 0);
}

Application::~Application()
{



}


void Application::Init(void)
{

	std::cout << "Initiating app..." << std::endl;

	entity_shader = new Shader();
	entity_shader = Shader::Get("shaders/raster.vs", "shaders/raster.fs");


	texture_s = new Texture();
	texture_s->Load("textures/lee_color_specular.tga");

	texture_n = new Texture();
	texture_n->Load("textures/lee_normal.tga");

	gouraud = new Shader();
	gouraud = Shader::Get("shaders/gouraud.vs", "shaders/gouraud.fs");

	phong = new Shader();
	phong = Shader::Get("shaders/phong.vs", "shaders/phong.fs");

	light = new Light(Vector3(5.0, 5.0, 10.0), Vector3(1.0f, 0.9f, 1.0f), Vector3(0.5, 0.5, 0.5));
	light2 = new Light(Vector3(-10.0, 10.0, 10.0), Vector3(0.0f, 0.9f, 1.0f), Vector3(0.5, 0.5, 0.5));
	light3 = new Light(Vector3(10.0, 5.0, -10.0), Vector3(1.0f, 0.5f, 0.0f), Vector3(0.5, 0.5, 0.5));

	camera.LookAt(Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	camera.SetPerspective(60, framebuffer.width / framebuffer.height, 0.1, 1000);

	entity = new Entity("meshes/lee.obj", Matrix44(), texture_s, texture_n, phong, camera);
	entity_gou = new Entity("meshes/lee.obj", Matrix44(), texture_s, texture_n, gouraud, camera);

	entity->modelMatrix.Translate(0.0f, 0.0f, 3.5f);
	entity_gou->modelMatrix.Translate(0.0f, 0.0f, 3.5f);

	is_orbiting = false;
	orbit = false;

}

//Image Toolbar;

// Render one frame
void Application::Render(void) {

	uniformData.ambient_light = Vector3(0.5, 0.5, 0.5);

	uniformData.scene_lights[0] = light;
	uniformData.view_projection = camera.viewprojection_matrix;

	if (opt == 2 && option == 11) {
		uniformData.scene_lights[1] = light2;
		entity->Render(uniformData, opt);
	}
	else if (opt == 3 && option == 11) {

		uniformData.scene_lights[1] = light2;


		uniformData.scene_lights[2] = light3;
		entity->Render(uniformData, opt);
	}
	else if (option == 10) {
		entity_gou->Render(uniformData, 1);
	}

	else if (option == 11) {
		entity->Render(uniformData, opt);
	}

}


// Called after render
void Application::Update(float seconds_elapsed)
{

}

//keyboard press event 
void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break;
	case SDLK_g:

		option = 10;
		break;


	case SDLK_p:
		option = 11;

		break;

	case SDLK_1:
		opt = 1;
		break;

	case SDLK_2:
		opt = 2;
		break;

	case SDLK_3:
		opt = 3;
		break;

	case SDLK_c:
		uniformData.option.x = 1 - uniformData.option.x;
		break;

	case SDLK_s:
		uniformData.option.y = 1 - uniformData.option.y;
		break;

	case SDLK_n:
		uniformData.option.z = 1 - uniformData.option.z;
		break;
	}

}





void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{
	Vector2 mousePosition(event.x, float(event.y) - float(framebuffer.height));
	std::cout << "Mouse Position: (" << mouse_position.x << ", " << mouse_position.y << ")" << std::endl;


	if (event.button == SDL_BUTTON_LEFT) {
		orbit_start_mouse_position = Vector2(event.x, event.y);
		is_orbiting = true;
	}

	if (event.button == SDL_BUTTON_RIGHT) {
		orbit = true;
	}

}


void Application::OnMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {

		is_orbiting = false;
	}

	else if (event.button == SDL_BUTTON_RIGHT) {

		orbit = false;
	}
}


void Application::OnMouseMove(SDL_MouseButtonEvent event)
{

	mouse_delta.x = event.x - mouse_position.x;
	mouse_delta.y = event.y - mouse_position.y;

	mouse_position.x = event.x;
	mouse_position.y = event.y;

	if (is_orbiting) {
		float sensitivity = 0.005f; // Adjust the sensitivity as needed

		float delta_x = event.x - orbit_start_mouse_position.x;
		float delta_y = event.y - orbit_start_mouse_position.y;

		// Calculate the right axis of the camera
		Vector3 right = camera.view_matrix.RightVector();

		// Update the camera's orientation based on mouse movement
		camera.Rotate(delta_x * sensitivity, Vector3(0.0f, 1.0f, 0.0f)); // Rotate around the up axis
		camera.Rotate(delta_y * sensitivity, right); // Rotate around the camera's right axis

		// Update the view matrix
		camera.UpdateViewMatrix();

		// Update the start mouse position for the next frame
		orbit_start_mouse_position = Vector2(event.x, event.y);
	}

	if (orbit) {
		camera.Orbit(0.1 * mouse_delta.x * DEG2RAD, Vector3(0, 1, 0));
		camera.Orbit(0.1 * mouse_delta.y * DEG2RAD, Vector3(1, 0, 0));

	}


}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
	camera.Zoom(dy < 0 ? 1.1 : 0.9);
}

void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);
}