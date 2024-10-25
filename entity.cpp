#include "entity.h"
#include "image.h"
#include "material.h"

Entity::Entity() {}

Entity::Entity(const char* filename, Matrix44 modelMatrix, Texture* texture_spec, Texture* texture_norm, Shader* entity_shader, Camera cam) {
    this->mesh.LoadOBJ(filename);
    this->modelMatrix = modelMatrix;
    this->texture_n = texture_norm;
    this->texture_s = texture_spec;
    this->entity_shader = entity_shader;



    this->camera = cam;


    this->material = new Material(entity_shader, texture_s, texture_n, Vector3(0.3f, 0.19f, 0.07f), Vector3(0.5f, 0.3f, 0.1f), Vector3(0.8f, 0.5f, 0.2f), 30.0f);

}

bool negZ1, negZ2, negZ3;

void Entity::Render(sUniformData uniformData, int num_lights) {


    uniformData.model_matrix = modelMatrix;

    uniformData.eye = camera.eye;

    uniformData.texture_spec = texture_s;
    uniformData.texture_norm = texture_n;

    uniformData.ka = material->ka;
    uniformData.kd = material->kd;
    uniformData.ks = material->ks;
    uniformData.shiness = material->shiness;

    material->Enable(uniformData, 0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_BLEND);

    mesh.Render();

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    for (int i = 1; i < num_lights; i++) {
        material->Enable(uniformData, i);
        mesh.Render();
    }

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    material->Disable();
}


void Entity::SetMatrix(float x, float y, float z) {
    this->modelMatrix.SetTranslation(x, y, z);
}

void Entity::Update(float seconds_elapsed, int axis, bool translation) {
    if (axis == 0) {
        modelMatrix.Rotate(PI / 100, Vector3(0, 1, 0));
        if (translation == true) {
            modelMatrix.Translate(0.01, 0, 0);
        }
    }
    else if (axis == 1) {
        modelMatrix.Rotate(PI / 100, Vector3(0, 0, 1));
        if (translation == true) {
            modelMatrix.Translate(0, 0, 0.01);
        }
    }
    else if (axis == 2) {
        modelMatrix.Rotate(PI / 50, Vector3(1, 1, 0));
        if (translation == true) {
            modelMatrix.Translate(0.01, 0, 0);
        }

    }
}