#include "render.h"
#include "glad.h"
#include <string>
#include <iostream>
#include "glm/glm.hpp"

void Render::init(float width, float height)
{
	projection = glm::perspective(glm::radians(60.0f), width / height, 0.1f, 100.0f);
	ortProjection = glm::ortho(0.0f, width, 0.0f, height);
}

void Render::draw_pbr(Scene* scene, Camera* cam)
{
	int length = scene->ents.size();
	for (int i = 0; i < length; ++i)
	{
		Entity* ent = scene->ents[i];
		Model* mod = ent->mod;
		glUseProgram(mod->shader_id);
		glBindVertexArray(mod->vao);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, ent->position);
		model = glm::rotate(model, glm::radians(ent->angle[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(ent->angle[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(ent->angle[2]), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, ent->e_scale);

		unsigned int model_loc = glGetUniformLocation(mod->shader_id, "u_M");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
		unsigned int view_loc = glGetUniformLocation(mod->shader_id, "u_V");
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(cam->view));
		unsigned int proj_loc = glGetUniformLocation(mod->shader_id, "u_P");
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(glGetUniformLocation(mod->shader_id, "albedo"), ent->mod->material->albedo[0], ent->mod->material->albedo[1], ent->mod->material->albedo[2]);
		glUniform1f(glGetUniformLocation(mod->shader_id, "ao"), ent->mod->material->ao);
		glUniform3f(glGetUniformLocation(mod->shader_id, "camPos"), cam->pos.x, cam->pos.y, cam->pos.z);
		glUniform1f(glGetUniformLocation(mod->shader_id, "metallic"), ent->mod->material->metallic);
		glUniform1f(glGetUniformLocation(mod->shader_id, "roughness"), ent->mod->material->roughness);
		
		glUniform3f(glGetUniformLocation(mod->shader_id, "lightPositions[0]"), scene->point_lights[0].position.x, scene->point_lights[0].position.y, scene->point_lights[0].position.z);
		glUniform3f(glGetUniformLocation(mod->shader_id, "lightColors[0]"), scene->point_lights[0].color.x, scene->point_lights[0].color.y, scene->point_lights[0].color.z);

		glDrawArrays(GL_TRIANGLES, 0, mod->ind_number);
	}
}

void	Render::draw_skybox(Skybox *skybox, Camera* cam)
{
	glDepthMask(GL_FALSE);
	glUseProgram(skybox->shader_id);
	glm::mat4 view = glm::mat4(glm::mat3(cam->view));
	unsigned int view_loc = glGetUniformLocation(skybox->shader_id, "u_V");
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
	unsigned int proj_loc = glGetUniformLocation(skybox->shader_id, "u_P");
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(skybox->vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}
