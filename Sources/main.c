/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:22:02 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/18 19:06:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../Include/scop.h"

int		init_everything(t_glstruct *glstruct)
{
	init_glfw();
	if (!(glstruct->window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL)))
		print_error(2);
	glfwMakeContextCurrent(glstruct->window);
	init_glew();
	return (0);
}

void change_alpha(t_glstruct glstruct, t_camera camera)
{
	static float alpha = 1;
	static float deltaTime = 0;
	static float lastFrame = 0;
	float currentFrame;

	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (camera.textureflag && alpha >= 0 && alpha < 1)
		alpha += 0.01;
	if (!camera.textureflag && alpha <= 1 && alpha > 0)
		alpha -= 0.01;
	if (alpha > 1)
		alpha = 1;
	if (alpha < 0)
		alpha = 0;
	glUseProgram(glstruct.shader_program);
	// if (alpha != 1 && alpha != 0)
	// 	printf("%f \n", alpha);
	glUniform1f(glGetUniformLocation(glstruct.shader_program, "alpha"),(GLfloat)alpha);

}


int		runobj(t_glstruct glstruct, t_index *ret, t_camera camera, int nb_obj, t_obj *obj)
{
	int		i;
	GLuint text[34];
	t_index *tmp;
	
	if (DEBUG)
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
	}
	

	printf("~~~~~~~~~~~~~~~~Shader~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	glstruct.shader_program = create_program();
	glUseProgram(glstruct.shader_program);
	printf("~~~~~~~~~~~~~~~~Texture~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	t_material *mtl;

	mtl = obj->mtl;
	if (mtl)
	{
		while (mtl)
		{
			if (!setup_texture(&glstruct, text, mtl->map_Kd, obj->path))
			{
				ft_putendl("Error Mallocated TGA file\n");
				return (-1);
			}
			mtl = mtl->next;
		}
	}
	else
	{
		if (!setup_texture(&glstruct, text, "Jinx.tga", "\0"))
		{
			ft_putendl("Error Mallocated TGA file\n");
			return (-1);
		}
		tmp = ret;
		while(tmp)
		{
			tmp->index_txt = 0;
			tmp = tmp->next;
		}
	}
	printf("~~~~~~~~~~~~~~~~LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	camera.yaw = -90;
	camera.pitch = 0;
	camera.mouseflag = 1;
	camera.polyflag = 0;
	camera.speed_base = 10.0;
	creat_camera(init_v3(0,0,-3), &camera);
	glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glUseProgram(glstruct.shader_program);
	glUniform3f(glGetUniformLocation(glstruct.shader_program, "size"), fabs(obj->min.x - obj->max.x), fabs(obj->min.y - obj->max.y), fabs(obj->min.z - obj->max.z));
	glUseProgram(glstruct.shader_program);
	glUniform3f(glGetUniformLocation(glstruct.shader_program, "center"), (obj->min.x + obj->max.x) / 2.0, (obj->min.y + obj->max.y) / 2.0, (obj->min.z + obj->max.z) / 2.0);

	tmp = ret;
	while (tmp)
	{
		generate_vbo(&tmp->vbo, tmp->verts, sizeof(float) * tmp->verts_size);
		generate_vao(&tmp->vao, tmp->vbo);
		generate_ebo(&tmp->ebo, (float*)tmp->index, (tmp->face_size));
		tmp = tmp->next;
	}
	while (!glfwWindowShouldClose(glstruct.window))
	{
		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		change_alpha(glstruct, camera);
		
		glfwPollEvents();
		if (camera.mouseflag)
			glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (camera.polyflag)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		int k;
		tmp = ret;
		k = 0;
		while (tmp)
		{
			update_camera(&glstruct, &camera);
	        glActiveTexture(GL_TEXTURE0 + tmp->index_txt);
	        glBindTexture(GL_TEXTURE_2D, text[tmp->index_txt]);
			glUniform1i(glGetUniformLocation(glstruct.shader_program, "texture1"), tmp->index_txt);
			glUseProgram(glstruct.shader_program);
			transformations(glstruct, &camera, obj);
			glBindVertexArray(tmp->vao);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp->ebo);
			glDrawElements(GL_TRIANGLES, tmp->verts_size, GL_UNSIGNED_INT, 0);
			tmp = tmp->next;
			k++;
		}
		glfwSwapBuffers(glstruct.window);
	}
	glfwTerminate();
/*			glDeleteVertexArrays(1 , &glstruct.vao);
			glDeleteBuffers(1, &glstruct.vbo);
			glDeleteBuffers(1, &glstruct.ebo);*/ //free all that for all t_indexes
	// freeobj();
	return (0);
}

void		find_index_material(t_group **group, t_material *mat, int *ret)
{
	int	i = 0;
	t_material *tmp;

	*ret = 0;
	tmp = mat;
	while (tmp)
	{
		if ((*group)->material && tmp->name)
		{
			if (!ft_strcmp((*group)->material, tmp->name))
			{
				printf("[%s] == [%s]\nTexture Find : %d\n", (*group)->material, tmp->name, i);
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
	t_camera 	camera;
	t_obj		*obj;
	int 		i = -1;
	int 		j = -1;
	int 		size;

	if (argc == 1)
		return (0);

    if (!(obj = malloc(sizeof(t_obj))))
        return (objerror(NULL, 1));
    if (init_obj(obj) == -1)
        return (objerror(obj, -1));
    if (argc < 2 || argc > 3)
        return (objerror(obj, 2));
	printf("First Parsing\n");
    if (objload(argv[1], INFO))
        return (objerror(obj, 1));
	i = 0;
	while (i < argc - 2)
	{
		printf("Second Parsing\n");
    	if (objload(argv[i + 2], INFO))
        	return (objerror(obj, 1));
		i++;
	}
	t_group *ptr_grp;
	t_obj *tmp_obj;
	tmp_obj = obj;
	i = 0;
	int savetxt;

	savetxt = 0;
	index.next = NULL;
	ptr = &index;
	while (obj)
	{
		ptr->index_obj = obj->id;
		ptr_grp = obj->group;
		while (ptr_grp)
		{
			// printf("~~~~~~~~~~~~~~~~~~~~Splits~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			if (split_faces(obj, &(tmp), ptr_grp))
				return (1);
			// printf("~~~~~~~~~~~~~~~~~~~~Vertex~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			if (create_vert(*obj, &(ptr), tmp.index, tmp.face_size * 3, ptr_grp))
				return (1);
			free(tmp.index);
			// printf("~~~~~~~~~~~~~~~~~~~~Vertex Done~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			if (ptr_grp && obj->mtl)
			{
				find_index_material(&ptr_grp, obj->mtl, &tmp.index_txt);
				savetxt = tmp.index_txt;
			}
			else if (ptr_grp)
			{
				tmp.index_txt = savetxt;
				printf("Save txt !");
			}
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
	printf("\n~~~~~~~~~~~~~~~~~~~~FreeObj~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	// free_obj(obj);
	printf("~~~~~~~~~~~~~~~~~~~~Init Opengl~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	init_everything(&glstruct);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	return(runobj(glstruct, &index, camera, i + 1, tmp_obj));
}
