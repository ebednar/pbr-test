#include "pbr.h"

void Sandbox::place_ent(Engine* eng)
{
    Entity*  box = new Entity();
    Model* mod = new Model();
    glm::vec3 lightPositions[] = {
        glm::vec3(-3.0f,  1.0f, 3.0f),
        glm::vec3(3.0f,  1.0f, 3.0f),
        glm::vec3(-3.0f, -1.0f, 3.0f),
        glm::vec3(3.0f, -1.0f, 3.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)
    };
    mod->load_obj("res/models/test.obj", true);
    //mod->set_shader("res/shaders/pbr_vert.glsl", "res/shaders/pbr_frag.glsl");
    mod->set_shader("res/shaders/pbr_vert.glsl", "res/shaders/pbr_frag.glsl");
    box->set_model(mod);
    eng->add_entity(box);
    box->move_to(0.0f, 0.0f, 0.0f);
    box->rotate(0.0f, 30.0f, 0.0f);
    for (int i = 0; i < 4; ++i)
    {
        Entity* light = new Entity();
        light->set_model(mod);
        eng->add_entity(light);
        light->move_to(lightPositions[i].x, lightPositions[i].y, lightPositions[i].z);
        light->scale(0.5f, 0.5f, 0.5f);
        eng->add_light_source(lightPositions[i], lightColors[i]);
    }
}