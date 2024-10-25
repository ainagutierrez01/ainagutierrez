#include "material.h"

Material::Material(Shader* s, Texture* specTex, Texture* normalTex, Vector3 ka, Vector3 kd, Vector3 ks, float shine){
    this->shader = s;
    this->normal_texture = normalTex;
    this->specular_texture = specTex;
  
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shiness = shine;
}

Material::Material(Shader* s, Texture* specTex, Texture* normalTex) {
    this->shader = s;
    this->normal_texture = normalTex;
    this->color_texture = specTex;
}

void Material::Enable(const sUniformData& uniformData, int light_index) {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader->Enable();

    shader->SetVector3("u_ka", uniformData.ka);
    shader->SetVector3("u_kd", uniformData.kd);
    shader->SetVector3("u_ks", uniformData.ks);
    shader->SetFloat("u_alpha", uniformData.shiness);

    shader->SetMatrix44("u_model", uniformData.model_matrix);
  
        shader->SetTexture("u_texture", uniformData.texture_spec);
    
    shader->SetTexture("u_normal_map", uniformData.texture_norm);

    shader->SetMatrix44("u_viewprojection", uniformData.view_projection);
    shader->SetVector3("u_camera", uniformData.eye);

    shader->SetVector3("u_light", uniformData.scene_lights[light_index]->position);
    shader->SetVector3("u_id", uniformData.scene_lights[light_index]->id);
    shader->SetVector3("u_is", uniformData.scene_lights[light_index]->is);
    shader->SetVector3("u_ia", uniformData.ambient_light);

    shader->SetUniform1("u_flag", light_index);

    shader->SetVector3("u_opt", uniformData.option);

}

void Material::Disable() {
    this->shader->Disable();
    glEnable(GL_DEPTH_TEST);
}