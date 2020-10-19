/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:22:02 by esuits            #+#    #+#             */
/*   Updated: 2020/08/18 19:06:33 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../Include/scop.h"

int		init_everything(t_glstruct *glstruct)
{
	init_glfw();
	if (!(glstruct->window = glfwCreateWindow(640, 480,
		"Hello Triangle", NULL, NULL)))
		print_error(2);
	glfwMakeContextCurrent(glstruct->window);
	init_glew();
	return (0);
}

void	change_alpha(t_glstruct glstruct, t_camera camera)
{
	static float	alpha = 1;
	static float	delta_time = 0;
	static float	last_frame = 0;
	float			current_frame;

	current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
	if (camera.textureflag && alpha >= 0 && alpha < 1)
		alpha += 0.01;
	if (!camera.textureflag && alpha <= 1 && alpha > 0)
		alpha -= 0.01;
	if (alpha > 1)
		alpha = 1;
	if (alpha < 0)
		alpha = 0;
	glUseProgram(glstruct.shader_program);
	glUniform1f(glGetUniformLocation(glstruct.shader_program,
		"alpha"), (GLfloat)alpha);
}

void	set_modes(t_glstruct glstruct, t_camera camera)
{
	change_alpha(glstruct, camera);
	if (camera.mouseflag)
		glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (camera.polyflag)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void	update_textures(t_glstruct glstruct, t_index *ind, GLuint text[34])
{
	glActiveTexture(GL_TEXTURE0 + ind->index_txt);
	glBindTexture(GL_TEXTURE_2D, text[ind->index_txt]);
	glUniform1i(glGetUniformLocation(glstruct.shader_program,
		"texture1"), ind->index_txt);
	glUseProgram(glstruct.shader_program);
}

void	draw_loop(t_glstruct glstruct, t_index *ret,
	GLuint text[34], t_obj *obj)
{
	t_index		*tmp;
	t_camera	camera;

	camera = init_camera(init_v3(0, 0, -3), obj);
	while (!glfwWindowShouldClose(glstruct.window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		set_modes(glstruct, camera);
		tmp = ret;
		while (tmp)
		{
			update_camera(&glstruct, &camera);
			update_textures(glstruct, tmp, text);
			transformations(glstruct, &camera, obj);
			glBindVertexArray(tmp->vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp->ebo);
			glDrawElements(GL_TRIANGLES, tmp->verts_size, GL_UNSIGNED_INT, 0);
			tmp = tmp->next;
		}
		glfwSwapBuffers(glstruct.window);
	}
}

int		assign_textures(t_glstruct glstruct, GLuint **text,
	t_obj *obj, t_index *ind)
{
	if (obj->mtl)
		while (obj->mtl)
		{
			if (!setup_texture(&glstruct, *text, obj->mtl->map_Kd, obj->path))
			{
				ft_putendl("Error Mallocated TGA file\n");
				return (-1);
			}
			obj->mtl = obj->mtl->next;
		}
	else
	{
		if (!setup_texture(&glstruct, *text, "Jinx.tga", "\0"))
		{
			ft_putendl("Error Mallocated TGA file\n");
			return (-1);
		}
		while (ind)
		{
			ind->index_txt = 0;
			ind = ind->next;
		}
	}
	return (0);
}

void	send_variables(t_glstruct glstruct, t_obj obj)
{
	glUseProgram(glstruct.shader_program);
	glUniform3f(glGetUniformLocation(glstruct.shader_program, "size"),
		fabs(obj.min.x - obj.max.x), fabs(obj.min.y - obj.max.y),
		fabs(obj.min.z - obj.max.z));
	glUseProgram(glstruct.shader_program);
	glUniform3f(glGetUniformLocation(glstruct.shader_program, "center"),
		(obj.min.x + obj.max.x) / 2.0, (obj.min.y + obj.max.y) / 2.0,
		(obj.min.z + obj.max.z) / 2.0);
}

int		runobj(t_glstruct glstruct, t_index *ret, int nb_obj, t_obj *obj)
{
	int			i;
	GLuint		text[34];
	t_index		*tmp;

	glstruct.shader_program = create_program();
	glUseProgram(glstruct.shader_program);
	if (assign_textures(glstruct, (GLuint **)&text, obj, ret))
		return (-1);
	glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	send_variables(glstruct, *obj);
	tmp = ret;
	while (tmp)
	{
		generate_vbo(&tmp->vbo, tmp->verts, sizeof(float) * tmp->verts_size);
		generate_vao(&tmp->vao, tmp->vbo);
		generate_ebo(&tmp->ebo, (float*)tmp->index, (tmp->face_size));
		tmp = tmp->next;
	}
	draw_loop(glstruct, ret, text, obj);
	glfwTerminate();
	// glDeleteVertexArrays(1 , &tmp->vao);
	// glDeleteBuffers(1, &tmp->vbo);
	// glDeleteBuffers(1, &tmp->ebo);
	// freeobj();
	return (0);
}

void	find_index_material(t_group **group, t_material *mat, int *ret)
{
	int			i;
	t_material	*tmp;

	i = 0;
	*ret = 0;
	tmp = mat;
	while (tmp)
	{
		if ((*group)->material && tmp->name)
		{
			if (!ft_strcmp((*group)->material, tmp->name))
			{
				printf("[%s] == [%s]\nTexture Find : %d\n",
				(*group)->material, tmp->name, i);
				*ret = i;
				return ;
			}
		}
		i++;
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv)
{
	t_glstruct	glstruct;
	t_index		index;
	t_index		tmp;
	t_index		*ptr;
	t_obj		*obj;
	int			i;
	int			savetxt;
	t_group		*ptr_grp;
	t_obj		*tmp_obj;

	if (argc == 1)
		return (0);
	if (!(obj = malloc(sizeof(t_obj))))
		return (objerror(NULL, 1));
	if (init_obj(obj) == -1)
		return (objerror(obj, -1));
	if (argc < 2 || argc > 3)
		return (objerror(obj, 2));
	if (objload(argv[1], INFO))
		return (objerror(obj, 1));
	i = 0;
	while (i < argc - 2)
	{
		if (objload(argv[i + 2], INFO))
			return (objerror(obj, 1));
		i++;
	}
	tmp_obj = obj;
	i = 0;
	savetxt = 0;
	index.next = NULL;
	ptr = &index;
	while (obj)
	{
		ptr->index_obj = obj->id;
		ptr_grp = obj->group;
		while (ptr_grp)
		{
			if (split_faces(obj, &(tmp), ptr_grp))
				return (1);
			if (create_vert(*obj, &(ptr), tmp.index,
				tmp.face_size * 3))
				return (1);
			find_mat(ptr_grp, &(ptr), *obj);
			free(tmp.index);
			if (ptr_grp && obj->mtl)
			{
				find_index_material(&ptr_grp, obj->mtl, &tmp.index_txt);
				savetxt = tmp.index_txt;
			}
			else if (ptr_grp)
				tmp.index_txt = savetxt;
			if (ptr_grp->next)
			{
				if (!(ptr->next = malloc(sizeof(t_index))))
					return (1);
				ptr = ptr->next;
				ptr->next = NULL;
			}
			ptr_grp = ptr_grp->next;
		}
		if (obj->next)
		{
			if (!(ptr->next = malloc(sizeof(t_index))))
				return (1);
			ptr = ptr->next;
			ptr->next = NULL;
		}
		obj = obj->next;
		++i;
	}
	// free_obj(obj);
	init_everything(&glstruct);
	return (runobj(glstruct, &index, i + 1, tmp_obj));
}
