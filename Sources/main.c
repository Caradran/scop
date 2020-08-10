/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:22:02 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/10 16:41:34 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../Include/scop.h"

void	creat_camera(t_vec3 pos,  t_camera *camera);
void	transformations(t_glstruct glstruct, t_camera *camera);
void	update_camera(t_glstruct *glstruct, t_camera *camera);

int		runobj(t_glstruct glstruct, t_index ret, t_camera camera)
{
	init_glfw();
	if (!(glstruct.window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL)))
		print_error(2);
	glfwMakeContextCurrent(glstruct.window);
	init_glew();
	
	if (DEBUG)
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
	}

	generate_vbo(&glstruct.vbo, ret.verts, sizeof(float) * ret.size);
	generate_vao(&glstruct.vao, glstruct.vbo);
	generate_ebo(&glstruct.ebo, (float*)ret.index, (ret.index_size) * sizeof(int));

	if (!setup_texture())
	{
		ft_putendl("Error Mallocated TGA file\n");
		return (-1);
	}

	glstruct.shader_program = create_program();

	printf("~~~~~~~~~~~~~~~~LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	camera.yaw = -90;
	camera.pitch = 0;
	creat_camera(init_v3(0,0,-3), &camera);
	glfwSetInputMode(glstruct.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!glfwWindowShouldClose(glstruct.window))
	{
		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		transformations(glstruct, &camera);
		update_camera(&glstruct, &camera);
		glUseProgram(glstruct.shader_program);
		glBindVertexArray(glstruct.vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glstruct.ebo);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, ret.index_size, GL_UNSIGNED_INT, 0);
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
	t_index		index_split;
	t_index		index;
	t_camera 	camera;
	t_obj		*obj;

	if (argc == 1)
		return (0);

    if (!(obj = malloc(sizeof(t_obj))))
        return (objerror(NULL, 1));
    if (init_obj(obj) == -1)
        return (objerror(obj, -1));
    if (argc < 2 || argc > 2)
        return (objerror(obj, 2));
    if (objload(argv[1]))
        return (objerror(obj, 1));

	/* Obj Checker */
	int i = -1;
	int j = -1;
	while (++i < obj->size_face[0])
	{
		j = -1;
		while (++j < obj->face[i].size)
			printf("Fv [%d][%d]: %d||%d||%d\n", i, j, obj->face[i].i_v[j], obj->face[i].i_vt[j], obj->face[i].i_vn[j]);
	}
	i = -1;
	while (++i < obj->size_v[0])
		printf("V : %f||%f||%f\n", obj->v[i].x, obj->v[i].y, obj->v[i].z);
	i = -1;
	while (++i < obj->size_vt[0])
		printf("VT : %f||%f||%f\n", obj->vt[i].x, obj->vt[i].y, obj->vt[i].z);
	i = -1;
	while (++i < obj->size_vn[0])
		printf("VN : %f||%f||%f\n", obj->vn[i].x, obj->vn[i].y, obj->vn[i].z);
	/* Obj Checker */
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	int size;
	size = 0;
	index_split.index = split_faces(obj, &size);
	
	for (int i = 0; i < 6; i++)
		printf("==> [%d]\n", index_split.index[i * 3]);
	/* /!\ Ne split pas actuellement */
	/* Split Checker */
	// i = -1;
	// while (++i < size * 9)
	// {
	// 	if (!(i%9))
	// 		printf("Face : %d\n", i / 3);
	// 	if (!(i%3))
	// 		printf("Point : %d\n", i / 3);
	// 	printf("index ID : %d\n", index_split.index[i]);
	// }
	/* Split Checker */
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	index = create_vert(*obj, index_split.index, size);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < index.size / 13; i++)
	{
		printf("[%d] :", i);
		for (int j = 0; j < 13; j++)
			printf("%f\t", index.verts[(i * 13) + j]);
		printf("\n");
	}
	return(runobj(glstruct, index, camera));
}
