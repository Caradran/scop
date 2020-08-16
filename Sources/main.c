/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:22:02 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/15 18:57:21 by lomasse          ###   ########.fr       */
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
	static float alpha = 0;
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
	if (alpha != 1 && alpha != 0)
		printf("%f \n", alpha);
	glUniform1f(glGetUniformLocation(glstruct.shader_program, "alpha"),(GLfloat)alpha);

}


int		runobj(t_glstruct glstruct, t_index *ret, t_camera camera, int nb_obj, t_obj *obj)
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
	generate_vbo(&glstruct.vbo, ret->verts, sizeof(float) * ret->size);
	printf("~~~~~~~~~~~~~~~~Vbo_Vao_Ebo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	generate_vao(&glstruct.vao, glstruct.vbo);
	printf("~~~~~~~~~~~~~~~~Vbo_Vao_Ebo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	generate_ebo(&glstruct.ebo, (float*)ret->index, (ret->index_size));
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

		transformations(glstruct, &camera, obj);
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
		change_alpha(glstruct, camera);
		glDrawElements(GL_TRIANGLES, ret[0].index_size, GL_UNSIGNED_INT, 0);
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
	t_index		index_split[2];
	t_index		index[2];
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
	if (argc > 2)
	{
		printf("Second Parsing\n");
    	if (objload(argv[2], INFO))
        	return (objerror(obj, 1));
	}
	i = 0;
	printf("adr obj %p\n", obj);
	while (obj)
	{
		printf("Obj : %s\n", obj->path);
		printf("~~~~~~~~~~~~~~~~~~~~Splits~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		size = 0;
		split_faces(obj, &size, &(index_split[i]));
		printf("~~~~~~~~~~~~~~~~~~~~Vertex~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		index[i] = create_vert(*obj, index_split[i].index, size, index_split[i].index_txt);
		printf("~~~~~~~~~~~~~~~~~~~~Vertex Done~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		if (!obj->next)
			break ;
		obj = obj->next;
		++i;
	}
	printf("\n~~~~~~~~~~~~~~~~~~~~FreeObj~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	// free_obj(obj);
	printf("~~~~~~~~~~~~~~~~~~~~Init Opengl~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	init_everything(&glstruct);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	return(runobj(glstruct, index, camera, i + 1, obj));
}
