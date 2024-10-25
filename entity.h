#pragma once
#include "camera.h"
#include "mesh.h"
#include "image.h"
#include "shader.h"
#include "material.h"

class Entity
{
public:
    Matrix44 modelMatrix;
    Mesh mesh;
    Material* material;

    Texture* texture_c;
    Texture* texture_n;
    Texture* texture_s;
    Shader* entity_shader;
    
    
    Camera camera;
    Mesh quad;
    Shader* shader;
    
    float tecla;
    bool withoutocclusions;
    // Constructors, dependiendo de los parametros, crear mas constructores
    Entity();
    Entity::Entity(const char* filename, Matrix44 modelMatrix, Texture* texture_spec, Texture* texture_norm, Shader* shader, Camera cam);
    void Render(sUniformData uniformData, int num_lights);
    //void Render(Image* framebuffer, Camera* camera, const Color& c1, const Color& c2, const Color& c3, bool fill, FloatImage* zBuffer);
    void Update(float seconds_elapsed, int axis, bool translation);
    void SetMatrix(float x, float y, float z);

};