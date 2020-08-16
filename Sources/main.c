/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:22:02 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/16 18:20:36 by lomasse          ###   ########.fr       */
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

int		runobj(t_glstruct glstruct, t_index *ret, t_camera camera, int nb_obj)
{
	int		i;
	GLuint text[2];
	
	if (DEBUG)
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
	}
	
	printf("~~~~~~~~~~~~~~~~Vbo_Vao_Ebo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	generate_vbo(&glstruct.vbo, ret->verts, sizeof(float) * ret->verts_size);
	printf("~~~~~~~~~~~~~~~~Vbo_Vao_Ebo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	generate_vao(&glstruct.vao, glstruct.vbo);
	printf("~~~~~~~~~~~~~~~~Vbo_Vao_Ebo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	generate_ebo(&glstruct.ebo, (float*)ret->index, (ret->face_size));
	printf("~~~~~~~~~~~~~~~~Shader~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	glstruct.shader_program = create_program();
	printf("~~~~~~~~~~~~~~~~Texture~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (!setup_texture(&glstruct, text))
	{
		ft_putendl("Error Mallocated TGA file\n");
		return (-1);
	}
	printf("~~~~~~~~~~~~~~~~LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	camera.yaw = -90;
	camera.pitch = 0;
	camera.mouseflag = 1;
	camera.polyflag = 0;
	creat_camera(init_v3(0,0,-3), &camera);
	glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(glstruct.window))
	{
		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, text[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, text[1]);

		transformations(glstruct, &camera);
		update_camera(&glstruct, &camera);
		glUseProgram(glstruct.shader_program);
		glBindVertexArray(glstruct.vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glstruct.ebo);
		if (camera.mouseflag)
			glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (camera.polyflag)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, ret->face_size, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 1, 4);
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(glstruct.window);
	}
	glDeleteVertexArrays(1 , &glstruct.vao);
	glDeleteBuffers(1, &glstruct.vbo);
	glfwTerminate();
	// freeobj();
	return (0);
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
	i = 0;
	index.next = NULL;
	ptr = &index;
	while (obj)
	{
		ptr->index_obj = obj->id;
		ptr_grp = obj->group;
		while (ptr_grp)
		{
			printf("~~~~~~~~~~~~~~~~~~~~Splits~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			if (split_faces(obj, &(tmp), ptr_grp))
				return (1);
			printf("~~~~~~~~~~~~~~~~~~~~Vertex~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			if (create_vert(*obj, &(ptr), tmp.index, tmp.face_size * 3, ptr_grp))
				return (1);
			free(tmp.index);
			printf("~~~~~~~~~~~~~~~~~~~~Vertex Done~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			if (ptr_grp->next)
			{
				if (!(ptr->next = malloc(sizeof(t_index))))
					return (1);
				ptr = ptr->next;
			}
			ptr_grp = ptr_grp->next;
		}
		if (obj->next)
		{
			if (!(ptr->next = malloc(sizeof(t_index))))
				return (1);
			ptr = ptr->next;
		}
		obj = obj->next;
		++i;
	}
	printf("\n~~~~~~~~~~~~~~~~~~~~FreeObj~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	// free_obj(obj);
	printf("~~~~~~~~~~~~~~~~~~~~Init Opengl~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	init_everything(&glstruct);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	return(runobj(glstruct, &index, camera, i + 1));
}
