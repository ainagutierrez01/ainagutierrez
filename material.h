#pragma once

#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "light.h"



typedef struct s_UniformData
{
    Matrix44 model_matrix;
    Matrix44 view_projection;
    Vector3 eye;
    Vector3 ambient_light;
    Texture* texture_spec;
  
    Texture* texture_norm;
    Vector3 ka;
    Vector3 kd;
    Vector3 ks;
    float shiness;
    Light* scene_lights[GL_MAX_LIGHTS];
    int num_lights;
    Vector3 option;

} sUniformData;

class Material
{
public:
    Shader* shader;
    Texture* color_texture;
    Texture* specular_texture;
    Texture* normal_texture;
    Vector3 ka;
    Vector3 kd;
    Vector3 ks;
    float shiness;

    // Constructor
    Material(Shader* s, Texture* specTex,Texture* normalTex, Vector3 ka, Vector3 kd, Vector3 ks, float shine);
    Material(Shader* s, Texture* specTex, Texture* normalTex);
    void Enable(const sUniformData& uniformData, int light_index);
    void Disable();
};