/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:21:07 by esuits            #+#    #+#             */
/*   Updated: 2020/08/18 19:08:34 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../Include/scop.h"

static t_mat4	creat_mat_camera(t_camera *camera)
{
	t_mat4 ret;
	t_mat4 p;

	ret = init_mat4();
	p = init_mat4();
	ret.mat[0][0] = camera->right.x;
	ret.mat[0][1] = camera->right.y;
	ret.mat[0][2] = camera->right.z;
	ret.mat[1][0] = camera->up.x;
	ret.mat[1][1] = camera->up.y;
	ret.mat[1][2] = camera->up.z;
	ret.mat[2][0] = camera->front.x;
	ret.mat[2][1] = camera->front.y;
	ret.mat[2][2] = camera->front.z;
	p.mat[0][3] = camera->pos.x;
	p.mat[1][3] = camera->pos.y;
	p.mat[2][3] = camera->pos.z;
	return (mult_mat4(ret, p));
}

static t_vec3	creat_med_pos(t_vertex min, t_vertex max)
{
	t_vec3 med;

	med.x = (float)(min.x + max.x) / 2.0;
	med.y = (float)(min.y + max.y) / 2.0;
	med.z = (float)(min.z + max.z) / 2.0;
	return (med);
}

t_camera		init_camera(t_vec3 pos)
{
	t_camera camera;

	camera.yaw = -90;
	camera.pitch = 0;
	camera.mouseflag = 1;
	camera.polyflag = 0;
	camera.speed_base = 10.0;
	creat_camera(pos, &camera);
	return (camera);
}

void			creat_camera(t_vec3 pos, t_camera *camera)
{
	camera->pos = pos;
	camera->front.x = cos(M_PI * camera->yaw / 180.0) *
		cos(M_PI * camera->pitch / 180.0);
	camera->front.y = sin(M_PI * camera->pitch / 180.0);
	camera->front.z = sin(M_PI * camera->yaw / 180.0) *
	cos(M_PI * camera->pitch / 180.0);
	camera->front = normalize_v3(camera->front);
	camera->up = init_v3(0, 1, 0);
	if (!norme_v3(sub_v3(camera->up, camera->front)))
		camera->up = init_v3(0, 0, 1);
	camera->right = normalize_v3(cross_vec3(camera->up, camera->front));
	camera->up = cross_vec3(camera->front, camera->right);
}

static t_mat4	model_mat(t_vec3 scale_vec, t_vec3 trans_vec,
	t_vec3 rot_vec, float theta)
{
	t_mat4 ret;

	ret = init_mat4();
	ret = mult_mat4(ret, scaling_mat4(scale_vec));
	ret = mult_mat4(ret, translation_mat4(trans_vec));
	ret = mult_mat4(ret, rot_mat4(rot_vec, theta));
	ret = mult_mat4(ret, translation_mat4(scale_v3(-1, trans_vec)));
	return (ret);
}

static t_mat4	view_mat(t_vec3 scale_vec, t_vec3 trans_vec,
	t_vec3 rot_vec, float theta)
{
	t_mat4 ret;

	ret = init_mat4();
	ret = mult_mat4(ret, scaling_mat4(scale_vec));
	ret = mult_mat4(ret, rot_mat4(rot_vec, theta));
	ret = mult_mat4(ret, translation_mat4(trans_vec));
	return (ret);
}

static t_mat4	proj_mat(float fov, float far, float near)
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

static float	get_delata_time_rot(float delta_time)
{
	static float	last_frame = 0;
	float			current_frame;

	current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
	return (delta_time);
}

void			transformations(t_glstruct glstruct,
	t_camera *camera, t_obj *obj)
{
	t_mat4			ret;
	float			test[16];
	float			*mat_array;
	int				i;
	static float	rotation = 0;
	static float	delta_time = 0;
	GLint			m_viewport[4];

	delta_time = get_delata_time_rot(delta_time);
	if (camera->rotflag)
		rotation += delta_time;
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	ret = proj_mat(90.0f * M_PI / 360.0, 100000.0f, 0.1f);
	ret = mult_mat4(ret, creat_mat_camera(camera));
	ret = mult_mat4(ret, model_mat(init_v3(3, 3, 3),
		creat_med_pos(obj->min, obj->max), normalize_v3(init_v3(1, 0, 0)),
		-90 * M_PI / 180.0));
	ret = mult_mat4(ret, scaling_mat4(init_v3(1,
		(float)m_viewport[2] / (float)m_viewport[3], 1)));
	mat_array = (float*)mat4_to_a(ret);
	i = -1;
	while (++i < 16)
		test[i] = (float)mat_array[i];
	ft_memdel((void**)&mat_array);
	glUseProgram(glstruct.shader_program);
	glUniformMatrix4fv(glGetUniformLocation(glstruct.shader_program,
		"transform"), 1, GL_FALSE, (GLfloat*)test);
}

void			mouse_callback(double xpos, double ypos, t_camera *camera)
{
	static double	last_x = 400;
	static double	last_y = 300;
	double			xoffset;
	double			yoffset;

	xoffset = xpos - last_x;
	yoffset = last_y - ypos;
	last_x = xpos;
	last_y = ypos;
	xoffset *= 0.1;
	yoffset *= 0.1;
	camera->pitch -= yoffset;
	camera->yaw += xoffset;
	camera->yaw = fmod(camera->yaw, 360);
	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;
	creat_camera(camera->pos, camera);
}

void			update_camera(t_glstruct *glstruct, t_camera *camera)
{
	static float	delta_time = 0;
	static float	last_frame = 0;
	float			current_frame;
	double			xpos;
	double			ypos;

	current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
	if (camera->mouseflag)
	{
		glfwGetCursorPos(glstruct->window, &xpos, &ypos);
		mouse_callback(xpos, ypos, camera);
	}
	camera->speed = camera->speed_base * delta_time;
	if (glfwGetKey(glstruct->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		exit(0);
	if (glfwGetKey(glstruct->window, GLFW_KEY_W) == GLFW_PRESS)
		camera->pos = add_v3(camera->pos,
			scale_v3(camera->speed, camera->front));
	if (glfwGetKey(glstruct->window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		camera->speed_base *= 1.001;
	if (glfwGetKey(glstruct->window, GLFW_KEY_S) == GLFW_PRESS)
		camera->pos = sub_v3(camera->pos,
			scale_v3(camera->speed, camera->front));
	if (glfwGetKey(glstruct->window, GLFW_KEY_A) == GLFW_PRESS)
		camera->pos = add_v3(camera->pos,
			scale_v3(camera->speed, camera->right));
	if (glfwGetKey(glstruct->window, GLFW_KEY_D) == GLFW_PRESS)
		camera->pos = sub_v3(camera->pos,
			scale_v3(camera->speed, camera->right));
	if (glfwGetKey(glstruct->window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->pos = add_v3(camera->pos,
			scale_v3(camera->speed, camera->up));
	if (glfwGetKey(glstruct->window, GLFW_KEY_E) == GLFW_PRESS)
		camera->pos = sub_v3(camera->pos,
			scale_v3(camera->speed, camera->up));
	if (glfwGetKey(glstruct->window, GLFW_KEY_SPACE) == GLFW_PRESS &&
		camera->mouseinputflag)
	{
		camera->mouseinputflag = 0;
		camera->mouseflag = camera->mouseflag ? 0 : 1;
	}
	if (!(glfwGetKey(glstruct->window, GLFW_KEY_SPACE) == GLFW_PRESS))
		camera->mouseinputflag = 1;
	if (glfwGetKey(glstruct->window, GLFW_KEY_P) == GLFW_PRESS &&
		camera->polyinputflag)
	{
		camera->polyinputflag = 0;
		camera->polyflag = camera->polyflag ? 0 : 1;
	}
	if (!(glfwGetKey(glstruct->window, GLFW_KEY_P) == GLFW_PRESS))
		camera->polyinputflag = 1;
	if (glfwGetKey(glstruct->window, GLFW_KEY_R) == GLFW_PRESS &&
		camera->rotinputflag)
	{
		camera->rotinputflag = 0;
		camera->rotflag = camera->rotflag ? 0 : 1;
	}
	if (!(glfwGetKey(glstruct->window, GLFW_KEY_R) == GLFW_PRESS))
		camera->rotinputflag = 1;
	if (glfwGetKey(glstruct->window, GLFW_KEY_T) == GLFW_PRESS &&
		camera->textureinputflag)
	{
		camera->textureinputflag = 0;
		camera->textureflag = camera->textureflag ? 0 : 1;
	}
	if (!(glfwGetKey(glstruct->window, GLFW_KEY_T) == GLFW_PRESS))
		camera->textureinputflag = 1;
}
