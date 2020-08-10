/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:21:07 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/10 16:26:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../Include/scop.h"


t_mat4 creat_mat_camera(t_camera *camera)
{
	t_mat4 ret;
	t_mat4 P;

	ret = init_mat4();
	P = init_mat4();
	ret.mat[0][0] = camera->right.x;
	ret.mat[0][1] = camera->right.y;
	ret.mat[0][2] = camera->right.z;
	ret.mat[1][0] = camera->up.x;
	ret.mat[1][1] = camera->up.y;
	ret.mat[1][2] = camera->up.z;
	ret.mat[2][0] = camera->front.x;
	ret.mat[2][1] = camera->front.y;
	ret.mat[2][2] = camera->front.z;

	P.mat[0][3] = camera->pos.x;
	P.mat[1][3] = camera->pos.y;
	P.mat[2][3] = camera->pos.z;
	return (mult_mat4(ret, P));
}

void	creat_camera(t_vec3 pos, t_vec3 target, t_camera *camera)
{

	camera->pos = pos;
	camera->front = normalize_v3(sub_v3(target, camera->pos));
	camera->up = init_v3(0, 1, 0);
	if (!norme_v3(sub_v3(camera->up, camera->front)))
		camera->up = init_v3(0, 0, 1);
	camera->right = normalize_v3(cross_vec3(camera->up, camera->front));
	camera->up = cross_vec3(camera->front, camera->right);
}

t_mat4	model_mat(t_vec3 scale_vec, t_vec3 trans_vec, t_vec3 rot_vec, float theta)
{
	t_mat4 ret;

	ret = init_mat4();
	ret = mult_mat4(ret, translation_mat4(trans_vec));
	ret = mult_mat4(ret, rot_mat4(rot_vec, theta));
	ret = mult_mat4(ret, translation_mat4(init_v3(-0.39 - 0.5 , -0.39 - 0.5, -0.39 - 0.5)));
	ret = mult_mat4(ret, scaling_mat4(scale_vec));
	return (ret);
}

t_mat4 view_mat(t_vec3 scale_vec, t_vec3 trans_vec, t_vec3 rot_vec, float theta)
{
	t_mat4 ret;

	ret = init_mat4();
	ret = mult_mat4(ret, rot_mat4(rot_vec, theta));
	ret = mult_mat4(ret, scaling_mat4(scale_vec));
	ret = mult_mat4(ret, translation_mat4(trans_vec));
	return (ret);
}

t_mat4 proj_mat(float fov, float far, float near)
{
	t_mat4 ret;

	ret = init_mat4();
	ret.mat[0][0] = 1.0 / tan(fov);
	ret.mat[1][1] = 1.0 / tan(fov);
	ret.mat[2][2] = -far / (far - near);
	ret.mat[3][2] = -1;
	ret.mat[2][3] = -far * near / (far - near);
	ret.mat[3][3] = 0;
	return (ret);
}

void	transformations(t_glstruct glstruct, t_camera *camera)
{
	t_mat4	ret;
	float	test[16];

	ret = proj_mat(90.0f * M_PI / 360.0, 1000.0f,  0.1f);
	ret = mult_mat4(ret, creat_mat_camera(camera));
	ret = mult_mat4(ret, model_mat(init_v3(3, 3, 3), init_v3(0.39, 0.39, 0.39), normalize_v3(init_v3(1, 1, 1)), (float)glfwGetTime()));

	// print_mat4(ret);
	int i = -1;
	while (++i < 16)
		test[i] = (float)(mat4_to_a(ret))[i];

	glUseProgram(glstruct.shader_program);
	unsigned int transformLoc = glGetUniformLocation(glstruct.shader_program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (GLfloat*)test);
}

void	update_camera(t_glstruct *glstruct, t_camera *camera)
{
	static float deltaTime = 0;
	static float lastFrame = 0;
	float currentFrame;

	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;  

    camera->speed = 2.50f * deltaTime;
    if (glfwGetKey(glstruct->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
       exit (0);
    if (glfwGetKey(glstruct->window, GLFW_KEY_W) == GLFW_PRESS)
       camera->pos = add_v3(camera->pos, scale_v3(camera->speed, camera->front));
    if (glfwGetKey(glstruct->window, GLFW_KEY_S) == GLFW_PRESS)
        camera->pos = sub_v3(camera->pos, scale_v3(camera->speed, camera->front));
    if (glfwGetKey(glstruct->window, GLFW_KEY_A) == GLFW_PRESS)
        camera->pos = add_v3(camera->pos, scale_v3(camera->speed, camera->right));
    if (glfwGetKey(glstruct->window, GLFW_KEY_D) == GLFW_PRESS)
        camera->pos = sub_v3(camera->pos, scale_v3(camera->speed, camera->right));
    if (glfwGetKey(glstruct->window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->pos = sub_v3(camera->pos, scale_v3(camera->speed, camera->up));
    if (glfwGetKey(glstruct->window, GLFW_KEY_E) == GLFW_PRESS)
        camera->pos = add_v3(camera->pos, scale_v3(camera->speed, camera->up));
}